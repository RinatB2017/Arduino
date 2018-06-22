//---------------------------------------------------------------
#include <Wire.h>
//---------------------------------------------------------------
#define FM24C_WR_ADDR		0xA0	// write device-address 
#define FM24C_RD_ADDR		0xA1	// read device-address
//---------------------------------------------------------------
//   ok = I2C_Read(FM24C_WR_ADDR, address,   FM24C_RD_ADDR, &temp.bytes.a);
//---------------------------------------------------------------
char fram_read(uint16_t address)
{
  Wire.beginTransmission(FM24C_WR_ADDR);  // выбор адреса
  Wire.write(address >> 8);               // посылаем старший байт MSB адреса
  Wire.write(address & 0xFF);             // посылаем младший байт LSB адреса
  Wire.endTransmission();

  Wire.beginTransmission(FM24C_RD_ADDR);  // выбор адреса
  Wire.requestFrom(FM24C_RD_ADDR, 1);     // считываем один байт данных
  Wire.endTransmission();
  
  return Wire.read();
}
//---------------------------------------------------------------
//  ok = I2C_Write(FM24C_WR_ADDR, address,   temp.bytes.a);
//---------------------------------------------------------------
void fram_write(uint16_t address, uint8_t data)
{
  Wire.beginTransmission(FM24C_WR_ADDR);  // выбор адреса
  Wire.write(address >> 8);               // посылаем старший байт MSB адреса
  Wire.write(address & 0xFF);             // посылаем младший байт LSB адреса
  Wire.write(data);
  Wire.endTransmission();
}
//---------------------------------------------------------------
void write_all(void)
{
  Serial.println("Write FM24C16...");
  for(int n=0; n<10; n++)
  {
    fram_write(n, n);
  }
}
//---------------------------------------------------------------
void read_all(void)
{
  Serial.println("Read FM24C16...");
  for(int n=0; n<11; n++)
  {
    char c = fram_read(n);
    Serial.print("0x");
    Serial.print(c, HEX);
    Serial.print(",");
  }
  Serial.println();
}
//---------------------------------------------------------------
void setup()
{
  Wire.begin();        // подключение к шине i2c
  Serial.begin(9600);  // запуск последовательного порта

  write_all();
  read_all();
}
//---------------------------------------------------------------
void loop()
{  

}
//---------------------------------------------------------------


