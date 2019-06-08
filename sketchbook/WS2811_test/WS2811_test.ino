//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#if 1
# define NUM_LEDS  6
#else
# define NUM_LEDS  144*4
#endif

#define LED_PIN     9
#define BRIGHTNESS  64
#define DELAY_MS    50
//---------------------------------------------------------------
enum {
  RED = 0,
  GREEN,
  BLUE
};
//---------------------------------------------------------------
CRGB leds[NUM_LEDS + 1];
//---------------------------------------------------------------
int index = 0;
int state = RED;
bool flag = false;
//---------------------------------------------------------------
void setup()
{
  delay(2000);
  LEDS.setBrightness(BRIGHTNESS);
  LEDS.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}
//---------------------------------------------------------------
void clear_1(void)
{
  for (int n = 0; n < NUM_LEDS; n++)
  {
    leds[n] = 0;
  }
}
//---------------------------------------------------------------
void update_1(void)
{
  if (index == 0)
  {
    switch (state)
    {
      case RED:
        state = GREEN;
        break;
      case GREEN:
        state = BLUE;
        break;
      case BLUE:
        state = RED;
        break;
      default:
        break;
    }
  }

  switch (state)
  {
    case RED:
      leds[index] = CRGB::Red;
      break;
    case GREEN:
      leds[index] = CRGB::Green;
      break;
    case BLUE:
      leds[index] = CRGB::Blue;
      break;
    default:
      break;
  }

  if (index < NUM_LEDS) index++;
  else index = 0;
}
//---------------------------------------------------------------
void loop()
{
  clear_1();
  update_1();
  LEDS.show();
  delay(DELAY_MS);
}
//---------------------------------------------------------------
