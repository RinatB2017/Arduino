#include <SoftwareSerial.h>
//---------------------------------------------------------------
SoftwareSerial gprsSerial(2, 3);
int ResetPin = 8;
//---------------------------------------------------------------
// software equivalent of pressing the GSM shield "power" button
void SIM900_Power(void)
{
  Serial.println("SIM900_Power");
  digitalWrite(ResetPin, HIGH);
  delay(1000);
  digitalWrite(ResetPin, LOW);
}
//---------------------------------------------------------------
void setup()
{
  // GPRS Shield общается по умолчанию на скорости 19200 бод
  gprsSerial.begin(19200);
  Serial.begin(9600);

  pinMode(ResetPin, OUTPUT); 
  Serial.println("Test begin");
  SIM900_Power();
}
//---------------------------------------------------------------
void loop()
{
  if(gprsSerial.available())
    Serial.write(gprsSerial.read());
  if(Serial.available())
    gprsSerial.write(Serial.read());
}
//---------------------------------------------------------------


