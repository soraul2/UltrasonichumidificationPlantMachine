#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(int motor_pin, int motor_power)
  : _motor_pin(motor_pin), _motor_power(motor_power) {
  pinMode(_motor_pin, OUTPUT);
}

void MotorController::turnOn() {
  Serial.println("motor ON");
  analogWrite(_motor_pin, _motor_power);
}

void MotorController::turnOff() {
  Serial.println("motor Off");
  analogWrite(_motor_pin, 0);
}