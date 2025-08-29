#include "TempHumi.h"

TempHumi::TempHumi(int dht_pin)
  : _dht_pin(dht_pin), dht(_dht_pin, DHTTYPE) {
}

void TempHumi::setup() {
  dht.begin();
}

void TempHumi::readSensor() {
  _humidity = dht.readHumidity();
  _temperature = dht.readTemperature();
}

float TempHumi::getTemperature() {
  return _temperature;
}

float TempHumi::getHumidity() {
  return _humidity;
}

