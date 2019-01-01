//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_LEDS  144

#define LED_PIN     9
#define BRIGHTNESS  10 // maximum brightness 96
#define DELAY_MS    50
#define LED_LEN     9

#define LEN_LEDS        NUM_LEDS
#define LEN_CLEAN_LEDS  (NUM_LEDS + (LED_LEN * 3))

//#define COLOR_1     CRGB::Magenta
//#define COLOR_2     CRGB::Green

#define COLOR_1     CRGB::Gold
#define COLOR_2     CRGB::Red
#define COLOR_3     CRGB::Blue

CRGB current_color = CRGB::Gold;
int index_color = 0;
//---------------------------------------------------------------
CRGB clean_leds[LEN_CLEAN_LEDS];
CRGB leds[LEN_LEDS];
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

#if 1
  index = 0;
  index_color = 0;
  int temp_index = 0;
  while (index < LEN_CLEAN_LEDS)
  {
    if (temp_index > LED_LEN)
    {
      index_color++;
      temp_index = 0;
    }
    else
    {
      temp_index++;
    }

    switch (index_color)
    {
      case 0:
        current_color = COLOR_1;
        break;

      case 1:
        current_color = COLOR_2;
        break;

      case 2:
        current_color = COLOR_3;
        break;

      default:
        index_color = 0;
        current_color = COLOR_1;
        break;
    }
    clean_leds[index++] = current_color;
  }
  index = 0;
#endif
}
//---------------------------------------------------------------
void update_2()
{
  index ++;
  if (index > (LED_LEN * 3))
  {
    index = 0;
  }
  for (int n = 0; n < NUM_LEDS; n++)
  {
    leds[n] = clean_leds[n + index];
  }
  controllers->show(leds, NUM_LEDS, BRIGHTNESS);
  delay(DELAY_MS);
}
//---------------------------------------------------------------
void loop()
{
  //update_1();
  update_2();
}
//---------------------------------------------------------------


