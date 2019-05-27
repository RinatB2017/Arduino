//---------------------------------------------------------------
#include "TFTLCD.h"
//---------------------------------------------------------------
#define LCD_RESET A4
#define LCD_CS    A3
#define LCD_CD    A2
#define LCD_WR    A1
#define LCD_RD    A0 
//---------------------------------------------------------------
// Color definitions
#define	BLACK     0x0000
#define	BLUE      0x001F
#define	RED       0xF800
#define	GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0 
#define WHITE     0xFFFF
//---------------------------------------------------------------
TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//---------------------------------------------------------------
void setup(void) 
{
  Serial.begin(9600);

  delay(2000);
  tft.reset();
  tft.initDisplay(); 
}
//---------------------------------------------------------------
void loop(void)
{
  tft.fillScreen(WHITE);
  
  //tft.setTextSize(32);
  //tft.setRotation(2);
  //tft.drawRect(10, 10, 210, 310, RED);
  //tft.drawString(10, 160, "abcdef0123456789", BLUE, 2);

  for(int y=10; y<310; y++)
  {
    for(int x=10; x<230; x++)
    {  
      tft.drawPixel(x, y, RED);
    }
  }

  //tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  //tft.fillScreen(BLUE);
  //tft.fillScreen(CYAN);
  //tft.fillScreen(MAGENTA);
  //tft.fillScreen(YELLOW);
  //tft.fillScreen(WHITE);

  //tft.writeRegister(0x0050, 0x00EF);
  //tft.writeRegister(0x0051, 0x0000);
  //tft.writeRegister(0x0052, 0x013F);
  //tft.writeRegister(0x0053, 0x0000);
  while(1)
  {
    
  }
}
//---------------------------------------------------------------

