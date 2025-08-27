#include "Humidifier.h"

// 생성자 선언 및 초기화
Humidifier::Humidifier(int humidifier_pin, int tempHumiSensor_pin, Enviroment* idealEnviroment)
  : _humidifier_pin(humidifier_pin),
    _tempHumiSensor_pin(tempHumiSensor_pin),
    _idealEnviroment(idealEnviroment),
    _humidMax(_idealEnviroment->getHumidMax()),
    _humidMin(_idealEnviroment->getHumidMin()),
    _tempHumiSensor(_tempHumiSensor_pin) {  // TempHumiSensor 객체 초기화

    pinMode(_humidifier_pin, OUTPUT);
    _tempHumiSensor.init();  // 센서 초기화는 생성자에서 한 번만 호출
}

// 가습기 작동 제어
void Humidifier::control() {
  _tempHumiSensor.readSensor();                       // 센서에서 최신 값 읽기
  _current_humidity = _tempHumiSensor.getHumidity();  // 습도 값 갱신

  if (_current_humidity < _humidMin) {
    turnOn();
  } else if (_current_humidity > _humidMax) {
    turnOff();
  }
}

void Humidifier::turnOn() {
  digitalWrite(_humidifier_pin, HIGH);
}

void Humidifier::turnOff() {
  digitalWrite(_humidifier_pin, LOW);
}