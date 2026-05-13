#include <DFRobot_RGBLCD1602.h>

DFRobot_RGBLCD1602 lcd(0x6B,16,2);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.setBacklight(true);
}

void loop() {
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print(millis(), DEC);
}
