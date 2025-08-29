#ifndef DashBoard_h
#define DashBoard_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class DashBoard {

private:
  LiquidCrystal_I2C _lcd;

public:
  DashBoard(uint8_t address, uint8_t cols, uint8_t rows)
    : _lcd(address, cols, rows) {
  }

  void init() {
    _lcd.init();
    _lcd.backlight();
  }

  void firstLinePrint(const char* text) {
    _lcd.setCursor(0, 0);
    _lcd.print(text);
  }

  void secondLinePrint(const char* text) {
    _lcd.setCursor(0, 1);
    _lcd.print(text);
  }
};

#endif