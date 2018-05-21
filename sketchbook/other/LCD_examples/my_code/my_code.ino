//---------------------------------------------------------------
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
//---------------------------------------------------------------
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//---------------------------------------------------------------
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RST A4

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RST);
//---------------------------------------------------------------
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Paint!");

  tft.reset();

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } 
  else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } 
  else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } 
  else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } 
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    //Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    //Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    //Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    //Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    //Serial.println(F("Also if using the breakout, double-check that all wiring"));
    //Serial.println(F("matches the tutorial."));
    //return;
  }

  tft.begin(); 
  //tft.begin(identifier); 
  //tft.fillScreen(RED);
  tft.fillRect(0, 0, 100, 100, YELLOW);
  
  //tft.setCursor(0, 0);
  //tft.setTextColor(WHITE);  
  //tft.setTextSize(4);
  //tft.println("Hello World!");
}
//---------------------------------------------------------------
void loop()
{
  //tft.fillScreen(RED);
  //delay(1000);
  //tft.fillScreen(GREEN);
  //delay(1000);
  //tft.fillScreen(BLUE);
  //delay(1000);
}
//---------------------------------------------------------------


