//---------------------------------------------------------------
#define MAX_DATA 50
union DATA
{
  struct {
    unsigned short reg_0;
    unsigned short reg_1;
    unsigned short reg_2;
    unsigned short reg_3;
  }
  data;
  unsigned char buf[sizeof(data)];
};
union PROTO
{
  struct {
    unsigned char  begin_byte;
    union DATA     regs[MAX_DATA];
    unsigned char  end_byte;
  } 
  data;
  unsigned char buf[sizeof(data)];
};
//---------------------------------------------------------------
unsigned char ascii_to_hex(unsigned char value)
{
  unsigned char temp;
  switch(value)
  {
  case 0x00: 
    temp = '0';  
    break;
  case 0x01: 
    temp = '1';  
    break;
  case 0x02: 
    temp = '2';  
    break;
  case 0x03: 
    temp = '3';  
    break;
  case 0x04: 
    temp = '4';  
    break;
  case 0x05: 
    temp = '5';  
    break;
  case 0x06: 
    temp = '6';  
    break;
  case 0x07: 
    temp = '7';  
    break;
  case 0x08: 
    temp = '8';  
    break;
  case 0x09: 
    temp = '9';  
    break;
  case 0x0A: 
    temp = 'A';  
    break;
  case 0x0B: 
    temp = 'B';  
    break;
  case 0x0C: 
    temp = 'C';  
    break;
  case 0x0D: 
    temp = 'D';  
    break;
  case 0x0E: 
    temp = 'E';  
    break;
  case 0x0F: 
    temp = 'F';  
    break;
  default:  
    temp = value;
    break;
  }
  return temp;
}
//---------------------------------------------------------------
void print_byte(unsigned char x)
{
  unsigned char a = (x & 0xF0) >> 4;
  unsigned char b = (x & 0x0F);
  Serial.write(ascii_to_hex(a));
  Serial.write(ascii_to_hex(b));
}
//---------------------------------------------------------------
void print_short(unsigned short x)
{
  unsigned char a = (x & 0xFF00) >> 8;
  unsigned char b = (x & 0x00FF);
  print_byte(a);
  print_byte(b);
}
//---------------------------------------------------------------
union PROTO proto;

void setup(void)
{
  Serial.begin(115200);

  //unsigned short x = 1;
  //Serial.print(((unsigned char *) &x) == 0 ? "big-endian" : "little-endian");
}
//---------------------------------------------------------------
void loop(void)
{
#if 1
  union PROTO proto;

  proto.data.begin_byte = ':';
  for(int n=0; n<MAX_DATA; n++)
  {
    proto.data.regs[n].data.reg_0 = analogRead(A0);
    proto.data.regs[n].data.reg_1 = analogRead(A1);
    proto.data.regs[n].data.reg_2 = analogRead(A2);
    proto.data.regs[n].data.reg_3 = analogRead(A3);
  }
  proto.data.end_byte = '\n';

  Serial.write(proto.data.begin_byte);
  for(int n=0; n<sizeof(PROTO) - 2; n++)
  {
    print_byte(proto.buf[n]);
  }
  Serial.write(proto.data.end_byte);
  //delay(100);
#endif  
}
//---------------------------------------------------------------














