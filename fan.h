#ifndef FAN_H
#define FAN_H

#include "Arduino.h"

class Fan {

private:
    int _fanPin;

public:
    Fan(int fanPin) {
        _fanPin = fanPin;
        pinMode(_fanPin, OUTPUT);
    }

    void turnOn() const {
        Serial.println("FAN ON()");
        digitalWrite(_fanPin, LOW);
    }

    void turnOff() const {
        Serial.println("FAN OFF()");
        digitalWrite(_fanPin, HIGH);
    }
};

#endif