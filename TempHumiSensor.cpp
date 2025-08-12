#include "TempHumiSensor.h"
#define DHTTYPE DHT11

TempHumiSensor::TempHumiSensor(int dht_pin) :
    _dht_pin(dht_pin),
    _dht(_dht_pin, DHTTYPE) {
    // 생성자 초기화 리스트에서 _dht_pin과 _dht를 초기화합니다.
}

void TempHumiSensor::init() {
    _dht.begin(); // 기존 _dht 객체의 begin() 함수만 호출합니다.
}

void TempHumiSensor::readSensor() {
    // 센서에서 값을 읽어 멤버 변수를 갱신합니다.
    _humidity = _dht.readHumidity();
    _temperature = _dht.readTemperature();
}

float TempHumiSensor::getTemperature() {
    return _temperature;
}

float TempHumiSensor::getHumidity() {
    return _humidity;
}