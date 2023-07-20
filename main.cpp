#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>       

#include "WebPage.h"
#include "OLED.h"
#include "Sensors.h"
#include "ServoMotor.h"


// Crear definiciones
float criticalh = 20; 

// Definicones para la web
WebServer server(80);


// Crear instancias de las clases
OLED oled;
Sensors sensors;
ServoMotor servoMotor;


boolean state = servoMotor.check_state(); 
float temperature = sensors.readTemperature();
float humidity = sensors.readHumidity();

// wifi part:
// definitions of your desired intranet created by the ESP32
IPAddress PageIP(190, 105, 55, 241);
IPAddress gateway(190, 105, 55, 241);
IPAddress subnet(255, 255, 255, 0);
IPAddress Actual_IP;
IPAddress ip;


#define LOCAL_SSID "34144a"
#define LOCAL_PASS "100114413"
#define AP_SSID "TestWebSite"
#define AP_PASS "023456789"

char XML[2048];
char buf[32];
int HumidityBar = 0;


void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);

}

// code to send the main web page
void SendXML() {

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  // send humidity
  sprintf(buf, "<B0>%d.%d</B0>\n", (int) (humidity), abs((int) (humidity * 10)  - ((int) (humidity) * 10)));
  strcat(XML, buf);
  // send temperature
  sprintf(buf, "<B1>%d.%d</B1>\n", (int) (temperature), abs((int) (temperature * 10)  - ((int) (temperature) * 10)));
  strcat(XML, buf);

      
  if (state) {
    strcat(XML, "<SWITCH>1</SWITCH>\n");
  }
  else {
    strcat(XML, "<SWITCH>0</SWITCH>\n");
  }

  strcat(XML, "</Data>\n");
  server.send(200, "text/xml", XML);


}

void printWifiStatus() {

  // imprime el SSID de la red a la que estás conectado:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // imprime la dirección IP de tu escudo WiFi:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // imprime la intensidad de la señal recibida:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}

void UpdateSlider() {
  String t_state = server.arg("VALUE");
  criticalh = t_state.toInt();
  
  //Para enviar algo a la página web, básicamente para mantenerla activa
  int ch = criticalh;
  strcpy(buf, "");
  sprintf(buf, "%d", ch);
  sprintf(buf, buf);

  
  server.send(200, "text/plain", buf); 
    
}

void setup() {
  Serial.begin(SERIAL_BAUD);

  // Inicializar la pantalla OLED
  Serial.println("Inicializado OLED");
  oled.StartOLED();

  // Inicializar los sensores
  Serial.println("Inicializado Sensores");
  sensors.StartSensors();

  // Inicializar el servo motor
  Serial.println("Inicializado Servo");
  servoMotor.StartServo();

  // Inicializar el servidor
  disableCore0WDT();
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
  printWifiStatus();
  server.on("/", SendWebsite);
  server.on("/xml", SendXML);
  server.on("/UPDATE_SLIDER", UpdateSlider);

  server.begin();

}


void loop() {
  // Leer valores de los sensores
  float temperature = sensors.readTemperature();
  float humidity = sensors.readHumidity();

  // Mostrar los valores en la pantalla OLED
  oled.displayHT(humidity, temperature);

  // Analizar los valores y controlar el servo motor
  bool needsWatering = sensors.analyze();
  if (needsWatering && !state) { // Se abre si se necesita agua y está cerrado
    servoMotor.open();
  } else {
    if (state){ // se cierra si ya estaba abierto de antes    
      servoMotor.close();
      }
  }
  server.handleClient();
  delay(5000); // Esperar 5 segundos antes de realizar la siguiente iteración

}



