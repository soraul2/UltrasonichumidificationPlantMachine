#ifndef WaterSensor_h
#define WaterSensor_h

#include "Arduino.h"

//with water 5
//no water 0

class WaterSensor {

public:
    // digtal Pin 으로 받아야한다.
    WaterSensor(int waterSensorPin){
        _waterSensorPin = waterSensorPin;
        pinMode(_waterSensorPin,INPUT);
    }
    
    //touch : 1 , not touch 0
    bool getTouchWater(){
        _touchWater = digitalRead(_waterSensorPin);
        Serial.println(_touchWater);
        return _touchWater;
    }

private:
    int _waterSensorPin;
    int _touchWater;
};

#endif