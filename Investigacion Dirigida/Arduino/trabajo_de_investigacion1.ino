#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int pinAnalogico = A0;
const float VREF = 5.0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  const int muestras = 30;
  long suma = 0;

  for (int i = 0; i < muestras; i++) {
    suma += analogRead(pinAnalogico);
    delay(2);
  }

  float adcPromedio = suma / (float)muestras;
  float voltaje = adcPromedio * (VREF / 1023.0);

  float anguloReal = 0.0;

  // Calibración por tramos:
  // 0.00V -> 0°
  // 1.11V -> 90°
  // 5.00V -> 180°
  if (voltaje <= 1.11) {
    anguloReal = (voltaje / 1.11) * 90.0;
  } else {
    anguloReal = 90.0 + ((voltaje - 1.11) / (5.0 - 1.11)) * 90.0;
  }

  if (anguloReal < 0) anguloReal = 0;
  if (anguloReal > 180) anguloReal = 180;

  int angulo = (int)(anguloReal + 0.5);

  lcd.setCursor(0, 0);
  lcd.print("Volt: ");
  lcd.print(voltaje, 2);
  lcd.print("V   ");

  lcd.setCursor(0, 1);
  lcd.print("Angulo: ");
  lcd.print(angulo);
  lcd.print((char)223);
  lcd.print("   ");

  delay(100);
}