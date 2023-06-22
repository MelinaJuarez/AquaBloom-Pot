#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OLED.h"
#include <Arduino.h>

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

OLED::OLED(){}


void OLED::StartOLED() {
  delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  // Enviar a pantalla
  display.display();
}

void OLED::displayHT(float temperature, float humidity) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  // Texto a imprimir
  // Para temperatura
  display.setCursor(1, 5);
  char tem[100];
  sprintf(tem, "Temperature: %.1f", temperature);
  display.printf(tem);
  // Para humedad
  display.setCursor(1, 20);
  char hum[100];
  sprintf(hum, "Humidity: %.2f %", humidity);
  display.printf(hum);
  // Enviar a pantalla
  display.display();
}

