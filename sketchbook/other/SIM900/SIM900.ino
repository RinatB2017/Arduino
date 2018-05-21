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
bool send_message(char *message)
{
  gprsSerial.println(message);
  //delay(100);

  int i = 0;
  while (!gprsSerial.available()) 
  {
    delay(1);
    if (++i == 1000) 
    {
      SIM900_Power();
      return false;
    }
  }
  while(gprsSerial.available())
    Serial.write(gprsSerial.read());

  return true;
}
//---------------------------------------------------------------
void loop()
{
  send_message("AT");
  send_message("AT+CMEE=2");
  send_message("AT+COPS=?");
  //send_message("AT+CPIN?");
  //send_message("AT+CGATT?");
  while(1)
  {
    
  }
#if 0  
  //if(send_message("ATD + +79182413874;"))
  if(send_message("ATD89182413874;"))
  {
    delay(1000);
    send_message("ATH");
    //while(1);
  }
#endif  

  delay(1000);
}
//---------------------------------------------------------------


