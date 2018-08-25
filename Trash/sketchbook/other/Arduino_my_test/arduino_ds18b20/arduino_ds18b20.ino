//--------------------------------------------------------------------------------
#include <OneWire.h>
//--------------------------------------------------------------------------------
// получаем температуру от DS18S20 
OneWire  ds(10);  // линия 1-Wire будет на pin 10
//--------------------------------------------------------------------------------
union TEMPERATURE
{
  unsigned short value;
  struct
  {
    unsigned bit_0: 1;
    unsigned bit_1: 1;
    unsigned bit_2: 1;
    unsigned bit_3: 1;
    unsigned bit_4: 1;
    unsigned bit_5: 1;
    unsigned bit_6: 1;
    unsigned bit_7: 1;
    unsigned bit_8: 1;
    unsigned bit_9: 1;
    unsigned bit_10: 1;
    unsigned bit_11: 1;
    unsigned bit_12: 1;
    unsigned bit_13: 1;
    unsigned bit_14: 1;
    unsigned bit_15: 1;
  } 
  bites;
};
//--------------------------------------------------------------------------------
float convert_9bit(unsigned short  temp_ds18b20)
{
  short temp;
  union TEMPERATURE temper;

  temp = temp_ds18b20 >> 3;

  temper.value = temp;

  int sign = 1;
  if(temper.bites.bit_8)
    sign = -1;

  if(temper.bites.bit_8)
    temp = (~temp + 1);
  temper.value = temp << 3;

  float value = 0;
  if(temper.bites.bit_7) value += pow(2, 3);
  if(temper.bites.bit_6) value += pow(2, 2);
  if(temper.bites.bit_5) value += pow(2, 1);
  if(temper.bites.bit_4) value += pow(2, 0);
  if(temper.bites.bit_3) value += pow(2, -1);
  if(temper.bites.bit_2) value += pow(2, -2);
  if(temper.bites.bit_1) value += pow(2, -3);
  if(temper.bites.bit_0) value += pow(2, -4);

  return (sign * value);
}
//--------------------------------------------------------------------------------
float convert_10bit(unsigned short temp_ds18b20)
{
  short temp;
  union TEMPERATURE temper;

  temp = temp_ds18b20 >> 2;

  temper.value = temp;

  int sign = 1;
  if(temper.bites.bit_9)
    sign = -1;

  if(temper.bites.bit_9)
    temp = (~temp + 1);
  temper.value = temp << 2;

  float value = 0;
  if(temper.bites.bit_8) value += pow(2, 4);
  if(temper.bites.bit_7) value += pow(2, 3);
  if(temper.bites.bit_6) value += pow(2, 2);
  if(temper.bites.bit_5) value += pow(2, 1);
  if(temper.bites.bit_4) value += pow(2, 0);
  if(temper.bites.bit_3) value += pow(2, -1);
  if(temper.bites.bit_2) value += pow(2, -2);
  if(temper.bites.bit_1) value += pow(2, -3);
  if(temper.bites.bit_0) value += pow(2, -4);

  return (sign * value);
}
//--------------------------------------------------------------------------------
float convert_11bit(unsigned short temp_ds18b20)
{
  short temp;
  union TEMPERATURE temper;

  temp = temp_ds18b20 >> 1;

  temper.value = temp;

  int sign = 1;
  if(temper.bites.bit_10)
    sign = -1;

  if(temper.bites.bit_10)
    temp = (~temp + 1);
  temper.value = temp << 1;

  float value = 0;
  if(temper.bites.bit_9) value += pow(2, 5);
  if(temper.bites.bit_8) value += pow(2, 4);
  if(temper.bites.bit_7) value += pow(2, 3);
  if(temper.bites.bit_6) value += pow(2, 2);
  if(temper.bites.bit_5) value += pow(2, 1);
  if(temper.bites.bit_4) value += pow(2, 0);
  if(temper.bites.bit_3) value += pow(2, -1);
  if(temper.bites.bit_2) value += pow(2, -2);
  if(temper.bites.bit_1) value += pow(2, -3);
  if(temper.bites.bit_0) value += pow(2, -4);

  return (sign * value);
}
//--------------------------------------------------------------------------------
float convert_12bit(unsigned short temp_ds18b20)
{
  unsigned short temp;
  union TEMPERATURE temper;

  temp = temp_ds18b20;

  temper.value = temp;

  int sign = 1;
  if(temper.bites.bit_11)
    sign = -1;

  if(temper.bites.bit_11)
    temp = (~temp + 1);
  temper.value = temp;

  float value = 0;
  if(temper.bites.bit_10) value += pow(2, 6);
  if(temper.bites.bit_9)  value += pow(2, 5);
  if(temper.bites.bit_8)  value += pow(2, 4);
  if(temper.bites.bit_7)  value += pow(2, 3);
  if(temper.bites.bit_6)  value += pow(2, 2);
  if(temper.bites.bit_5)  value += pow(2, 1);
  if(temper.bites.bit_4)  value += pow(2, 0);
  if(temper.bites.bit_3)  value += pow(2, -1);
  if(temper.bites.bit_2)  value += pow(2, -2);
  if(temper.bites.bit_1)  value += pow(2, -3);
  if(temper.bites.bit_0)  value += pow(2, -4);

  return (sign * value);
}
//--------------------------------------------------------------------------------
void setup(void) 
{
  Serial.begin(9600);
}
//--------------------------------------------------------------------------------
void loop(void) 
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  if ( !ds.search(addr)) {
    //Serial.println("No more addresses.");
    ds.reset_search();
    return;
  }


  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.print("CRC is not valid!\n");
    return;
  }

  if ( addr[0] != 0x28) {
    Serial.print("R=");
    for( i = 0; i < 8; i++) {
      Serial.print(addr[i], HEX);
      Serial.print(" ");
    }
    Serial.print("Device is not a DS18S20 family device.\n");
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // запускаем конвертацию

  delay(1000);     // скорее всего достаточно 750ms 
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // считываем ОЗУ датчика

  for ( i = 0; i < 9; i++) {           // обрабатываем 9 байт
    data[i] = ds.read();
  }

  // высчитываем температуру :)
  int HighByte, LowByte, TReading;
  float Tc_100;
  LowByte  = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte; 
  Tc_100 = convert_12bit(TReading);

  //Serial.print("LB= ");
  //Serial.print(LowByte,HEX);
  //Serial.print(" HB= ");
  //Serial.print(HighByte,HEX);
  Serial.print(" T = ");
  Serial.print(Tc_100);
  Serial.println();
}
//--------------------------------------------------------------------------------



