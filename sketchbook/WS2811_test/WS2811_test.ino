//---------------------------------------------------------------
#include "FastSPI_LED2.h"
//---------------------------------------------------------------
#if 1
# define NUM_LEDS_1  5
#else
# define NUM_LEDS_1  144*4
#endif

#define LED_PIN_1   8
#define BRIGHTNESS  255 // maximum brightness 96
#define DELAY_MS    50
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

#if 1  
  clear_1();

//  CRGB led;
//  led.r = 255;
//  led.g = 255;
//  led.b = 255;
//
//  leds1[0] = led;
//  leds1[4] = led;

  leds1[0] = CRGB::Red;
  leds1[1] = CRGB::Green;
  leds1[2] = CRGB::Blue;
  
  LEDS.show();
#endif
  
#if 0
  for (int n = 0; n < NUM_LEDS_1; n++)
  {
    leds1[n] = 0;
  }
#endif
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
#if 0  
  clear_1();
  update_1();
  LEDS.show();
  delay(DELAY_MS);
#endif
}
//---------------------------------------------------------------


