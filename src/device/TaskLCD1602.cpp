#include "TaskLCD1602.h"

LCD_I2C lcd(0x21, 16, 2);

void initLCD1602() {
    Wire.begin(SDA, SCL);
    lcd.begin();
    lcd.backlight();
}