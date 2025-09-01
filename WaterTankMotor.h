#ifndef WaterTankMotor_h
#define WaterTankMotor_h


class WaterTankMotor{

  public :
    WaterTankMotor(int motor_pin);
      
    void turnOn();
    void turnOff();

  private : 
    int _motor_pin;
};

#endif