#include "WaterTankMotor.h"
#include <Arduino.h>

WaterTankMotor::WaterTankMotor(int motor_pin)
  : _motor_pin(motor_pin){
  pinMode(_motor_pin, OUTPUT);
}

void WaterTankMotor::turnOn() {
  Serial.println("motor ON");
  digitalWrite(_motor_pin,LOW);
}

void WaterTankMotor::turnOff() {
  Serial.println("motor Off");
  digitalWrite(_motor_pin, HIGH);
}