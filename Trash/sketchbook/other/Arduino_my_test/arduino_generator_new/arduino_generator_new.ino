//---------------------------------------------------------------
union DECADES
{
  int16_t value;
  struct
  {
    unsigned a: 4;
    unsigned b: 4;
    unsigned c: 4;
    unsigned d: 4;
  } 
  decades;
};

int16_t e_data = 0;
//---------------------------------------------------------------
char convert_to_char(uint8_t data)
{
  char temp = 0;
  switch(data)
  {
    case 0x00: temp='0'; break;
    case 0x01: temp='1'; break;
    case 0x02: temp='2'; break;
    case 0x03: temp='3'; break;
    case 0x04: temp='4'; break;
    case 0x05: temp='5'; break;
    case 0x06: temp='6'; break;
    case 0x07: temp='7'; break;
    case 0x08: temp='8'; break;
    case 0x09: temp='9'; break;
    case 0x0A: temp='A'; break;
    case 0x0B: temp='B'; break;
    case 0x0C: temp='C'; break;
    case 0x0D: temp='D'; break;
    case 0x0E: temp='E'; break;
    case 0x0F: temp='F'; break;
    default:   temp='0'; break;
  }
  return temp;
}
//---------------------------------------------------------------
void send_u16(int16_t data)
{
  union DECADES temp;
  
  temp.value = data;
  
  Serial.print(convert_to_char(temp.decades.d));
  Serial.print(convert_to_char(temp.decades.c));
  Serial.print(convert_to_char(temp.decades.b));
  Serial.print(convert_to_char(temp.decades.a));
}
//---------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);
  //Serial.begin(9600);
}
//---------------------------------------------------------------
void loop() 
{
  //y[n] = double(308.0)*qSin(double(n)*double(M_PI)/double(180.0));;
  Serial.print(':');
  for(int n=0; n<20; n++)
  {
    send_u16(double(308.0)*sin(double(e_data)*double(3.14159265)/double(180.0))+0.5f);
    e_data++;
  }
  Serial.write(0x0A);
  delay(50);
}
//---------------------------------------------------------------

