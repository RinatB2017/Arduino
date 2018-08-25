//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_LEDS_PER_STRIP 6
#define NUM_STRIPS 4
//---------------------------------------------------------------
CRGB matrix[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CLEDController *controllers[NUM_STRIPS];
uint8_t gBrightness = 255;
//---------------------------------------------------------------
int delay_ms = 10;
//---------------------------------------------------------------
#define LED_PIN_1 8
#define LED_PIN_2 9
#define LED_PIN_3 10
#define LED_PIN_4 11
//---------------------------------------------------------------
void test_R()
{
  int n = 0;

  for(n=0; n<255; n++)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = n;
      s.green = 0;
      s.blue = 0;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
  for(n=255; n>0; n--)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = n;
      s.green = 0;
      s.blue = 0;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
}
//---------------------------------------------------------------
void test_G()
{
  int n = 0;

  for(n=0; n<255; n++)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = 0;
      s.green = n;
      s.blue = 0;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
  for(n=255; n>0; n--)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = 0;
      s.green = n;
      s.blue = 0;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
}
//---------------------------------------------------------------
void test_B()
{
  int n = 0;

  for(n=0; n<255; n++)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = 0;
      s.green = 0;
      s.blue = n;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
  for(n=255; n>0; n--)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = 0;
      s.green = 0;
      s.blue = n;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
}
//---------------------------------------------------------------
void test_W()
{
  int n = 0;

  for(n=0; n<255; n++)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = n;
      s.green = n;
      s.blue = n;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
  for(n=255; n>0; n--)
  {
    for(int y=0; y<NUM_STRIPS; y++)
    {
      CRGB s;
      s.red = n;
      s.green = n;
      s.blue = n;
      for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = s;
    }
    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    
    delay(delay_ms);
  }
}
//---------------------------------------------------------------
void setup() 
{ 
  controllers[0] = &FastLED.addLeds<WS2812, LED_PIN_1, GRB>(matrix[0], NUM_LEDS_PER_STRIP);
  controllers[1] = &FastLED.addLeds<WS2812, LED_PIN_2, GRB>(matrix[1], NUM_LEDS_PER_STRIP);
  controllers[2] = &FastLED.addLeds<WS2812, LED_PIN_3, GRB>(matrix[2], NUM_LEDS_PER_STRIP);
  controllers[3] = &FastLED.addLeds<WS2812, LED_PIN_4, GRB>(matrix[3], NUM_LEDS_PER_STRIP);
}
//---------------------------------------------------------------
void loop(void) 
{ 
  test_R();
  test_G();
  test_B();
  
  test_W();
}
//---------------------------------------------------------------


