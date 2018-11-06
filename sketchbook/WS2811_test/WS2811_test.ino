//---------------------------------------------------------------
#include "FastSPI_LED2.h"
//---------------------------------------------------------------
#if 0
# define NUM_LEDS_1  6
#else
# define NUM_LEDS_1  144*4
#endif

#define LED_PIN_1   8
#define BRIGHTNESS  25 // maximum brightness 96
#define DELAY_MS    10
//---------------------------------------------------------------
enum {
  RED = 0,
  GREEN,
  BLUE
};
//---------------------------------------------------------------
CRGB leds1[NUM_LEDS_1 + 1];
//---------------------------------------------------------------
int index_1 = 0;
int state_1 = RED;
bool flag = false;
//---------------------------------------------------------------
void setup()
{
  delay(2000);
  LEDS.setBrightness(BRIGHTNESS);
  LEDS.addLeds<WS2811, LED_PIN_1, RGB>(leds1, NUM_LEDS_1);
}
//---------------------------------------------------------------
void clear_1(void)
{
  for (int n = 0; n < NUM_LEDS_1; n++)
  {
    leds1[n] = 0;
  }
}
//---------------------------------------------------------------
void update_1(void)
{
  if (index_1 == 0)
  {
    switch (state_1)
    {
      case RED:
        state_1 = GREEN;
        break;
      case GREEN:
        state_1 = BLUE;
        break;
      case BLUE:
        state_1 = RED;
        break;
      default:
        break;
    }
  }

  switch (state_1)
  {
    case RED:
      leds1[index_1] = CRGB::Red;
      break;
    case GREEN:
      leds1[index_1] = CRGB::Green;
      break;
    case BLUE:
      leds1[index_1] = CRGB::Blue;
      break;
    default:
      break;
  }

  if (index_1 < NUM_LEDS_1) index_1++;
  else index_1 = 0;
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


