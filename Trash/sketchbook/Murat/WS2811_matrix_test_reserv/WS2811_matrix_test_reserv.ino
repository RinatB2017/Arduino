//---------------------------------------------------------------
// тест по-быстрому
//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_STRIPS 9
//---------------------------------------------------------------
enum {
  RED = 0,
  GREEN,
  BLUE
};
//---------------------------------------------------------------
/*
   0 - 20
   1 - 30
   2 - 36
   3 - 40
   4 - 36
   5 - 36
   6 - 25
   7 - 20
   8 - 25
*/
//---------------------------------------------------------------
int leds_per_strip[NUM_STRIPS] = { 20, 30, 36, 40, 36, 30, 25, 20, 25 };
//---------------------------------------------------------------
CRGB matrix0[20];
CRGB matrix1[30];
CRGB matrix2[36];
CRGB matrix3[40];
CRGB matrix4[36];
CRGB matrix5[30];
CRGB matrix6[25];
CRGB matrix7[20];
CRGB matrix8[25];
//---------------------------------------------------------------
CLEDController *controllers[NUM_STRIPS];
uint8_t gBrightness = 12;
//---------------------------------------------------------------
int current_led = 0;    // текущий светодиод
int current_strip = 0;  // текущая лента светодиодов
//---------------------------------------------------------------
CRGB led_color = CRGB::Red;
int current_color = RED;
//---------------------------------------------------------------
#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5
#define LED_PIN_5 6
#define LED_PIN_6 7
#define LED_PIN_7 8
#define LED_PIN_8 9
#define LED_PIN_9 10
//---------------------------------------------------------------
//void debug(String text)
//{
//  Serial.println(text);
//}
//---------------------------------------------------------------
void init_matrix(void)
{
  //debug("init_matrix");
  controllers[0] = &FastLED.addLeds<WS2812, LED_PIN_1, GRB>(matrix0, leds_per_strip[0]);
  controllers[1] = &FastLED.addLeds<WS2812, LED_PIN_2, GRB>(matrix1, leds_per_strip[1]);
  controllers[2] = &FastLED.addLeds<WS2812, LED_PIN_3, GRB>(matrix2, leds_per_strip[2]);
  controllers[3] = &FastLED.addLeds<WS2812, LED_PIN_4, GRB>(matrix3, leds_per_strip[3]);
  controllers[4] = &FastLED.addLeds<WS2812, LED_PIN_5, GRB>(matrix4, leds_per_strip[4]);
  controllers[5] = &FastLED.addLeds<WS2812, LED_PIN_6, GRB>(matrix5, leds_per_strip[5]);
  controllers[6] = &FastLED.addLeds<WS2812, LED_PIN_7, GRB>(matrix6, leds_per_strip[6]);
  controllers[7] = &FastLED.addLeds<WS2812, LED_PIN_8, GRB>(matrix7, leds_per_strip[7]);
  controllers[8] = &FastLED.addLeds<WS2812, LED_PIN_9, GRB>(matrix8, leds_per_strip[8]);
}
//---------------------------------------------------------------
void show_leds(void)
{
  controllers[0]->show(matrix0, leds_per_strip[0], gBrightness);
  controllers[1]->show(matrix1, leds_per_strip[1], gBrightness);
  controllers[2]->show(matrix2, leds_per_strip[2], gBrightness);
  controllers[3]->show(matrix3, leds_per_strip[3], gBrightness);
  controllers[4]->show(matrix4, leds_per_strip[4], gBrightness);
  controllers[5]->show(matrix5, leds_per_strip[5], gBrightness);
  controllers[6]->show(matrix6, leds_per_strip[6], gBrightness);
  controllers[7]->show(matrix7, leds_per_strip[7], gBrightness);
  controllers[8]->show(matrix8, leds_per_strip[8], gBrightness);
}
//---------------------------------------------------------------
void clear_matrix(void)
{
  for (int x = 0; x < leds_per_strip[0]; x++) matrix0[x] = 0;
  for (int x = 0; x < leds_per_strip[1]; x++) matrix1[x] = 0;
  for (int x = 0; x < leds_per_strip[2]; x++) matrix2[x] = 0;
  for (int x = 0; x < leds_per_strip[3]; x++) matrix3[x] = 0;
  for (int x = 0; x < leds_per_strip[4]; x++) matrix4[x] = 0;
  for (int x = 0; x < leds_per_strip[5]; x++) matrix5[x] = 0;
  for (int x = 0; x < leds_per_strip[6]; x++) matrix6[x] = 0;
  for (int x = 0; x < leds_per_strip[7]; x++) matrix7[x] = 0;
  for (int x = 0; x < leds_per_strip[8]; x++) matrix8[x] = 0;
}
//---------------------------------------------------------------
void show_line(void)
{
  switch (current_strip)
  {
    case 0:
      matrix0[current_led] = led_color;
      break;

    case 1:
      matrix1[current_led] = led_color;
      break;

    case 2:
      matrix2[current_led] = led_color;
      break;

    case 3:
      matrix3[current_led] = led_color;
      break;

    case 4:
      matrix4[current_led] = led_color;
      break;

    case 5:
      matrix5[current_led] = led_color;
      break;

    case 6:
      matrix6[current_led] = led_color;
      break;

    case 7:
      matrix7[current_led] = led_color;
      break;

    case 8:
      matrix8[current_led] = led_color;
      break;
  }
  show_leds();
}
//---------------------------------------------------------------
void switch_color(void)
{
  //debug("current_strip = " + String(current_strip));
  switch (current_color)
  {
    case RED:
      //debug("Red");
      led_color = CRGB::Green;
      current_color = GREEN;
      break;

    case GREEN:
      //debug("Green");
      led_color = CRGB::Blue;
      current_color = BLUE;
      break;

    case BLUE:
      //debug("Blue");
      led_color = CRGB::Red;
      current_color = RED;
      break;

    default:
      //debug("default");
      led_color = CRGB::Red;
      current_color = RED;
      break;
  }
}
//---------------------------------------------------------------
void switch_strip(void)
{
  if (current_led != 0)
  {
    return;
  }

  switch (current_strip)
  {
    case 0:
      current_strip = 5;
      break;
    case 1:
      current_strip = 6;
      break;
    case 2:
      current_strip = 3;
      break;
    case 3:
      current_strip = 0;
      break;
    case 4:
      current_strip = 7;
      break;
    case 5:
      current_strip = 8;
      break;
    case 6:
      current_strip = 2;
      break;
    case 7:
      current_strip = 1;
      break;
    case 8:
      current_strip = 4;
      break;

    default:
      current_strip = 0;
      break;
  }
  current_led = 0;
  if (current_strip == 0)
  {
    switch_color();
  }
}
//---------------------------------------------------------------
void setup()
{
  Serial.begin(57600);
  init_matrix();
}
//---------------------------------------------------------------
void loop(void)
{
  clear_matrix();
  switch_strip();

  if (current_led < leds_per_strip[current_strip])
  {
    show_line();
    current_led++;
    //delay(10);
  }
  else
  {
    current_led = 0;
  }
}
//---------------------------------------------------------------

