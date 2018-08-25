//-------------------------------------------------------
#define SDIO 8
#define SCLK 9
//-------------------------------------------------------
int i = 0;
//-------------------------------------------------------
byte DriverRead(byte address) 
{
  pinMode (SDIO, OUTPUT);
  for (byte i=128; i >0 ; i >>= 1) 
  {
    digitalWrite (SCLK, LOW);
    delayMicroseconds(10);
    digitalWrite (SDIO, (address & i) != 0 ? HIGH : LOW);
    delayMicroseconds(10);
    digitalWrite (SCLK, HIGH);
    delayMicroseconds(10);
  }
  delayMicroseconds(120);
  pinMode (SDIO, INPUT);
  byte res = 0;
  for (byte i=128; i >0 ; i >>= 1) 
  {
    digitalWrite (SCLK, LOW);
    delayMicroseconds(10);
    digitalWrite (SCLK, HIGH);
    delayMicroseconds(10);
    if( digitalRead (SDIO) == HIGH )
    {
      res |= i;
    }
  }
  delayMicroseconds(100);
  return res;
}
//-------------------------------------------------------
void DriverWrite(byte address, byte data) 
{
  address |= 0x80;
  pinMode (SDIO, OUTPUT);
  for (byte i = 128; i > 0 ; i >>= 1) 
  {
    digitalWrite (SCLK, LOW);
    delayMicroseconds(10);
    digitalWrite (SDIO, (address & i) != 0 ? HIGH : LOW);
    delayMicroseconds(10);    
    digitalWrite (SCLK, HIGH);
    delayMicroseconds(10);
  }
  delayMicroseconds(120);
  for (byte i = 128; i > 0 ; i >>= 1) 
  {
    digitalWrite (SCLK, LOW);
    delayMicroseconds(10);
    digitalWrite (SDIO, (data & i) != 0 ? HIGH : LOW);
    delayMicroseconds(10);
    digitalWrite (SCLK, HIGH);
    delayMicroseconds(10);
  }
  delayMicroseconds(100);
}
//-------------------------------------------------------
void DriverInit() 
{
  pinMode(SCLK, OUTPUT);
  pinMode(SDIO, OUTPUT);
  digitalWrite(SCLK, HIGH);
  delayMicroseconds(5);
  digitalWrite(SCLK, LOW);
  delayMicroseconds(1);
  digitalWrite(SCLK, HIGH);
  delay(1025);
  DriverWrite(0x00, 0x01);
  delay(3000);
}
//-------------------------------------------------------
int DriverReadFrame(byte *arr, int len)
{
  byte *pos=arr;
  byte *uBound=arr+len;
  unsigned long timeout = millis() + 1000;
  byte val;
  DriverWrite(0x08, 0x2A);
  while( millis() < timeout && pos < uBound)
  {
    val = DriverRead(0x08);

    //Only bother with the next bit if the pixel data is valid.
    if( !(val & 64) )
    {
      continue;
    }
    //If we encounter a start-of-field indicator, and the cursor isn't at the first pixel, then stop. ('Cause the last pixel was the end of the frame.)
    if( ( val & 128 )  &&  ( pos != arr) )
    {
      break;
    }
    *pos = val & 63;
    pos++;
  }
  return (pos-arr);
}
//-------------------------------------------------------
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
    default: break;
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
    default: break;
    }
}
//-------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  DriverInit();
}
//-------------------------------------------------------
void loop() 
{
  byte tmp[324];
#if 1  
  int len = DriverReadFrame(tmp,324);
#else
  for(int n=0; n<324; n++)
  {
    tmp[n] = i++;
  }
  int len = 324;
#endif  

  Serial.print(":");
  for(int i=0;i<len;i++)
  {
    convert_data_to_ascii(tmp[i]);
  }
  Serial.println();
}
//-------------------------------------------------------
