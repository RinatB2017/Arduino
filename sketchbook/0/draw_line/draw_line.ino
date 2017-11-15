
#include <FAB_LED.h>

const int num_strip = 5;        // количество полос
const int cnt_led_in_strip = 5; // количество светодиодов в полосе
const int max_cnt_led = (num_strip + 2) * cnt_led_in_strip; // нужен запас, чтобы было откуда выезжать и куда заезжать полосе
const int len_line = 5;     // длина линии
const int max_len_line = 5; // макс. длина линии

int index_led = 0;

int color_index = 0;
uint8_t brightness_R = 0;
uint8_t brightness_G = 0;
uint8_t brightness_B = 255;

grb array_leds[max_cnt_led] = {};

// Declare the LED protocol and the port
ws2812b<D,7>  strip_7;
ws2812b<D,6>  strip_6;
ws2812b<D,5>  strip_5;
ws2812b<D,4>  strip_4;
ws2812b<D,3>  strip_3;

// The pixel array to display
grb  pixels[cnt_led_in_strip] = {};

int delay_ms = 100;
//-----------------------------------------------------------------------------
void clear_all()
{
  // Turn off the LEDs
  strip_3.clear(cnt_led_in_strip);
  strip_4.clear(cnt_led_in_strip);
  strip_5.clear(cnt_led_in_strip);
  strip_6.clear(cnt_led_in_strip);
  strip_7.clear(cnt_led_in_strip);
}
//-----------------------------------------------------------------------------
void setup()
{
  clear_all();
}
//-----------------------------------------------------------------------------
void prepare_line()
{
  for(int i=0; i<max_cnt_led; i++)
  {
    array_leds[i].r = 0;
    array_leds[i].g = 0;
    array_leds[i].b = 0;
  }    

  for(int n=0; n<len_line; n++)
  {
    array_leds[index_led+n].r = brightness_R;
    array_leds[index_led+n].g = brightness_G;
    array_leds[index_led+n].b = brightness_B;
  }
  
  if(index_led<(max_cnt_led - cnt_led_in_strip))
  {
    index_led++;
  }
  else
  {
    index_led = 0;
    switch(color_index)
    {
      case 0:
        brightness_R = 255;
        brightness_G = 0;
        brightness_B = 0;
        color_index = 1;
        break;
        
      case 1:
        brightness_R = 0;
        brightness_G = 255;
        brightness_B = 0;
        color_index = 2;
        break;
        
      case 2:
        brightness_R = 0;
        brightness_G = 0;
        brightness_B = 255;
        color_index = 0;
        break;     
        
     default:
        color_index = 0;
        break;
    }
  }
}
//-----------------------------------------------------------------------------
void draw_line()
{
  int index = 0;
  //---
  index = cnt_led_in_strip;
  for(int i = 0; i < cnt_led_in_strip; i++)
  {
    pixels[i].r = array_leds[index + i].r;
    pixels[i].g = array_leds[index + i].g;
    pixels[i].b = array_leds[index + i].b;
  }
  strip_3.sendPixels(cnt_led_in_strip, pixels);
  //---
  index += cnt_led_in_strip;
  for(int i = 0; i < cnt_led_in_strip; i++)
  {
    pixels[i].r = array_leds[index + i].r;
    pixels[i].g = array_leds[index + i].g;
    pixels[i].b = array_leds[index + i].b;
  }
  strip_4.sendPixels(cnt_led_in_strip, pixels);
  //---
  index += cnt_led_in_strip;
  for(int i = 0; i < cnt_led_in_strip; i++)
  {
    pixels[i].r = array_leds[index + i].r;
    pixels[i].g = array_leds[index + i].g;
    pixels[i].b = array_leds[index + i].b;
  }
  strip_5.sendPixels(cnt_led_in_strip, pixels);
  //---
  index += cnt_led_in_strip;
  for(int i = 0; i < cnt_led_in_strip; i++)
  {
    pixels[i].r = array_leds[index + i].r;
    pixels[i].g = array_leds[index + i].g;
    pixels[i].b = array_leds[index + i].b;
  }
  strip_6.sendPixels(cnt_led_in_strip, pixels);
  //---
  index += cnt_led_in_strip;
  for(int i = 0; i < cnt_led_in_strip; i++)
  {
    pixels[i].r = array_leds[index + i].r;
    pixels[i].g = array_leds[index + i].g;
    pixels[i].b = array_leds[index + i].b;
  }
  strip_7.sendPixels(cnt_led_in_strip, pixels);
  //---
}
//-----------------------------------------------------------------------------
void sleep()
{
  delay(delay_ms);
}
//-----------------------------------------------------------------------------
void new_loop()
{
  prepare_line();
  draw_line();
  sleep();
}
//-----------------------------------------------------------------------------
void loop()
{
  new_loop();
}
//-----------------------------------------------------------------------------

