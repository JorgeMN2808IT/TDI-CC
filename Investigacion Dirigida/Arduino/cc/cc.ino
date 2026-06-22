#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C de la pantalla.
// En físico muchas pantallas usan 0x27, pero en algunos simuladores puede ser 0x20.
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinAnalogico = A0;
const float VREF = 5.0;

// Rango real del potenciómetro
const float ANGULO_MAX = 270.0;

// Voltajes de calibración
const float VOLTAJE_MIN = 0.0;
const float VOLTAJE_MAX = 5.0;

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

  float anguloReal = (voltaje - VOLTAJE_MIN) * (ANGULO_MAX / (VOLTAJE_MAX - VOLTAJE_MIN));

  if (anguloReal < 0) {
    anguloReal = 0;
  }

  if (anguloReal > 270) {
    anguloReal = 270;
  }

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