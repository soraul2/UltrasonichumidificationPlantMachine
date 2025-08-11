#ifndef MotorController_h
#define MotorController_h


class MotorController{

  public :
    MotorController(int motor_pin , int motor_power);
      

    void turnOn();
    void turnOff();

  private : 
    int _motor_pin;
    int _motor_power;

};

#endif