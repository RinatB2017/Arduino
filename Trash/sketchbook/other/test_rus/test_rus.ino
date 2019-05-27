//---------------------------------------------------------------
#include <LiquidCrystal.h>
#include "simvols.h"
//---------------------------------------------------------------
struct PROTOCOL {
  uint8_t  begin_byte;
  uint8_t  command;
  uint16_t address;
  uint8_t  data;
  uint16_t checksum;
  uint8_t  end_byte;
};
//---------------------------------------------------------------
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//---------------------------------------------------------------
void test_rus(void)
{
  lcd.createChar(0, s0);
  lcd.setCursor(0, 0);  
  lcd.write(byte(0));

  lcd.createChar(1, s1);
  lcd.setCursor(1, 0);  
  lcd.write(byte(1));

  lcd.createChar(2, s2);
  lcd.setCursor(2, 0);  
  lcd.write(byte(2));

  lcd.createChar(3, s3);
  lcd.setCursor(3, 0);  
  lcd.write(byte(3));

  lcd.createChar(4, s4);
  lcd.setCursor(4, 0);  
  lcd.write(byte(4));

  lcd.createChar(5, s5);
  lcd.setCursor(5, 0);  
  lcd.write(byte(5));

  lcd.createChar(6, s6);
  lcd.setCursor(6, 0);  
  lcd.write(byte(6));

  lcd.createChar(7, s7);
  lcd.setCursor(7, 0);  
  lcd.write(byte(7));
}
//---------------------------------------------------------------
void setup(void)
{
  lcd.begin(16, 2);
  test_rus();
}
//---------------------------------------------------------------
void loop(void)
{

  
}
//---------------------------------------------------------------

