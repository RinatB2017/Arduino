//---------------------------------------------------------------
#include <PCD8544.h>
//---------------------------------------------------------------
#define PCD8544_DATA HIGH
//---------------------------------------------------------------
// The dimensions of the LCD (in pixels)...
static const byte LCD_WIDTH = 84;
static const byte LCD_HEIGHT = 48;
static const int MAX_BUF = LCD_WIDTH * LCD_HEIGHT / 8;
//---------------------------------------------------------------
char buf[MAX_BUF];
//---------------------------------------------------------------
static PCD8544 lcd;
//---------------------------------------------------------------
void setup() 
{
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
}
//---------------------------------------------------------------
void loop() 
{
  lcd.setCursor(0, 0);

  for (unsigned short i = 0; i < MAX_BUF; i++) 
  {
    lcd.send(PCD8544_DATA, 0xF0);
  }
  delay(50);
  for (unsigned short i = 0; i < MAX_BUF; i++) 
  {
    lcd.send(PCD8544_DATA, 0x0F);
  }
  delay(10);
}
//---------------------------------------------------------------

