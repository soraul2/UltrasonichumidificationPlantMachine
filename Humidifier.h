#include <Arduino.h>
#include "TempHumiSensor.h"
#include "Enviroment.h" // Enviroment 클래스 헤더 추가

class Humidifier {
public:
  Humidifier(int humidifier_pin, int tempHumiSensor_pin, Enviroment* idealEnviroment);
  
  void control();
  void turnOn();
  void turnOff();

private:
  int _humidifier_pin;
  int _tempHumiSensor_pin; // 핀 번호 멤버 변수 추가

  float _current_humidity; // float으로 수정
  float _humidMin;
  float _humidMax;

  Enviroment* _idealEnviroment;
  TempHumiSensor _tempHumiSensor; // TempHumiSensor 객체 추가
};