#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 16);

int sensorPin = A0;
void setup()
{
  lcd.begin();
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DATA KEKERUHAN"));
}

void loop() {
  for (int i = 1; i < 1000000; i++)
  {
    Serial.print("{\"Detik\": ");
    Serial.print(i);
  

  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  lcd.setCursor(0, 0);
  lcd.print("Kekeruhan:");
  lcd.print("   ");
  lcd.setCursor(10, 0);
  lcd.print(turbidity);

  Serial.print(",\"Kekeruhan\": ");
 
  if (turbidity < 20) {
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
    lcd.setCursor(0, 1);
    lcd.print("----- AMAN -----");
    Serial.print(turbidity);
    Serial.print(",\"Status\": ");
    Serial.print(1);
  };
  if ((turbidity > 19) && (turbidity < 51)) {
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    lcd.setCursor(0, 1);
    lcd.print("-- AGAK KERUH --");
    Serial.print(turbidity);
    Serial.print(",\"Status\": ");
    Serial.print(2);
  };
  if (turbidity > 50) {
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(3, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("- SEGERA GANTI -");
    Serial.print(turbidity);
    Serial.print(",\"Status\": ");
    Serial.print(3);
  };
  Serial.println("}");
  delay(1000);
  }
}
