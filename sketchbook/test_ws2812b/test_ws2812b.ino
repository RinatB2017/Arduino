#include "FastLED.h"

#define NUM_LEDS 6

#define MIN_BRIGHTNESS  0
#define MAX_BRIGHTNESS  50

#define DATA_PIN 7

CRGB leds[NUM_LEDS];

int color = 0xFFFFFF;

int index = 0;
int inc = 1;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  //  leds[0] = CRGB::Red;
  //  leds[1] = CRGB::Green;
  //  leds[2] = CRGB::Blue;
  //  leds[3] = CRGB::Red;
  //  leds[4] = CRGB::Green;
  //  leds[5] = CRGB::Blue;
  for(int n=0; n<NUM_LEDS; n++)
  {
    //  leds[n] = color;
    leds[n] = CRGB::White;
  }
}

void loop() { 
  index += inc;
  if(index <= MIN_BRIGHTNESS)
    inc *= -1;
  if(index >= MAX_BRIGHTNESS)
    inc *= -1;

  FastLED.setBrightness(index);
  FastLED.show();
}


