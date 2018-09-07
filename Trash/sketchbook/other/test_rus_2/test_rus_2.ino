//---------------------------------------------------------------
#include <LiquidCrystal.h>
//---------------------------------------------------------------
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//---------------------------------------------------------------
void test_rus(void)
{
  for(int n=0; n<256; n++)
  {
    lcd.setCursor(0, 0);
    lcd.print(n);
    lcd.setCursor(0, 1);
    lcd.write((byte)n);
    delay(500);
  }
  lcd.setCursor(0, 0);
  lcd.print("The end!");
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
