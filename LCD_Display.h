#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCD_Display{

  public :
    LCD_Display();

    void initialize();
    void showMessage(const char* line1, const char* line2);

  private :
    LiquidCrystal_I2C _lcd;


}

