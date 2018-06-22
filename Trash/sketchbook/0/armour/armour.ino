
#include <FAB_LED.h>

// Declare the LED protocol and the port
ws2812b<D,7>  strip_7;
ws2812b<D,6>  strip_6;
ws2812b<D,5>  strip_5;
ws2812b<D,4>  strip_4;
ws2812b<D,3>  strip_3;

// How many pixels to control
const uint8_t numPixels = 5;

// How bright the LEDs will be (max 255)
const uint8_t maxBrightness = 16;

// The pixel array to display
grb  pixels[numPixels] = {};

grb  pixels_7[numPixels] = {};
grb  pixels_6[numPixels] = {};
grb  pixels_5[numPixels] = {};
grb  pixels_4[numPixels] = {};
grb  pixels_3[numPixels] = {};

int delay_ms = 100;
//-----------------------------------------------------------------------------
int buf[5][5] = {
  { 0,0,0,0,0 },
  { 0,0,0,0,0 },
  { 0,0,0,0,0 },
  { 0,0,0,0,0 },
  { 0,0,0,0,0 }
};
//-----------------------------------------------------------------------------
void updateColors(char r, char g, char b)
{
  for(int i = 0; i < numPixels; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}
//-----------------------------------------------------------------------------
void clear_all()
{
  // Turn off the LEDs
  strip_3.clear(numPixels);
  strip_4.clear(numPixels);
  strip_5.clear(numPixels);
  strip_6.clear(numPixels);
  strip_7.clear(numPixels);
}
//-----------------------------------------------------------------------------
void set_color(int index, char r, char g, char b)
{
  if(index <  0) return;
  if(index >= numPixels) return;
  
  pixels[index].r = r;
  pixels[index].g = g;
  pixels[index].b = b;
}

//-----------------------------------------------------------------------------
void set_color_7(int index, char r, char g, char b)
{
  if(index <  0) return;
  if(index >= numPixels) return;
  
  pixels_7[index].r = r;
  pixels_7[index].g = g;
  pixels_7[index].b = b;
}
//-----------------------------------------------------------------------------
void set_color_6(int index, char r, char g, char b)
{
  if(index <  0) return;
  if(index >= numPixels) return;
  
  pixels_6[index].r = r;
  pixels_6[index].g = g;
  pixels_6[index].b = b;
}
//-----------------------------------------------------------------------------
void set_color_5(int index, char r, char g, char b)
{
  if(index <  0) return;
  if(index >= numPixels) return;
  
  pixels_5[index].r = r;
  pixels_5[index].g = g;
  pixels_5[index].b = b;
}
//-----------------------------------------------------------------------------
void set_color_4(int index, char r, char g, char b)
{
  if(index <  0) return;
  if(index >= numPixels) return;
  
  pixels_4[index].r = r;
  pixels_4[index].g = g;
  pixels_4[index].b = b;
}
//-----------------------------------------------------------------------------
void set_color_3(int index, char r, char g, char b)
{
  if(index <  0) return;
  if(index >= numPixels) return;
  
  pixels_3[index].r = r;
  pixels_3[index].g = g;
  pixels_3[index].b = b;
}
//-----------------------------------------------------------------------------
void setup()
{
  clear_all();
}
//-----------------------------------------------------------------------------
void loop()
{
  //---
  //set_color(0, maxBrightness, 0 , 0);
  //set_color(1, 0, 0 , 0);
  //set_color(2, 0, 0 , 0);
  //set_color(3, 0, 0 , 0);
  //set_color(4, 0, 0 , 0);
  
  updateColors(maxBrightness, 0 , 0);
  strip_3.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(maxBrightness, 0 , 0);
  strip_4.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(maxBrightness, 0 , 0);
  strip_5.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(maxBrightness, 0 , 0);
  strip_6.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(maxBrightness, 0 , 0);
  strip_7.sendPixels(numPixels, pixels);
  delay(delay_ms);
  //---
  updateColors(0, maxBrightness, 0);
  strip_3.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, maxBrightness, 0);
  strip_4.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, maxBrightness, 0);
  strip_5.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, maxBrightness, 0);
  strip_6.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, maxBrightness, 0);
  strip_7.sendPixels(numPixels, pixels);
  delay(delay_ms);
  //---
  updateColors(0, 0, maxBrightness);
  strip_3.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, 0, maxBrightness);
  strip_4.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, 0, maxBrightness);
  strip_5.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, 0, maxBrightness);
  strip_6.sendPixels(numPixels, pixels);
  delay(delay_ms);

  updateColors(0, 0, maxBrightness);
  strip_7.sendPixels(numPixels, pixels);
  delay(delay_ms);
  //---
  for(int n=0; n<5; n++)
  {
    set_color_3(n, maxBrightness, 0, 0);
    set_color_4(n, maxBrightness, 0, 0);
    set_color_5(n, maxBrightness, 0, 0);
    set_color_6(n, maxBrightness, 0, 0);
    set_color_7(n, maxBrightness, 0, 0);

    strip_3.sendPixels(numPixels, pixels_3);
    strip_4.sendPixels(numPixels, pixels_4);
    strip_5.sendPixels(numPixels, pixels_5);
    strip_6.sendPixels(numPixels, pixels_6);
    strip_7.sendPixels(numPixels, pixels_7);
    delay(delay_ms);
  }
  //---
  for(int n=0; n<5; n++)
  {
    set_color_3(n, 0, maxBrightness, 0);
    set_color_4(n, 0, maxBrightness, 0);
    set_color_5(n, 0, maxBrightness, 0);
    set_color_6(n, 0, maxBrightness, 0);
    set_color_7(n, 0, maxBrightness, 0);

    strip_3.sendPixels(numPixels, pixels_3);
    strip_4.sendPixels(numPixels, pixels_4);
    strip_5.sendPixels(numPixels, pixels_5);
    strip_6.sendPixels(numPixels, pixels_6);
    strip_7.sendPixels(numPixels, pixels_7);
    delay(delay_ms);
  }
  //---
  for(int n=0; n<5; n++)
  {
    set_color_3(n, 0, 0, maxBrightness);
    set_color_4(n, 0, 0, maxBrightness);
    set_color_5(n, 0, 0, maxBrightness);
    set_color_6(n, 0, 0, maxBrightness);
    set_color_7(n, 0, 0, maxBrightness);

    strip_3.sendPixels(numPixels, pixels_3);
    strip_4.sendPixels(numPixels, pixels_4);
    strip_5.sendPixels(numPixels, pixels_5);
    strip_6.sendPixels(numPixels, pixels_6);
    strip_7.sendPixels(numPixels, pixels_7);
    delay(delay_ms);
  }
  //---
}
//-----------------------------------------------------------------------------

