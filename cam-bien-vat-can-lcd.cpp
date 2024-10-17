#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Sensor A0
#define THRESHOLD 512
int Value;
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup() {  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LDR Value: ");

}

void loop() {
  Value = analogRead(Sensor);
  lcd.setCursor(10, 0);
  lcd.print("               ");
  if (Value < THRESHOLD){
    lcd.setCursor(10, 0);
    lcd.print("1");
  }
  else{
    lcd.setCursor(10, 0);
    lcd.print("0");
  }
  delay(500);
}
