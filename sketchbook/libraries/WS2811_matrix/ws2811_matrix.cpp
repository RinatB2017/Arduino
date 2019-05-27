/**********************************************************************************
 **                   Author: Bikbao Rinat Zinorovich                            **
 **********************************************************************************/
#include "ws2811_matrix.h"
//--------------------------------------------------------------------------------
WS2811_matrix::WS2811_matrix()
{
    init_leds();
}
//--------------------------------------------------------------------------------
int WS2811_matrix::test(void)
{
    return 42;
}
//--------------------------------------------------------------------------------
void WS2811_matrix::init_leds(void)
{
    controllers[0] = &FastLED.addLeds<WS2812, LED_PIN_1, GRB>(matrix0, SIZE_MATRIX_0);
    controllers[1] = &FastLED.addLeds<WS2812, LED_PIN_2, GRB>(matrix1, SIZE_MATRIX_1);
    controllers[2] = &FastLED.addLeds<WS2812, LED_PIN_3, GRB>(matrix2, SIZE_MATRIX_2);
    controllers[3] = &FastLED.addLeds<WS2812, LED_PIN_4, GRB>(matrix3, SIZE_MATRIX_3);
    controllers[4] = &FastLED.addLeds<WS2812, LED_PIN_5, GRB>(matrix4, SIZE_MATRIX_4);
    controllers[5] = &FastLED.addLeds<WS2812, LED_PIN_6, GRB>(matrix5, SIZE_MATRIX_5);
    controllers[6] = &FastLED.addLeds<WS2812, LED_PIN_7, GRB>(matrix6, SIZE_MATRIX_6);
    controllers[7] = &FastLED.addLeds<WS2812, LED_PIN_8, GRB>(matrix7, SIZE_MATRIX_7);
    controllers[8] = &FastLED.addLeds<WS2812, LED_PIN_9, GRB>(matrix8, SIZE_MATRIX_8);
}
//--------------------------------------------------------------------------------
void WS2811_matrix::show_leds(uint8_t brightness)
{
    controllers[0]->show(matrix0, SIZE_MATRIX_0, brightness);
    controllers[1]->show(matrix1, SIZE_MATRIX_1, brightness);
    controllers[2]->show(matrix2, SIZE_MATRIX_2, brightness);
    controllers[3]->show(matrix3, SIZE_MATRIX_3, brightness);
    controllers[4]->show(matrix4, SIZE_MATRIX_4, brightness);
    controllers[5]->show(matrix5, SIZE_MATRIX_5, brightness);
    controllers[6]->show(matrix6, SIZE_MATRIX_6, brightness);
    controllers[7]->show(matrix7, SIZE_MATRIX_7, brightness);
    controllers[8]->show(matrix8, SIZE_MATRIX_8, brightness);
}
//--------------------------------------------------------------------------------
void WS2811_matrix::clear_leds(void)
{
    int x = 0;
    for (x = 0; x < SIZE_MATRIX_0; x++) matrix0[x] = 0;
    for (x = 0; x < SIZE_MATRIX_1; x++) matrix1[x] = 0;
    for (x = 0; x < SIZE_MATRIX_2; x++) matrix2[x] = 0;
    for (x = 0; x < SIZE_MATRIX_3; x++) matrix3[x] = 0;
    for (x = 0; x < SIZE_MATRIX_4; x++) matrix4[x] = 0;
    for (x = 0; x < SIZE_MATRIX_5; x++) matrix5[x] = 0;
    for (x = 0; x < SIZE_MATRIX_6; x++) matrix6[x] = 0;
    for (x = 0; x < SIZE_MATRIX_7; x++) matrix7[x] = 0;
    for (x = 0; x < SIZE_MATRIX_8; x++) matrix8[x] = 0;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_left_pixel(unsigned int addr, CRGB color)
{
    unsigned int addr1 = SIZE_MATRIX_7;
    unsigned int addr2 = addr1 + SIZE_MATRIX_1;
    unsigned int addr3 = addr2 + SIZE_MATRIX_6;
    unsigned int addr4 = addr3 + SIZE_MATRIX_2;

    if (addr < addr1)
    {
      matrix0[addr] = color;
      return true;
    }
    if (addr < addr2)
    {
      matrix5[addr - addr1] = color;
      return true;
    }
    if (addr < addr3)
    {
      matrix8[addr - addr2] = color;
      return true;
    }
    if (addr < addr4)
    {
      //FIXME перевернут по ошибке
      matrix4[abs(addr4 - addr - 1)] = color;
      return true;
    }
    if (addr < max_address)
    {
      return true;
    }

    return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_right_pixel(unsigned int addr, CRGB color)
{
    unsigned int addr1 = SIZE_MATRIX_0;
    unsigned int addr2 = addr1 + SIZE_MATRIX_5;
    unsigned int addr3 = addr2 + SIZE_MATRIX_8;
    unsigned int addr4 = addr3 + SIZE_MATRIX_4;

    if (addr < addr1)
    {
      matrix7[addr] = color;
      return true;
    }
    if (addr < addr2)
    {
      matrix1[addr - addr1] = color;
      return true;
    }
    if (addr < addr3)
    {
      matrix6[addr - addr2] = color;
      return true;
    }
    if (addr < addr4)
    {
      matrix2[addr - addr3] = color;
      return true;
    }
    if (addr < max_address)
    {
      return true;
    }

    return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_horizontal_pixel(unsigned int addr, CRGB color)
{
    if (addr > SIZE_MATRIX_3)
    {
      return false;
    }
    matrix3[addr] = color;
    return true;

}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_horizontal(CRGB color)
{
    for (int x = 0; x < SIZE_MATRIX_3; x++) matrix3[x] = color;
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_0(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_0)
    {
      matrix0[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_1(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_1)
    {
      matrix1[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_2(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_2)
    {
      matrix2[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_3(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_3)
    {
      matrix3[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_4(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_4)
    {
      matrix4[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_5(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_5)
    {
      matrix5[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_6(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_6)
    {
      matrix6[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_7(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_7)
    {
      matrix7[addr] = color;
    }
}
//--------------------------------------------------------------------------------
void WS2811_matrix::set_pixel_matrix_8(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_8)
    {
      matrix8[addr] = color;
    }
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_left_pixel_front(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_7)
    {
      set_pixel_matrix_7(addr, color);
      return true;
    }
    if (addr < (SIZE_MATRIX_7 + SIZE_MATRIX_1))
    {
      set_pixel_matrix_1(addr - SIZE_MATRIX_7, color);
      return true;
    }
    if (addr < (SIZE_MATRIX_7 + SIZE_MATRIX_1 + SIZE_MATRIX_6))
    {
      set_pixel_matrix_6(addr - SIZE_MATRIX_7 - SIZE_MATRIX_1, color);
      return true;
    }
    return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_right_pixel_front(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_0)
    {
      set_pixel_matrix_0(addr, color);
      return true;
    }
    if (addr < (SIZE_MATRIX_0 + SIZE_MATRIX_5))
    {
      set_pixel_matrix_5(addr - SIZE_MATRIX_0, color);
      return true;
    }
    if (addr < (SIZE_MATRIX_0 + SIZE_MATRIX_5 + SIZE_MATRIX_8))
    {
      set_pixel_matrix_8(addr - SIZE_MATRIX_0 - SIZE_MATRIX_5, color);
      return true;
    }
    return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_left_pixel_back(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_2)
    {
      //FIXME надо перевернуть
      set_pixel_matrix_2(SIZE_MATRIX_2 - addr, color);
      //set_pixel_matrix_2(addr, color);
      return true;
    }
    if (addr < (SIZE_MATRIX_2 + (SIZE_MATRIX_3 / 2)))
    {
      set_pixel_matrix_3(SIZE_MATRIX_3 - (addr - SIZE_MATRIX_2) - 1, color);
      return true;
    }
    return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_right_pixel_back(unsigned int addr, CRGB color)
{
      if (addr < SIZE_MATRIX_4)
      {
        set_pixel_matrix_4(addr, color);
        return true;
      }
      if (addr < (SIZE_MATRIX_4 + (SIZE_MATRIX_3 / 2)))
      {
        set_pixel_matrix_3(addr - SIZE_MATRIX_4, color);
        return true;
      }
      return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_left_pixel_shoulders(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_6)
    {
      set_pixel_matrix_6(addr, color);
      return true;
    }
    return false;
}
//--------------------------------------------------------------------------------
bool WS2811_matrix::set_right_pixel_shoulders(unsigned int addr, CRGB color)
{
    if (addr < SIZE_MATRIX_8)
    {
      set_pixel_matrix_8(addr, color);
      return true;
    }
    return false;
}
//--------------------------------------------------------------------------------
int WS2811_matrix::get_max_address(void)
{
    return max_address;
}
//--------------------------------------------------------------------------------
