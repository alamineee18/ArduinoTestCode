#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address (you may need to change this)
LiquidCrystal_I2C lcd(0x27, 20, 4);  // 0x27 is the default I2C address for most 16x2 I2C LCD modules

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
}

void loop() {
  lcd.setCursor(0, 0);              // Set the cursor to the first line, first position
  lcd.print("Hello!");       // Print text on the LCD
  lcd.setCursor(0, 1);              // Set the cursor to the first line, first position
  lcd.print("Ruhul Engineering Ltd.");       // Print text on the LCD
  delay(1000);                     // Wait for 1 second
  //lcd.clear();                     // Clear the LCD
  delay(1000);                     // Wait for 1 second
}
