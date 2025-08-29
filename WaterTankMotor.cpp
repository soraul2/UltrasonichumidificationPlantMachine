#include "WaterTankMotor.h"
#include <Arduino.h>

WaterTankMotor::WaterTankMotor(int motor_pin, int motor_power)
  : _motor_pin(motor_pin), _motor_power(motor_power) {
  pinMode(_motor_pin, OUTPUT);
}

void WaterTankMotor::turnOn() {
  Serial.println("motor ON");
  analogWrite(_motor_pin, _motor_power);
}

void WaterTankMotor::turnOff() {
  Serial.println("motor Off");
  analogWrite(_motor_pin, 0);
}