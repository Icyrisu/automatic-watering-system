#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int wet = 239;
const int dry = 595;

LiquidCrystal_I2C lcd(0x20, 16, 2);

int aPin = A0; // pin Analog Soil Moisture 1
int bPin = A1; // pin Analog Soil Moisture 2
int cPin = A2; // pin Analog Soil Moisture 3

int valvePin = 2; // pin Digital Valve 2
int pumpPin = 3; // pin Digital Pump 3

int topValue; // buat atur batas atas
int botValue; // buat atur batas bawah

void setup() {
  // buat Relay sebagai output
  pinMode(valvePin, OUTPUT);
  pinMode(pumpPin, OUTPUT);

  // buat nyalain LCD
  lcd.init(); 
  lcd.backlight();
}

void loop() {
  // buat baca nilai Soil Moisture
  int aValue = analogRead(aPin);
  int bValue = analogRead(bPin);
  int cValue = analogRead(cPin);

  // buat baca nilai Potensiometer
  topValue = 80;
  botValue = 40;

  // buat baca relay
  int valveStatus = digitalRead(valvePin);
  int pumpStatus = digitalRead(pumpPin);

  // buat jadiin persen
  int aPercentage = map(aValue, wet, dry, 100, 0);
  int bPercentage = map(bValue, wet, dry, 100, 0);
  int cPercentage = map(cValue, wet, dry, 100, 0);

  // buat tampilan di LCD
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("1: ");
  lcd.print(aPercentage);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("2: ");
  lcd.print(bPercentage);
  lcd.print("%");

  lcd.setCursor(8, 0);
  lcd.print("3: ");
  lcd.print(cPercentage);
  lcd.print("%");

  if (aPercentage < botValue || bPercentage < botValue || cPercentage < botValue) {
    digitalWrite(valvePin, HIGH);
    digitalWrite(pumpPin, HIGH);
    
  } else if (aPercentage > topValue && bPercentage > topValue && cPercentage > topValue) {
    digitalWrite(valvePin, LOW);
    digitalWrite(pumpPin, LOW);
    
  }

  if (pumpStatus == HIGH) {
    lcd.setCursor(8, 1);
    lcd.print("Pump:ON");
  } else {
    lcd.setCursor(8, 1);
    lcd.print("Pump:OFF");
  }

  // perhitungan tiap 1000 milisekon = 1 sekon
  delay(1000); 
}