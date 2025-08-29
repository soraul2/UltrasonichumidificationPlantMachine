#ifndef WaterTankMotor_h
#define WaterTankMotor_h


class WaterTankMotor{

  public :
    WaterTankMotor(int motor_pin , int motor_power);
      
    void turnOn();
    void turnOff();

  private : 
    int _motor_pin;
    int _motor_power;

};

#endif