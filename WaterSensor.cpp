#include "WaterSensor.h"
#include <Arduino.h>  // 아두이노 라이브러리를 포함합니다.

// 생성자 구현
WaterSensor::WaterSensor(int waterSensor_pin)
  : _waterSensor_pin(waterSensor_pin) {
}

// getValue() 함수 구현
int WaterSensor::getValue() const {  // const 키워드 추가
  // 멤버 변수인 _waterSensor_pin을 사용해야 합니다.
  return analogRead(_waterSensor_pin);
}