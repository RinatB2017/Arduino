//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define led_type  RGB
//#define led_type  GRB
//---------------------------------------------------------------
#define NUM_LEDS  144

#define LED_PIN     9
#define BRIGHTNESS  32

//#define DELAY_MS    50
#define DELAY_US  50000

#define LED_LEN     9

#define LEN_LEDS        NUM_LEDS
#define LEN_CLEAN_LEDS  (NUM_LEDS + (LED_LEN * 3))

//#define COLOR_1     CRGB::Gold

#define COLOR_1     CRGB::Red
#define COLOR_2     CRGB::Green
#define COLOR_3     CRGB::Blue

// триколор
//#define COLOR_1     CRGB::White
//#define COLOR_2     CRGB::Blue
//#define COLOR_3     CRGB::Red

CRGB current_color = CRGB::Black;
int index_color = 0;
//---------------------------------------------------------------
CRGB clean_leds[LEN_CLEAN_LEDS];
CRGB leds[LEN_LEDS];
CLEDController *controllers;

int index = 0;
//---------------------------------------------------------------
void delay_ms(int delay_milli_sec)
{
  if(delay_milli_sec == 0) return;
  delay(delay_milli_sec);
}
//---------------------------------------------------------------
void delay_us(int delay_micro_sec)
{
  if(delay_micro_sec == 0) return;
  delayMicroseconds(delay_micro_sec);
}
//---------------------------------------------------------------
void prepare_buf()
{
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
}
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
  delay_us(DELAY_US);

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
  delay_us(DELAY_US);

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
  delay_us(DELAY_US);
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
  delay_us(DELAY_US);
}
//---------------------------------------------------------------
void setup()
{
  controllers = &FastLED.addLeds<WS2812, LED_PIN, led_type>(leds, NUM_LEDS);
  prepare_buf();
}
//---------------------------------------------------------------
void loop()
{
  //update_1();
  update_2();
}
//---------------------------------------------------------------
