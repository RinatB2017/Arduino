//---------------------------------------------------------------
// тест по-быстрому
//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_STRIPS 9
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

CLEDController *controllers[NUM_STRIPS];
uint8_t gBrightness = 12;
//---------------------------------------------------------------
int index = 0;
int index_strip = 0;
//int led_color = 0;
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
void setup()
{
  Serial.begin(9600);

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
/*
  void test(void)
  {
    if (index < NUM_LEDS_PER_STRIP)
    {
    index++;
    }
    else
    {
    index = 0;
    //    led_color = 2;
    if (led_color < 2)
    {
      led_color++;
    }
    else
    {
      led_color = 0;
    }
    }
    for (int y = 0; y < NUM_STRIPS; y++)
    {
    for (int x = 0; x < NUM_LEDS_PER_STRIP; x++) matrix[y][x] = 0;
    //    if(led_color == 0)  matrix[y][index] = CRGB::Red;
    //    if(led_color == 1)  matrix[y][index] = CRGB::Green;
    //    if(led_color == 2)  matrix[y][index] = CRGB::Blue;
    switch (led_color)
    {
      case 0:
        matrix[y][index] = CRGB::Red;
        break;
      case 1:
        matrix[y][index] = CRGB::Green;
        break;
      case 2:
        matrix[y][index] = CRGB::Blue;
        break;
    }
    }

    controllers[0]->show(matrix[0], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[1]->show(matrix[1], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[2]->show(matrix[2], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[3]->show(matrix[3], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[4]->show(matrix[4], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[5]->show(matrix[5], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[6]->show(matrix[6], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[7]->show(matrix[7], NUM_LEDS_PER_STRIP, gBrightness);
    controllers[8]->show(matrix[8], NUM_LEDS_PER_STRIP, gBrightness);

    //delay(50);
  }
*/
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
   8 -
*/
//---------------------------------------------------------------
void loop(void)
{
  /*
    Serial.print(index);
    Serial.print(" ");
    Serial.println(leds_per_strip[0]);
  */

  for (int x = 0; x < leds_per_strip[0]; x++) matrix0[x] = 0;
  for (int x = 0; x < leds_per_strip[1]; x++) matrix1[x] = 0;
  for (int x = 0; x < leds_per_strip[2]; x++) matrix2[x] = 0;
  for (int x = 0; x < leds_per_strip[3]; x++) matrix3[x] = 0;
  for (int x = 0; x < leds_per_strip[4]; x++) matrix4[x] = 0;
  for (int x = 0; x < leds_per_strip[5]; x++) matrix5[x] = 0;
  for (int x = 0; x < leds_per_strip[6]; x++) matrix6[x] = 0;
  for (int x = 0; x < leds_per_strip[7]; x++) matrix7[x] = 0;
  for (int x = 0; x < leds_per_strip[8]; x++) matrix8[x] = 0;

  if (index == 0)
  {
    if (index_strip < 8)
    {
      index_strip++;
    }
    else
    {
      index_strip = 0;
    }
  }

  switch (index_strip)
  {
    case 0:
      if (index < leds_per_strip[0])
        index++;
      else
        index = 0;
      matrix0[index] = CRGB::Red;
      break;

    case 1:
      if (index < leds_per_strip[1])
        index++;
      else
        index = 0;
      matrix1[index] = CRGB::Red;
      break;

    case 2:
      if (index < leds_per_strip[2])
        index++;
      else
        index = 0;
      matrix2[index] = CRGB::Red;
      break;

    case 3:
      if (index < leds_per_strip[3])
        index++;
      else
        index = 0;
      matrix3[index] = CRGB::Red;
      break;

    case 4:
      if (index < leds_per_strip[4])
        index++;
      else
        index = 0;
      matrix4[index] = CRGB::Red;
      break;

    case 5:
      if (index < leds_per_strip[5])
        index++;
      else
        index = 0;
      matrix5[index] = CRGB::Red;
      break;

    case 6:
      if (index < leds_per_strip[6])
        index++;
      else
        index = 0;
      matrix6[index] = CRGB::Red;
      break;

    case 7:
      if (index < leds_per_strip[7])
        index++;
      else
        index = 0;
      matrix7[index] = CRGB::Red;
      break;

    case 8:
      if (index < leds_per_strip[8])
        index++;
      else
        index = 0;
      matrix8[index] = CRGB::Red;
      break;
  }

  controllers[0]->show(matrix0, leds_per_strip[0], gBrightness);
  controllers[1]->show(matrix1, leds_per_strip[1], gBrightness);
  controllers[2]->show(matrix2, leds_per_strip[2], gBrightness);
  controllers[3]->show(matrix3, leds_per_strip[3], gBrightness);
  controllers[4]->show(matrix4, leds_per_strip[4], gBrightness);
  controllers[5]->show(matrix5, leds_per_strip[5], gBrightness);
  controllers[6]->show(matrix6, leds_per_strip[6], gBrightness);
  controllers[7]->show(matrix7, leds_per_strip[7], gBrightness);
  controllers[8]->show(matrix8, leds_per_strip[8], gBrightness);

  delay(100);
}
//---------------------------------------------------------------

