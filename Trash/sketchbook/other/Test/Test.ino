//---------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
//---------------------------------------------------------------
bool flag = false;
int led = 13;
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
//---------------------------------------------------------------
void loop(void)
{
  Serial.println("update");
  digitalWrite(led, flag ? HIGH : LOW);
  flag = !flag;
  delay(1000);
}
//---------------------------------------------------------------



