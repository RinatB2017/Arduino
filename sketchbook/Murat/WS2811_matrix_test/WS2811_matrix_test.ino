//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_LEDS_PER_STRIP 6
#define NUM_STRIPS 8
//---------------------------------------------------------------
CRGB matrix[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CLEDController *controllers[NUM_STRIPS];
uint8_t gBrightness = 128;
//---------------------------------------------------------------
#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5
#define LED_PIN_5 6
#define LED_PIN_6 7
#define LED_PIN_7 8
#define LED_PIN_8 9
//---------------------------------------------------------------
void setup() 
{ 
  controllers[0] = &FastLED.addLeds<WS2812, LED_PIN_1, GRB>(matrix[0], NUM_LEDS_PER_STRIP);
  controllers[1] = &FastLED.addLeds<WS2812, LED_PIN_2, GRB>(matrix[1], NUM_LEDS_PER_STRIP);
  controllers[2] = &FastLED.addLeds<WS2812, LED_PIN_3, GRB>(matrix[2], NUM_LEDS_PER_STRIP);
  controllers[3] = &FastLED.addLeds<WS2812, LED_PIN_4, GRB>(matrix[3], NUM_LEDS_PER_STRIP);
  controllers[4] = &FastLED.addLeds<WS2812, LED_PIN_5, GRB>(matrix[4], NUM_LEDS_PER_STRIP);
  controllers[5] = &FastLED.addLeds<WS2812, LED_PIN_6, GRB>(matrix[5], NUM_LEDS_PER_STRIP);
  controllers[6] = &FastLED.addLeds<WS2812, LED_PIN_7, GRB>(matrix[6], NUM_LEDS_PER_STRIP);
  controllers[7] = &FastLED.addLeds<WS2812, LED_PIN_8, GRB>(matrix[7], NUM_LEDS_PER_STRIP);
}
//---------------------------------------------------------------
void loop(void) 
{ 
#if 0  
  fill_solid(leds[0], NUM_LEDS_PER_STRIP, CRGB::Red);
  fill_solid(leds[1], NUM_LEDS_PER_STRIP, CRGB::Green);
  fill_solid(leds[2], NUM_LEDS_PER_STRIP, CRGB::Blue);
  fill_solid(leds[3], NUM_LEDS_PER_STRIP, CRGB::Red);
  fill_solid(leds[4], NUM_LEDS_PER_STRIP, CRGB::Green);
  fill_solid(leds[5], NUM_LEDS_PER_STRIP, CRGB::Blue);
  fill_solid(leds[6], NUM_LEDS_PER_STRIP, CRGB::Red);
  fill_solid(leds[7], NUM_LEDS_PER_STRIP, CRGB::Green);
#else
  for(int y=0; y<NUM_STRIPS; y++)
  {
    for(int x=0; x<NUM_LEDS_PER_STRIP; x++) matrix[y][x] = CRGB::Red;
  }
#endif
  
  controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[4]->show(matrix[4], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[5]->show(matrix[5], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[6]->show(matrix[6], NUM_LEDS_PER_STRIP, gBrightness);
  controllers[7]->show(matrix[7], NUM_LEDS_PER_STRIP, gBrightness);
}
//---------------------------------------------------------------

