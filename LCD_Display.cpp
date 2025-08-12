
LCD_Display::LCD_Display(uint8_t lcd_addr , uint8_t lcd_cols, uint8_t lcd_rows)
  :_lcd(lcd_addr , lcd_cols , lcd_rows){ 

}

LCD_Display::initialize(){
  _lcd.init();
  _lcd.backlight();
}

LCD_Display::showMessage(const char* line1, const char* line2){
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}