#include "Enviroment.h"
#include "TempHumi.h"
#include "Led.h"
#include "PlantSupplyWater.h"
#include "WaterTankMotor.h"
#include "RealTime.h"
#include "WaterSensor.h"
#include "DashBoard.h"
#include "fan.h"

//출력 핀 (OUT PUT)

//가습기 핀
#define humidifier_pin 3

//LED 핀
#define led_pin 4

//pumpPin
//pwm 가능한 pin에만 연결
#define motor_pin 5

//fanPin
#define fanPin 6

//환경 데이터 핀 (INPUT)

//온습도 핀
#define dht_pin 7

//수위 센서 핀
#define WaterSensorPin 8

//RTC Sensor 핀
#define clk 11
#define dat 12
#define rst 13


static bool isFanOn = false;  // 팬의 현재 상태를 저장하는 변수

//lcd pin 추가

//Enviroment 데이터 값 넣기
//(최저 온도 , 최대 온도 , 최저 습도 , 최대 습도 , 시작 시간 , 종료 시간)
Enviroment enviroment(20.0, 25.0, 75, 85, 6, 19);

//h bridge를 활용하여 미니 온도 조절기 사용
//survo 모터를 활용하여 외부 창 On Off


//가습기 컨트롤러 객체 생성
PlantSupplyWater plantSupplyWater(&enviroment, humidifier_pin, dht_pin);
//LED ON OFF 컨트롤러 객체 생성
Led led(&enviroment, led_pin, clk, dat, rst);

//수위 센서 객체 생성
WaterSensor waterSensor(WaterSensorPin);
//펌프 컨트롤러 객체 생성
WaterTankMotor waterTankMotor(motor_pin);

TempHumi tempHumi(dht_pin);

DashBoard dashBoard(0x27, 16, 2);

Fan fan(fanPin);

//millis 관련 코드 ------------------------------

unsigned long previous_ledTime = 0;
unsigned long previous_humidifierTime = 0;
unsigned long previous_waterTankTime = 0;

const long interval_humidifierTime = 3000;
const long interval_ledTime = 5000;
const long interval_waterTankTime = 5000;

unsigned long previous_fanTime = 0;

const long interval_fanTime = 10000;


unsigned long previous_dashboardTime = 0;

const long interval_dashboardTime = 1000;


//millis 관련 코드-------------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("가습기 제어 시스템을 시작합니다.");
  Serial.println("Led 제어 시스템을 시작합니다.");
  Serial.println("TempHumi Controller Initialized!");


  //온습도 센서 초기화
  tempHumi.setup();

  //dashboard 초기화
  dashBoard.init();

  delay(2000);  //센서가 안정될 시간
}

void loop() {

  unsigned long currentMillis = millis();

  //시간에 따른 LED 제어
  if (currentMillis - previous_ledTime >= interval_ledTime) {
    previous_ledTime = currentMillis;
    Serial.println("led 제어");
    led.control();
  }

  if (currentMillis - previous_humidifierTime >= interval_humidifierTime) {
    previous_humidifierTime = currentMillis;
    plantSupplyWater.control();
  }

  //수위센서에 따른 물 펌프 제어
  if (currentMillis - previous_waterTankTime >= interval_waterTankTime) {
    previous_waterTankTime = currentMillis;

    //수위센서에 물이 닿지 않으면 motor ON
    if (waterSensor.getTouchWater() == 1) {  //not touch : 0 , touch : 1
      waterTankMotor.turnOn();
      //수위센서에 물이 닿으면 motor OFF
    } else {  //20 ~ n
      waterTankMotor.turnOff();
    }
  }



  if (currentMillis - previous_fanTime >= interval_fanTime) {
    previous_fanTime = currentMillis;

    float humi = tempHumi.getHumidity();

    if (humi >= 85.0 && !isFanOn) {
      fan.turnOn();
      isFanOn = true;
    } else if (humi <= 70.0 && isFanOn) {
      fan.turnOff();
      isFanOn = false;
    }
  }


  if (currentMillis - previous_dashboardTime >= interval_dashboardTime) {
    previous_dashboardTime = currentMillis;
    tempHumi.readSensor();
    float humi = tempHumi.getHumidity();
    Serial.println(humi);
    // 습도 값을 담을 char 배열
    char humiValueStr[10];
    // 전체 문자열을 담을 char 배열
    char fullString[20];

    // dtostrf(변수, 최소너비, 소수점 자릿수, 배열)
    // humi 변수의 값을 소수점 2자리까지 humiValueStr에 저장
    dtostrf(humi, 4, 2, humiValueStr);

    // dtostrf 변환 예시:
    // humiValueStr은 "50.50" 문자열을 가짐

    // strcat 함수로 두 문자열을 합치기
    // 먼저 "습도: " 문자열을 fullString에 복사
    strcpy(fullString, "humi: ");
    // 이어서 humiValueStr 내용을 fullString에 추가
    strcat(fullString, humiValueStr);
    // 마지막으로 "%" 기호를 추가
    strcat(fullString, "%");

    // 완성된 문자열을 두 번째 줄에 출력
    dashBoard.firstLinePrint(fullString);
    

  }
}
