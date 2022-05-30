#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(11,10);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

uint8_t data_len=20;      
uint8_t DataPacketHeader[27];
volatile unsigned int IRR,REDD,ECG,TEMP,BPM;
void setup() {
 BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)velocidad= 38400
 Serial.begin(9600);   // Inicializamos  el puerto serie 
}

void loop() {

  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    REDD = BT.read();
    IRR = BT.read();
    ECG = BT.read();
    BPM = BT.read();
    TEMP = BT.read();
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
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
    
    DataPacketHeader[13] = ECG;
    DataPacketHeader[14] = ECG>>8;
    DataPacketHeader[15] = ECG>>16;
    DataPacketHeader[16] = ECG>>24;

    DataPacketHeader[17] = BPM;
    DataPacketHeader[18] = BPM>>8;
    DataPacketHeader[19] = BPM>>16;
    DataPacketHeader[20] = BPM>>24;
    
    DataPacketHeader[21] = BPM;
    DataPacketHeader[22] = BPM>>8;
    DataPacketHeader[23] = BPM>>16;
    DataPacketHeader[24] = BPM>>24;

    DataPacketHeader[25] = 0x00;
    DataPacketHeader[26] = 0x0b;

    for(int i=0; i<27; i++) // transmit the data
    {
       Serial.write(DataPacketHeader[i]);
     }
}
