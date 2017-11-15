//---------------------------------------------------------------
#define pin0  52
#define pin1  50
#define pin2  48
#define pin3  46
#define pin4  44
#define pin5  42
#define pin6  40
#define pin7  38
//---------------------------------------------------------------
union DATA_BYTE {
  uint8_t value;
  struct {
unsigned bit0  :1;
unsigned bit1  :1;
unsigned bit2  :1;
unsigned bit3  :1;
unsigned bit4  :1;
unsigned bit5  :1;
unsigned bit6  :1;
unsigned bit7  :1;
  } 
  bites;
};
//---------------------------------------------------------------
void setup(void)
{
  pinMode(pin0, OUTPUT); 
  pinMode(pin1, OUTPUT); 
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT); 
  pinMode(pin5, OUTPUT); 
  pinMode(pin6, OUTPUT); 
  pinMode(pin7, OUTPUT); 
}
//---------------------------------------------------------------
void draw(uint8_t data)
{
  union DATA_BYTE b;
  b.value = data;
  digitalWrite(pin0, b.bites.bit0);
  digitalWrite(pin1, b.bites.bit1);
  digitalWrite(pin2, b.bites.bit2);
  digitalWrite(pin3, b.bites.bit3);
  digitalWrite(pin4, b.bites.bit4);
  digitalWrite(pin5, b.bites.bit5);
  digitalWrite(pin6, b.bites.bit6);
  digitalWrite(pin7, b.bites.bit7);
}
//---------------------------------------------------------------
void loop(void)
{
  draw(0x55);
  delay(500);
  draw(0xAA);
  delay(500);
}
//---------------------------------------------------------------

