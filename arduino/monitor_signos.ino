#include "Protocentral_MAX30102.h"
#include <Wire.h>
#include <OneWire.h>  
#include <DallasTemperature.h>
#include<SoftwareSerial.h>

OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
MAX30100 sensor;  //attach sensor
volatile unsigned int IRR,REDD,ECG,TEMP;
unsigned int average_value[60];
int i = 0;
long lastDebounceTime = 0;
long debounceDelay = 300;
long counter = 0;
SoftwareSerial BT(11,10);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

void setup() {
  Wire.begin();
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(10, INPUT); // Configuración para la detección LO + Para detectar fallas de desconexion o cables
  pinMode(11, INPUT); // Configuración para la detección LO -
  while(!Serial);
  sensor.begin(pw1600, i50, sr100 );
  sensors.begin();   //Se inicia el sensor
}

void loop() {
     float sum = 0.0;
     float bpm = 0.0;
    sensor.readSensor();        //read sensor
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    //float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
    REDD=sensor.RED;  
    IRR=sensor.IR;
if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
ECG=0;
}
else{
ECG=analogRead(A0); 
if ((millis() - lastDebounceTime) > debounceDelay){
      average_value[i] = analogRead(A0);
      i++;
      
      if (i >= 30){
        for (int j = 0; j < 60; j++){
          sum = sum + average_value[j];
          if (average_value[j] > 370){
            Serial.println(average_value[j]);
          }
          
        }
        bpm = sum/60.0;

        i = 0;
      }
    }
  }
  TEMP=sensors.getTempCByIndex(0);
  BT.println(REDD);
  BT.println(IRR);
  BT.println(ECG);
  BT.println(bpm);
  BT.println(TEMP);
                  
    

  delay(10);
}
