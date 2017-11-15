//---------------------------------------------------------------
#include <LiquidCrystal.h>
//---------------------------------------------------------------
#define MAX_X_LCD  16
#define MAX_Y_LCD  2
//---------------------------------------------------------------
#define pin_rs 8
#define pin_en 9
#define pin_d4 4
#define pin_d5 5
#define pin_d6 6
#define pin_d7 7
LiquidCrystal lcd(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7); 
//---------------------------------------------------------------
#define MAX_LEN 128

uint8_t input_buf[MAX_LEN];
int input_buf_index;
//---------------------------------------------------------------
int modbus_receive(void)
{
  uint8_t i;
  uint8_t s;

  input_buf_index = 0;
  while(true) 
  {
    if(!Serial.available()) 
    {
      i = 0;
      while (!Serial.available()) 
      {
        delay(1);
        if (++i == 10) 
        {
          /* Too late, bye */
          return -1;
        }
      }
    }
    s = Serial.read();
    if(s >= 0)
    {
      if(input_buf_index < MAX_LEN)
      {
        input_buf[input_buf_index] = s;
        input_buf_index++;
      }
    }
  }
  return input_buf_index;
}
//---------------------------------------------------------------
void clear(void)
{
  for(int n=0; n<MAX_LEN; n++)
  {
    input_buf[n] = 0;
  }
  input_buf_index = 0;
}
//---------------------------------------------------------------
void setup(void)
{
  lcd.begin(MAX_X_LCD, MAX_Y_LCD);
  lcd.clear();
  lcd.print("MODBUS RTU");

  Serial.begin(9600);
}
//---------------------------------------------------------------
// Compute the MODBUS RTU CRC
uint16_t ModRTU_CRC(unsigned char *buf, int len)
{
  unsigned short crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned short)buf[pos]; 

    for (int i = 8; i != 0; i--)
    {
      if ((crc & 0x0001) != 0)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
    }
  }
  return crc;
}
//---------------------------------------------------------------
void loop(void)
{
  bool ok = false;
  if(Serial.available()) 
  {
    clear();
    modbus_receive();

    lcd.clear();
    lcd.print(input_buf_index);
  }
}
//---------------------------------------------------------------

