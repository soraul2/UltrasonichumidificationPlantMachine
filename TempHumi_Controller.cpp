#include "TempHumi_Controller.h"

TempHumi_Controller::TempHumi_Controller(int dht_pin)
  : _dht_pin(dht_pin), dht(_dht_pin, DHTTYPE) {
}

void TempHumi_Controller::setup() {
  dht.begin();
}

void TempHumi_Controller::readSensor() {
  _humidity = dht.readHumidity();
  _temperature = dht.readTemperature();
}

float TempHumi_Controller::getTemperature() {
  return _temperature;
}

float TempHumi_Controller::getHumidity() {
  return _humidity;
}