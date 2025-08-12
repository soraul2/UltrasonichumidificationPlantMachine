#include "Enviroment.h"
#include "HumidifierController.h"
#include "Led_OnOff_Controller.h"
#include "WaterSensor.h"
#include "MotorController.h"

#define humidifier_pin 3
#define dht_pin 4
#define led_pin 5

#define clk 6
#define dat 7
#define rst 8

#define waterSensor_pin A0

//pwm 가능한 pin에만 연결
#define motor_pin 9
//0~255
#define motor_power 250

//Enviroment 데이터 값 넣기
//(최저 온도 , 최대 온도 , 최저 습도 , 최대 습도 , 시작 시간 , 종료 시간)
Enviroment enviroment(20.0, 25.0, 75, 85, 6, 19);

//가습기 컨트롤러 객체 생성
HumidifierController humidifierController(&enviroment, humidifier_pin, dht_pin);
//LED ON OFF 컨트롤러 객체 생성
Led_OnOff_Controller led_OnOff_Controller(&enviroment, led_pin, clk, dat, rst);

//수위 센서 객체 생성
WaterSensor waterSensor(waterSensor_pin);
//펌프 컨트롤러 객체 생성
MotorController motorController(motor_pin,motor_power);
//millis 관련 코드 ------------------------------

  unsigned long previous_ledTime = 0;
  unsigned long previous_humidifierTime = 0;
  unsigned long previous_waterTankTime = 0;

  const long interval_humidifierTime = 3000;
  const long interval_ledTime = 5000;
  const long interval_waterTankTime = 5000;
  
  
//millis 관련 코드-------------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("가습기 제어 시스템을 시작합니다.");
  Serial.println("Led 제어 시스템을 시작합니다.");
  
  delay(2000);  //센서가 안정될 시간
}

void loop() {

  unsigned long currentMillis = millis();

  //시간에 따른 LED 제어
  if(currentMillis-previous_ledTime >= interval_ledTime){
    previous_ledTime = currentMillis;
    Serial.println("led 제어");
    led_OnOff_Controller.control();
  
  }

  //가습기 제어
  if(currentMillis-previous_humidifierTime >= interval_humidifierTime){
    previous_humidifierTime = currentMillis;
    humidifierController.control();
  }

  //수위센서에 따른 물 펌프 제어
  if(currentMillis-previous_waterTankTime >= interval_waterTankTime){
    previous_waterTankTime = currentMillis;
    
    //수위센서에 물이 닿지 않으면 motor ON
    if(waterSensor.getValue() <= 20){ // -n ~ 20 , 20까지는 습도 보정 값
      motorController.turnOn();
    //수위센서에 물이 닿으면 motor OFF
    }else{ //20 ~ n
      motorController.turnOff();
    }

  }

}




