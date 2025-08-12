#ifndef HumidifierController_h
#define HumidifierController_h

#include "Arduino.h"
#include "Enviroment.h"
#include <DHT.h>

#define DHTTYPE DHT11

class HumidifierController {
public:
    HumidifierController(Enviroment* idealEnviroment, int humidifierPin, int dhtSensorPin)
      : _idealEnviroment(idealEnviroment), 
        _humidifierPin(humidifierPin), 
        _dhtSensorPin(dhtSensorPin),
        dht(_dhtSensorPin, DHTTYPE)
    {
        pinMode(_humidifierPin, OUTPUT);
        dht.begin();
    }

    void control() {
        // control() 함수에서 한 번만 센서 값을 읽고 멤버 변수에 저장
        _current_humidity = dht.readHumidity();
        _current_temperature = dht.readTemperature();

        if (isnan(_current_humidity) || isnan(_current_temperature)) {
            Serial.println("DHT 센서 읽기 실패");
            return;
        }
        
        Serial.print("Current Humidity: ");
        Serial.print(_current_humidity);
        Serial.print(" % | Target Range: ");
        Serial.print(_idealEnviroment->getHumidMin());
        Serial.print(" ~ ");
        Serial.print(_idealEnviroment->getHumidMax());
        Serial.println(" %");
        
        if (_current_humidity < _idealEnviroment->getHumidMin()) {
            turnOn();
        } else if (_current_humidity > _idealEnviroment->getHumidMax()) {
            turnOff();
        }
    }

    void turnOn() {
        digitalWrite(_humidifierPin, HIGH);
        // Serial.println("가습기 ON");
    }

    void turnOff() {
        digitalWrite(_humidifierPin, LOW);
        // Serial.println("가습기 OFF");
    }


private:
    Enviroment* _idealEnviroment;
    float _current_temperature;
    float _current_humidity;
    int _dhtSensorPin;
    int _humidifierPin;
    DHT dht;
};

#endif