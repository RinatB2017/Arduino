//---------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif 
//---------------------------------------------------------------
union GY_521
{
  struct {
    unsigned char address;
    float DEL;

    struct {
      float x;
      float y;
      float z;
    } ACC;
    struct {
      float x;
      float y;
      float z;
    } GYR;
    struct {
      float x;
      float y;
      float z;
    } FIL;    
  } body;
  unsigned char buf[sizeof(body)];
};
//---------------------------------------------------------------
void convert_data_to_ascii(unsigned char data)
{
  unsigned char hi = (data >> 4) & 0x0F;
  unsigned char lo = (data & 0x0F);

  switch(hi)
  {
  case 0x00: Serial.print("0"); break;
  case 0x01: Serial.print("1"); break;
  case 0x02: Serial.print("2"); break;
  case 0x03: Serial.print("3"); break;
  case 0x04: Serial.print("4"); break;
  case 0x05: Serial.print("5"); break;
  case 0x06: Serial.print("6"); break;
  case 0x07: Serial.print("7"); break;
  case 0x08: Serial.print("8"); break;
  case 0x09: Serial.print("9"); break;
  case 0x0A: Serial.print("A"); break;
  case 0x0B: Serial.print("B"); break;
  case 0x0C: Serial.print("C"); break;
  case 0x0D: Serial.print("D"); break;
  case 0x0E: Serial.print("E"); break;
  case 0x0F: Serial.print("F"); break;
  default: 
    break;
  }

  switch(lo)
  {
  case 0x00: Serial.print("0"); break;
  case 0x01: Serial.print("1"); break;
  case 0x02: Serial.print("2"); break;
  case 0x03: Serial.print("3"); break;
  case 0x04: Serial.print("4"); break;
  case 0x05: Serial.print("5"); break;
  case 0x06: Serial.print("6"); break;
  case 0x07: Serial.print("7"); break;
  case 0x08: Serial.print("8"); break;
  case 0x09: Serial.print("9"); break;
  case 0x0A: Serial.print("A"); break;
  case 0x0B: Serial.print("B"); break;
  case 0x0C: Serial.print("C"); break;
  case 0x0D: Serial.print("D"); break;
  case 0x0E: Serial.print("E"); break;
  case 0x0F: Serial.print("F"); break;
  default: 
    break;
  }
}
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
}
//---------------------------------------------------------------
GY_521 gy;

union FLOAT
{
  float value;
  struct
  {
    uint8_t d;
    uint8_t c;
    uint8_t b;
    uint8_t a;
  } bytes;
};
//---------------------------------------------------------------
void loop(void)
{
#if 0
  FLOAT f;
  f.value = 1.5f;
  Serial.print(f.bytes.a);
  Serial.print(" ");
  Serial.print(f.bytes.b);
  Serial.print(" ");
  Serial.print(f.bytes.c);
  Serial.print(" ");
  Serial.print(f.bytes.d);
  Serial.println();
#endif
  
#if 0  
  Serial.println(sizeof(float));
#endif  
  
#if 0  
  unsigned short x = 1;
  Serial.println((((unsigned char *) &x) == 0 ? "big-endian" : "little-endian"));
#endif  

#if 1  
  gy.body.address = 1;

  gy.body.DEL = 1.5f;

  gy.body.ACC.x = 1.0f;
  gy.body.ACC.y = 2.0f;
  gy.body.ACC.z = 3.0f;

  gy.body.GYR.x = 4.0f;
  gy.body.GYR.y = 5.0f;
  gy.body.GYR.z = 6.0f;

  gy.body.FIL.x = 7.0f;
  gy.body.FIL.y = 8.0f;
  gy.body.FIL.z = 9.0f;

  Serial.print(":");
  for(unsigned int n=0; n<sizeof(GY_521); n++)
  {
    convert_data_to_ascii(gy.buf[n]);
  }
  Serial.println();
#endif  

  delay(1000);
}
//---------------------------------------------------------------
















