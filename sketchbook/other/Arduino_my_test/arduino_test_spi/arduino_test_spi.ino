//---------------------------------------------------------------
#include <SPI.h>
//---------------------------------------------------------------
uint8_t data = 0;
const int ssPin = 10;
//---------------------------------------------------------------
void setup(void)
{
  pinMode(ssPin, OUTPUT);

  Serial.begin(9600);
  //SPI.setBitOrder(LSBFIRST);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(64);
  //SPI.setDataMode(SPI_MODE0);
  //SPI.setDataMode(SPI_MODE1);
  //SPI.setDataMode(SPI_MODE2);
  //SPI.setDataMode(SPI_MODE3);
}
//---------------------------------------------------------------
void write_to_SPI(uint8_t data)
{
  SPI.begin();

  digitalWrite(ssPin, LOW);
  SPI.transfer(data);
  digitalWrite(ssPin, HIGH);

  SPI.end();
}
//---------------------------------------------------------------
void loop(void)
{
#if 0  
  if (Serial.available()) 
  {
    // read the incoming byte:
    data = Serial.read();
    write_to_SPI(data);  
  }
#else
  write_to_SPI(data);
  delay(1000);
  //Serial.println(data);
  data+=10;
#endif 
}
//---------------------------------------------------------------



