#include <AltSoftSerial.h>

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12

AltSoftSerial altSerial;
//#define SPEED  38400
#define SPEED  9600
void setup() 
{
  Serial.begin(SPEED);
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(SPEED);
  //altSerial.println("Hello World");

#if 0
  pinMode(10, OUTPUT); 
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(10, LOW);
#endif  
}

void loop() 
{
  char c;

  if (Serial.available()) 
  {
    c = Serial.read();
    altSerial.print(c);
  }
  if (altSerial.available()) 
  {
    c = altSerial.read();
    Serial.print(c);
  }
}




