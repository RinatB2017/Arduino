//-------------------------------------------------------
int val_U = 0;
int val_I = 0;
//-------------------------------------------------------
union SHORT {
  unsigned short value;
  struct {
    unsigned char a;
    unsigned char b;
  } bytes;
};
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
}
//-------------------------------------------------------
void loop()
{
  val_U = analogRead(A1);
  val_I = analogRead(A0);

  SHORT data;
  Serial.print(":");
  data.value = val_U;
  convert_data_to_ascii(data.bytes.b);
  convert_data_to_ascii(data.bytes.a);
  
  data.value = val_I;
  convert_data_to_ascii(data.bytes.b);
  convert_data_to_ascii(data.bytes.a);
  Serial.println();
}
//-------------------------------------------------------

