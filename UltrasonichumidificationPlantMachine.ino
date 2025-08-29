#include "Enviroment.h"
#include "TempHumi.h"
#include "Led.h"
#include "PlantSupplyWater.h"
#include "WaterTankMotor.h"
#include "RealTime.h"
#include "WaterSensor.h"
#include "DashBoard.h"
//가습기 핀
#define humidifier_pin 3
//온습도 핀
#define dht_pin 4
//LED 핀
#define led_pin 5

//RTC Sensor 핀
#define clk 11
#define dat 12
#define rst 13

//수위 센서 핀
#define WaterSensorPin 10

//물 펌프 핀
//pwm 가능한 pin에만 연결
#define motor_pin 9
//0~255
#define motor_power 250

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
WaterTankMotor waterTankMotor(motor_pin,motor_power);

TempHumi tempHumi(dht_pin);

DashBoard dashBoard(0x27,16,2);


//millis 관련 코드 ------------------------------

  unsigned long previous_ledTime = 0;
  unsigned long previous_humidifierTime = 0;
  unsigned long previous_waterTankTime = 0;
  
  const long interval_humidifierTime = 3000;
  const long interval_ledTime = 5000;
  const long interval_waterTankTime = 5000;
  
  unsigned long previous_DashBoardTime = 0;
  
  const long interval_DashBoardTime = 9000;
  
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
  if(currentMillis-previous_ledTime >= interval_ledTime){
    previous_ledTime = currentMillis;
    Serial.println("led 제어");
    led.control();

  }

  if(currentMillis-previous_humidifierTime >= interval_humidifierTime){
    previous_humidifierTime = currentMillis;
    plantSupplyWater.control();
  }

  //수위센서에 따른 물 펌프 제어
  if(currentMillis-previous_waterTankTime >= interval_waterTankTime){
    previous_waterTankTime = currentMillis;
    
    //수위센서에 물이 닿지 않으면 motor ON
    if(waterSensor.getTouchWater() == 0)
    { //not touch : 0 , touch : 1
      waterTankMotor.turnOn();
    //수위센서에 물이 닿으면 motor OFF
    }else{ //20 ~ n
      waterTankMotor.turnOff();
    }

  }

  if(currentMillis-previous_DashBoardTime >= interval_DashBoardTime){
    previous_DashBoardTime = currentMillis;
    
        // 센서 값을 읽어옴
    tempHumi.readSensor();
    float temp = tempHumi.getTemperature();
    float humi = tempHumi.getHumidity();

    // LCD에 출력할 문자열 버퍼를 선언하고 충분한 크기로 확보
    char tempBuffer[20];
    char humiBuffer[20];
    
    // 온도를 문자열로 변환 (예: "Temp: 25.5 C")
    sprintf(tempBuffer, "Temp: %.1f C", temp);
    
    // 습도를 문자열로 변환 (예: "Humi: 78.3 %")
    sprintf(humiBuffer, "Humi: %.1f %%", humi);
    // 참고: '%' 기호를 출력하려면 '%%'를 사용해야 합니다.

    // 첫 번째 줄에 온도 출력
    dashBoard.firstLinePrint(tempBuffer);
    
    // 두 번째 줄에 습도 출력
    dashBoard.secondLinePrint(humiBuffer);
  }


}
