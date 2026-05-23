#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// En tu simulador la pantalla está en 0x20
LiquidCrystal_I2C lcd(0x20, 16, 2);

const int pinAnalogico = A0;
const float VREF = 5.0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);
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