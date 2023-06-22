# Proyecto AquaBloom Pot
Proyecto de riego automático para Electrónica Digital I

### Austral - Electronica Digital - 2023 - EAM


## Secciones

- [Objetivo](#objetivo)
- [Hardware](#hardware)
- [Programa](#programa)
- [platformio.ini](#platformio.ini)
- [Biblioteca](#biblioteca)
- [Constantes](#constantes)


## Objetivo

>   Armar un riego automatico registrando valores de humedad y temperatura
>   Crear una página de Web residente en el ESP32, y mediante la misma, se podrá ver los valores de humedad y temperatura de la planta
>   Ademas de poder modificar la humedad critica en la pagina Web, que indicara cuando se abrira el gotero   

## Hardware

  1 YL69 (Sensor de humedad)
  1 DS18B20 (Sensor de temperatura)
  1 Resistor de 4700 ohm
  1 SG-5010 (Servo de 180 grados)
  1 SSD1306 (Pantalla OLED)
  Jumper wires

  Sensor de Humedad:
    Conectar VCC a 5V
    Conectar GND a GND
    Conectar A0 a GPIO "HUMIDITYPIN" (32)

  Sensor de Temperatura:
    Conectar VCC a 5V
    Conectar GND a GND
    Conectar DQ a GPIO "TEMPERATUREPIN" (4)
    Conectar DQ a la resitencia de 4700 ohm a 5V

  Pantalla OLED:
    Conectar VCC a 5V
    Conectar GND a GND
    Conectar SCL a GPIO 22
    Conectar SDA a GPIO 21

  Servo:
    Conectar VCC a 5V
    Conectar GND a GND
    Conectar SIGNAL a GPIO "SERVOPIN" (32)
    

## Programa

 El programa es una modificación respecto a los proyectos _05-servo_main_ y del proyecto _ Update WebPageUpdate.ino_ del autor _KrisKasprzak_.    

   

 Creación de objetos:  
   (45) _display_ de tipo Adafruit_SSD1306 con las varaibles (ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
   (46) _oneWireObjeto_ de tipo OneWire con la variable (TEMPERATUREPIN)
   (47) _sensorDS18B20_ de tipo DallasTemperature con la instancia (&oneWireObjeto)
   (48) _servo_ de tipo Servo
   (49) _server_ de tipo _WiFiServer_ en port 80  

 Definiciones: 
   (24) Define _state_ de tipo _bool_ para indicar si el estado del servo esta abierto o cerrado  
   (25) Define _criticalh_ de tipo _int_ para almacenar el valor de humandad donde el Servo se abre
   (27) Define _temperature_ de tipo _float_ para almacenar los valores de temperatura
   (28) Define _humidity_ de tipo _float_ para almacenar los valores de humedad 
   

 [-] Funciones privadas del módulo: 
    Funciones de sensores:
        (54-88) _StartSensors()_: Iniciliza los sensores de humedad y de temperatura
        (60-63) _readTemperature()_: Retorna el float de temperatura en Celsius 
        (65-68) _readHumidity()_: Retorna float de analog del sensor de humedad
        (70-90) _analyze()_: Obtiene los valores de humedad y humedad critica y verifica si el Servo debe estar abierto o cerrado.
   Funciones de Servo:
        (93-97) _StartServo()_: Inicializa el servo y lo pone en 0 grados, es decir cerrado.
        (99-101) _check_state()_: Retorna un bool sobre el estado del Servo
        (103-108) _open()_: Abre el Servo, lo pone en 180 grados.
        (110-115) _close()_: Cierra el Servo, lo pone en 0 grados.
    Funciones de OLED:
        (119-127) _StartOLED()_: Inicializa la pantalla, muestra el logo de Arduino.
        (129-146) _OLEDdisplay()_: Envia a la pantalla los valores de temperatura y de humedad.
    Funciones de Servidor:
        (149-161) _UpdateSlider()_: Manega la barra de la pagina web que controla el valor critico de humedad.
        (163-168) _SendWebsite()_: Envia la pagina web al dispositivo que se concecta.
        (170-192) _SendXML()_: Envia los valores de humedad, temperatura y estado del servo.
        (194-212) _printWifiStatus()_: Muetra la dirección IP donde se accedera a la pagina Web.

 [-] Funciones públicas del módulo  
  [-] Función _setup_  
   Inicializa _Serial_  
   Inicializar la pantalla con StartOLED();
   Inicializar ambos sensores con StartSensors(); 
   Inicializar el Servo con StartServo(); 
   Se inicializa el Wifi con LOCAL_SSID y LOCAL_PASS 
   Se inicializa el servidor  

  [-] Función _loop_  
   Se registra los valores de los sensores de temperatura y humedad
   Se envia los valores de temperatura y de humedad a la pantalla OLED
   Se analiza los valores de humedad con analize(); y se abre o se cierra el Servo
   Se maneja el servidor server.handleClient();


## platformio.ini
   Se definen seis constantes:
   _TEMPERATUREPIN_: define en qué GPIO está conectado el sensor de temperatura
   _HUMIDITYPIN_: define en qué GPIO está conectado el sensor de humedad
   _SERVOPIN_: define en qué GPIO está conectado al Servo
   _ANCHO_PANTALLA_: define el ancho de la pantalla OLED
   _ALTO_PANTALLA_: define el alto de la pantalla OLED
   _SERIAL_BAUD_: define el baud rate de la conexión serie haciendola igual a _monitor_speed_    


## Biblioteca

    Se necesitan estas librerias externas:
    Pantalla OLED:
        _SPI.h_
        _Wire.h_
        _Adafruit_GFX.h_
        _Adafruit_SSD1306.h_
    
    Sensor de temperatura:
        _OneWire.h_
        _DallasTemperature.h_
    
    Servo:
        _Servo.h_
    
    Matematicas:
        _cmath_

    Las librerias de Arduino utilizadas para el Servidor son:
        _WiFi.h_
        _WebServer.h_
        _"WebPage.h"_

## Constantes

   Las declaradas en _platformio.ini_


