#include "Protocentral_MAX30102.h"
#include <Wire.h>

MAX30100 sensor;  //attach sensor
uint8_t data_len=8;      
uint8_t DataPacketHeader[15];
volatile unsigned int IRR,REDD;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(10, INPUT); // Configuración para la detección LO + Para detectar fallas de desconexion o cables
  pinMode(11, INPUT); // Configuración para la detección LO -
  while(!Serial);
  sensor.begin(pw1600, i50, sr100 );
}

void loop() {
    sensor.readSensor();        //read sensor
    
    REDD=sensor.RED;  
    if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
Serial.println('!');
}
else{
// Imprimir la lectura del puerto 
IRR=analogRead(A0);  
}                       
    DataPacketHeader[0] = 0x0A;
    DataPacketHeader[1] = 0xFA;
    DataPacketHeader[2] = (uint8_t) (data_len);
    DataPacketHeader[3] = (uint8_t) (data_len>>8);
    DataPacketHeader[4] = 0x02;
    
 
    DataPacketHeader[5] = REDD;
    DataPacketHeader[6] = REDD>>8;
    DataPacketHeader[7] = REDD>>16;
    DataPacketHeader[8] = REDD>>24; 

    
    DataPacketHeader[9] = IRR;
    DataPacketHeader[10] = IRR>>8;
    DataPacketHeader[11] = IRR>>16;
    DataPacketHeader[12] = IRR>>24; 

    DataPacketHeader[13] = 0x00;
    DataPacketHeader[14] = 0x0b;

    for(int i=0; i<15; i++) // transmit the data
    {
       Serial.write(DataPacketHeader[i]);
     }

  delay(10);
}
