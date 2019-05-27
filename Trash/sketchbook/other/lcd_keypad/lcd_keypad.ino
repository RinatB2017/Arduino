//---------------------------------------------------------------
#include <LiquidCrystal.h>
//---------------------------------------------------------------
enum {
  BTN_NO_PRESS = 0,
  BTN_UP,
  BTN_DOWN,
  BTN_LEFT,
  BTN_RIGHT,
  BTN_SELECT
};
//---------------------------------------------------------------
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//---------------------------------------------------------------
void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("LCD Key Shield");
  lcd.setCursor(0,1);
  //lcd.print("Press Key:");
  float x= 666.123456789f;
  lcd.print(x, 6);
  //lcd.print(x*1e6);
  //lcd.print((int)x);
  //lcd.print(".");
  //lcd.print((x - (int)x) * 1000000);
}
//---------------------------------------------------------------
int get_key(int data)
{
  if(data < 60)    return BTN_RIGHT;
  if(data < 200)  return BTN_UP;
  if(data < 400)  return BTN_DOWN;
  if(data < 600)  return BTN_LEFT;
  if(data < 800)  return BTN_SELECT;
  return BTN_NO_PRESS;
}
//---------------------------------------------------------------
void loop() 
{
  int x;
  x = analogRead (0);
  lcd.setCursor(10,1);
  switch(get_key(x))
  {
  case BTN_UP:        lcd.print ("Up    "); break;
  case BTN_DOWN:   lcd.print ("Down  "); break;
  case BTN_LEFT:      lcd.print ("Left  "); break;
  case BTN_RIGHT:    lcd.print ("Right "); break;
  case BTN_SELECT:  lcd.print ("Select"); break;
  default:
    break;
  }
}
//---------------------------------------------------------------
