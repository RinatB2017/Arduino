#include <SoftwareSerial.h>
//---------------------------------------------------------------
SoftwareSerial gprsSerial(2, 3);
int ResetPin = 8;
//---------------------------------------------------------------
void SIM900_Power(void)
{
  //Serial.println("SIM900_Power");
  digitalWrite(ResetPin, HIGH);
  delay(1000);
  digitalWrite(ResetPin, LOW);
}
//---------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  //Serial.println("AltSoftSerial Test Begin");

  gprsSerial.begin(9600);
  pinMode(ResetPin, OUTPUT); 
  //Serial.println("Test begin");
  SIM900_Power();
}
//---------------------------------------------------------------
void loop() 
{
  char c;

  if (Serial.available()) 
  {
    c = Serial.read();
    gprsSerial.print(c);
  }
  if (gprsSerial.available()) 
  {
    c = gprsSerial.read();
    Serial.print(c);
  }
}
//---------------------------------------------------------------

