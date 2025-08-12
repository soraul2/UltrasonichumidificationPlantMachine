#ifndef TempHumi_Controller_h
#define TempHumi_Controller_h

#include "Arduino.h"
#include <DHT.h>

#define DHTTYPE DHT11

class TempHumi_Controller{

  public :
    TempHumi_Controller(int dht_pin);
    void setup();
    void readSensor();

    float getTemperature();
    float getHumidity();

  private :
    int _dht_pin;
    float _temperature;
    float _humidity;

    DHT dht;

};

#endif