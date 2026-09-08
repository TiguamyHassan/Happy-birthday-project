#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int BUZZER = 4, LED1 = 3, LED2 = 2;
int melody[] = {262, 262, 294, 262, 349, 330, 262, 262, 294, 262, 392, 349, 262, 262, 523, 440, 349, 330, 294, 466, 466, 440, 349, 392, 349};
int durations[] = {300, 300, 400, 400, 400, 600, 300, 300, 400, 400, 400, 600, 300, 300, 400, 400, 400, 400, 400, 300, 300, 400, 400, 400, 600};
int notes = 25, ledPattern = 0;
unsigned long lastLed = 0;
void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  lcd.init();
  lcd.backlight();
}
void loop() {
  lcd.clear();
  lcd.print("Happy Birthday!");
  for (int i = 0; i < notes; i++) {
    tone(BUZZER, melody[i], durations[i]);
    unsigned long start = millis();
    while (millis() - start < durations[i]) {
      if (millis() - lastLed > 200) {
        lastLed = millis();
        ledPattern = (ledPattern + 1) % 4;
        digitalWrite(LED1, ledPattern == 0 || ledPattern == 2);
        digitalWrite(LED2, ledPattern == 1 || ledPattern == 2);
      }
      delay(10);
    }
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(50);
  }
  lcd.clear();
  lcd.print("Happy Birthday!");
  lcd.setCursor(0, 1);
  lcd.print("Enjoy!");
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(200);
  }
  delay(1000);
}
