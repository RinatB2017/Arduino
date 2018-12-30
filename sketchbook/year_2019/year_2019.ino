//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_LEDS  144

#define LED_PIN     9
#define BRIGHTNESS  10 // maximum brightness 96
#define DELAY_MS    100
#define LED_LEN     9

//#define COLOR_1     CRGB::Magenta
//#define COLOR_2     CRGB::Green

#define COLOR_1     CRGB::Gold
#define COLOR_2     CRGB::Red
#define COLOR_3     CRGB::Blue
//---------------------------------------------------------------
CRGB leds[NUM_LEDS + LED_LEN];
CLEDController *controllers;

int index = 0;
//---------------------------------------------------------------
void update_1()
{
  index = 0;
  while (index < NUM_LEDS)
  {
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_1;
    }
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_2;
    }
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_3;
    }
  }
  controllers->show(leds, NUM_LEDS, BRIGHTNESS);
  delay(DELAY_MS);

  index = 0;
  while (index < NUM_LEDS)
  {
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_2;
    }
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_3;
    }
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_1;
    }
  }
  controllers->show(leds, NUM_LEDS, BRIGHTNESS);
  delay(DELAY_MS);

  index = 0;
  while (index < NUM_LEDS)
  {
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_3;
    }
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_1;
    }
    for (int n = 0; n < LED_LEN; n++)
    {
      leds[index++] = COLOR_2;
    }
  }
  controllers->show(leds, NUM_LEDS, BRIGHTNESS);
  delay(DELAY_MS);
}
//---------------------------------------------------------------
void setup()
{
  controllers = &FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}
//---------------------------------------------------------------
void loop()
{
  update_1();
}
//---------------------------------------------------------------


