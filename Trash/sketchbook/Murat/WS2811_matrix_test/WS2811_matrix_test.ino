//---------------------------------------------------------------
// тест по-быстрому
//---------------------------------------------------------------
#include "FastLED.h"
//---------------------------------------------------------------
#define NUM_STRIPS 9
//---------------------------------------------------------------
enum {
  RED = 0,
  GREEN = 1,
  BLUE = 2
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
const int leds_per_strip[NUM_STRIPS] = { 20, 30, 36, 40, 36, 30, 25, 20, 25 };
//---------------------------------------------------------------
// левая сторона
//CRGB matrix0[20];
//CRGB matrix5[30];
//CRGB matrix8[25];
//CRGB matrix4[36];

// правая сторона
//CRGB matrix7[20];
//CRGB matrix1[30];
//CRGB matrix6[25];
//CRGB matrix2[36];

// горизонталь
//CRGB matrix3[40];
//---------------------------------------------------------------
const int size_left_line  = (20 + 30 + 25 + 36 + 20);
const int size_right_line = (20 + 30 + 25 + 36 + 20);
const int size_central_line = 40;
CRGB left_line[size_left_line];
CRGB right_line[size_right_line];
CRGB central_line[size_central_line];
//---------------------------------------------------------------
CLEDController *controllers[NUM_STRIPS];
uint8_t gBrightness = 12;
//---------------------------------------------------------------
int current_color = RED;
int led_color = CRGB::Red;
//---------------------------------------------------------------
int current_led = 0;    // текущий светодиод
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
void debug(String text)
{
  Serial.println(text);
}
//---------------------------------------------------------------
void init_matrix(void)
{
  int index = 0;
  controllers[0] = &FastLED.addLeds<WS2812, LED_PIN_1, GRB>(&left_line[index], leds_per_strip[0]);
  index += leds_per_strip[0];
  controllers[5] = &FastLED.addLeds<WS2812, LED_PIN_6, GRB>(&left_line[index], leds_per_strip[5]);
  index += leds_per_strip[5];
  controllers[8] = &FastLED.addLeds<WS2812, LED_PIN_9, GRB>(&left_line[index], leds_per_strip[8]);
  index += leds_per_strip[8];
  controllers[4] = &FastLED.addLeds<WS2812, LED_PIN_5, GRB>(&left_line[index], leds_per_strip[4]);

  index = 0;
  controllers[7] = &FastLED.addLeds<WS2812, LED_PIN_8, GRB>(&right_line[index], leds_per_strip[7]);
  index += leds_per_strip[7];
  controllers[1] = &FastLED.addLeds<WS2812, LED_PIN_2, GRB>(&right_line[index], leds_per_strip[1]);
  index += leds_per_strip[1];
  controllers[6] = &FastLED.addLeds<WS2812, LED_PIN_7, GRB>(&right_line[index], leds_per_strip[6]);
  index += leds_per_strip[6];
  controllers[2] = &FastLED.addLeds<WS2812, LED_PIN_3, GRB>(&right_line[index], leds_per_strip[2]);

  index = 0;
  controllers[3] = &FastLED.addLeds<WS2812, LED_PIN_4, GRB>(&central_line[index], leds_per_strip[3]);
}
//---------------------------------------------------------------
void show_leds(void)
{
  int index = 0;
  controllers[0]->show(&left_line[index], leds_per_strip[0], gBrightness);
  index += leds_per_strip[0];
  controllers[5]->show(&left_line[index], leds_per_strip[5], gBrightness);
  index += leds_per_strip[5];
  controllers[8]->show(&left_line[index], leds_per_strip[8], gBrightness);
  index += leds_per_strip[8];
  controllers[4]->show(&left_line[index], leds_per_strip[4], gBrightness);

  index = 0;
  controllers[7]->show(&right_line[index], leds_per_strip[7], gBrightness);
  index += leds_per_strip[7];
  controllers[1]->show(&right_line[index], leds_per_strip[1], gBrightness);
  index += leds_per_strip[1];
  controllers[6]->show(&right_line[index], leds_per_strip[6], gBrightness);
  index += leds_per_strip[6];
  controllers[2]->show(&right_line[index], leds_per_strip[2], gBrightness);

  index = 0;
  controllers[3]->show(&central_line[index], leds_per_strip[3], gBrightness);
}
//---------------------------------------------------------------
void clear_matrix(void)
{
  int x = 0;
  for (x = 0; x < size_left_line; x++)    left_line[x]    = CRGB::Black;
  for (x = 0; x < size_right_line; x++)   right_line[x]   = CRGB::Black;
  for (x = 0; x < size_central_line; x++) central_line[x] = CRGB::Black;
}
//---------------------------------------------------------------
void setup()
{
  Serial.begin(57600);
  delay(1000);
  init_matrix();
}
//---------------------------------------------------------------
void loop(void)
{
  debug("loop");
  clear_matrix();
  if (current_led < 111) // без горизонта
  {
    left_line[current_led]  = led_color;
    right_line[current_led] = led_color;
    show_leds();
    current_led++;
  }
  else if (current_led < (111 + 20)) //горизонт
  {
    central_line[current_led - 111]  = led_color;
    central_line[(111 + 40) - current_led] = led_color;
    current_led++;
  }
  else
  {
    current_led = 0;
    switch (current_color)
    {
      case RED:
        current_color = GREEN;
        led_color = CRGB::Green;
        break;
        
      case GREEN:
        current_color = BLUE;
        led_color = CRGB::Blue;
        break;
        
      case BLUE:
        current_color = RED;
        led_color = CRGB::Red;
        break;
        
      default:
        current_color = RED;
        led_color = CRGB::Red;
        break;
    }
  }
  delay(10);
}
//---------------------------------------------------------------

