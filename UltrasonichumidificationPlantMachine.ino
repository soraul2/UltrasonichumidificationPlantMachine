#include "Enviroment.h"
#include "HumidifierController.h"
#include "Led_OnOff_Controller.h"
#include "WaterSensor.h"
#include "MotorController.h"

UltrasonichumidificationPlantMachine

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

HumidifierController humidifierController(&enviroment, humidifier_pin, dht_pin);
Led_OnOff_Controller led_OnOff_Controller(&enviroment, led_pin, clk, dat, rst);

WaterSensor waterSensor(waterSensor_pin);
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

  //LED CONTROL
  if(currentMillis-previous_ledTime >= interval_ledTime){
    previous_ledTime = currentMillis;
    led_OnOff_Controller.control();
  }

  if(currentMillis-previous_humidifierTime >= interval_humidifierTime){
    previous_humidifierTime = currentMillis;
    humidifierController.control();
  }

  if(currentMillis-previous_waterTankTime >= interval_waterTankTime){
    previous_waterTankTime = currentMillis;
    
    Serial.println(waterSensor.getValue());

    //수위센서에 물이 닿지 않으면 motor ON
    if(waterSensor.getValue() <= 0){
      motorController.turnOn();
    //수위센서에 물이 닿으면 motor OFF
    }else{
      motorController.turnOff();
    }

  }

}




