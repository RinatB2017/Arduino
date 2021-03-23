#include "FastLED.h"
#define NUM_LEDS 6
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}

void loop() {
  leds[1] = CRGB::White; FastLED.show(); delay(30);
  leds[1] = CRGB::Black; FastLED.show(); delay(30);
}
