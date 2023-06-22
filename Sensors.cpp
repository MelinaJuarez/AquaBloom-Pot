#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Sensors.h"


 
// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(DS18B20PIN);
DallasTemperature sensorDS18B20(&oneWireObjeto);


bool state;
extern float criticalh;
float temperature = 0;
float humidity = 0;

Sensors::Sensors(){}

float sensorValue;

void Sensors::StartSensors(){
  Serial.begin(SERIAL_BAUD);
  sensorDS18B20.begin();
  pinMode(HUMIDITYPIN, INPUT);
}

float Sensors::readTemperature(){
  sensorDS18B20.requestTemperatures();
  return sensorDS18B20.getTempCByIndex(0);
}

float Sensors::readHumidity(){
  float value = analogRead(HUMIDITYPIN);
  return value;
}

bool Sensors::analyze(){
  humidity = (((readHumidity()/4095)*100)-100)*(-1);
  if(humidity >= criticalh){
      Serial.println(" - Doesn't need watering.");
      state = false;
      return state;
  } else if (state)
  {
    if (humidity >= criticalh*1.2){
      state = false;
      return state;
    } else {
        return state;
      }
  } else
  {
    Serial.println(" - Time to water your plant.");
    state = true;
    return state;
  }
    
}




