//---------------------------------------------------------------
#include <LiquidCrystal.h>
//---------------------------------------------------------------
#define MAX_X_LCD  16
#define MAX_Y_LCD  2
//---------------------------------------------------------------
#define pin_rs  8
#define pin_en 9
#define pin_d4 4
#define pin_d5 5
#define pin_d6 6
#define pin_d7 7
LiquidCrystal lcd(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7); 
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//---------------------------------------------------------------
void setup(void)
{
  lcd.begin(MAX_X_LCD, MAX_Y_LCD);
}
//---------------------------------------------------------------
void loop(void)
{
  lcd.clear();
  lcd.print("Hello, world!");
  delay(1000);  
}
//---------------------------------------------------------------

