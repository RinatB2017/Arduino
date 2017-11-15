#include <SimpleModbusMaster.h>

//////////////////// Port information ///////////////////
#define baud 9600
#define timeout 1000
#define polling 200 // the scan rate

#define retry_count 10

#define TxEnablePin 2 

#define LED 9

enum
{
  PACKET1,
  TOTAL_NO_OF_PACKETS
};

Packet packets[TOTAL_NO_OF_PACKETS];

packetPointer packet1 = &packets[PACKET1];

unsigned int readRegs[1];
unsigned int writeRegs[1];

void setup()
{
  modbus_construct(packet1, 
                    2, 
                    READ_HOLDING_REGISTERS, 
                    0, 
                    1, 
                    readRegs);

  modbus_configure(&Serial, 
                    baud, 
                    SERIAL_8N1, 
                    timeout, 
                    polling, 
                    retry_count, 
                    TxEnablePin, 
                    packets, 
                    TOTAL_NO_OF_PACKETS);

  pinMode(LED, OUTPUT);
}

void loop()
{
  modbus_update();

  writeRegs[0] = analogRead(A0); // update data to be written to arduino slave
  analogWrite(LED, readRegs[0]>>2); // constrain adc value from the arduino slave to 255
}

