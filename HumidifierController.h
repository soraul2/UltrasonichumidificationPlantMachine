#ifndef HumidifierController_h
#define HumidifierController_h

#include "Arduino.h"
#include "Enviroment.h"
#include <DHT.h>

// DHT 센서 타입 정의
#define DHTTYPE DHT11

class HumidifierController {
public:
    // 생성자 매개변수 및 멤버 이니셜라이저 리스트 수정
    HumidifierController(Enviroment* idealEnviroment, int humidifierPin, int dhtSensorPin)
      : _idealEnviroment(idealEnviroment), 
        _humidifierPin(humidifierPin), 
        _dhtSensorPin(dhtSensorPin),
        dht(_dhtSensorPin, DHTTYPE)
    {
        // 생성자 본문에서는 멤버 변수 초기화 외의 다른 로직은 최소화
        pinMode(_humidifierPin, OUTPUT);
        dht.begin();
    }

    void control() {
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
    int _dhtSensorPin; // dht 센서 핀
    int _humidifierPin; // 가습기 핀
    DHT dht;
};

#endif