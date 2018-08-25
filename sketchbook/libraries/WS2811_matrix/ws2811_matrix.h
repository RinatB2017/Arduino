/**********************************************************************************
 **                   Author: Bikbao Rinat Zinorovich                            **
 **********************************************************************************/
#ifndef WS2811_MATRIX_H
#define WS2811_MATRIX_H

#include "FastLED.h"

#define NUM_STRIPS 9

#define SIZE_MATRIX_0 20
#define SIZE_MATRIX_1 30
#define SIZE_MATRIX_2 36
#define SIZE_MATRIX_3 40
#define SIZE_MATRIX_4 36
#define SIZE_MATRIX_5 30
#define SIZE_MATRIX_6 25
#define SIZE_MATRIX_7 20
#define SIZE_MATRIX_8 25

#define MAX_ADDRESS_FRONT     (SIZE_MATRIX_0 + SIZE_MATRIX_1 + SIZE_MATRIX_6)
#define MAX_ADDRESS_SHOULDERS SIZE_MATRIX_6
#define MAX_ADDRESS_BACK      (SIZE_MATRIX_2 + (SIZE_MATRIX_3 / 2))

#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5
#define LED_PIN_5 6
#define LED_PIN_6 7
#define LED_PIN_7 8
#define LED_PIN_8 9
#define LED_PIN_9 10

class WS2811_matrix
{
public:
    WS2811_matrix();

    int test(void);

    void init_leds(void);
    void show_leds(uint8_t brightness);
    void clear_leds(void);
    bool set_left_pixel(unsigned int addr, CRGB color);
    bool set_right_pixel(unsigned int addr, CRGB color);
    bool set_horizontal_pixel(unsigned int addr, CRGB color);
    void set_horizontal(CRGB color);
    void set_pixel_matrix_0(unsigned int addr, CRGB color);
    void set_pixel_matrix_1(unsigned int addr, CRGB color);
    void set_pixel_matrix_2(unsigned int addr, CRGB color);
    void set_pixel_matrix_3(unsigned int addr, CRGB color);
    void set_pixel_matrix_4(unsigned int addr, CRGB color);
    void set_pixel_matrix_5(unsigned int addr, CRGB color);
    void set_pixel_matrix_6(unsigned int addr, CRGB color);
    void set_pixel_matrix_7(unsigned int addr, CRGB color);
    void set_pixel_matrix_8(unsigned int addr, CRGB color);
    bool set_left_pixel_front(unsigned int addr, CRGB color);
    bool set_right_pixel_front(unsigned int addr, CRGB color);
    bool set_left_pixel_back(unsigned int addr, CRGB color);
    bool set_right_pixel_back(unsigned int addr, CRGB color);
    bool set_left_pixel_shoulders(unsigned int addr, CRGB color);
    bool set_right_pixel_shoulders(unsigned int addr, CRGB color);

    int get_max_address(void);

private:
    CRGB matrix0[SIZE_MATRIX_0];
    CRGB matrix1[SIZE_MATRIX_1];
    CRGB matrix2[SIZE_MATRIX_2];
    CRGB matrix3[SIZE_MATRIX_3];
    CRGB matrix4[SIZE_MATRIX_4];
    CRGB matrix5[SIZE_MATRIX_5];
    CRGB matrix6[SIZE_MATRIX_6];
    CRGB matrix7[SIZE_MATRIX_7];
    CRGB matrix8[SIZE_MATRIX_8];

    CLEDController *controllers[NUM_STRIPS];
    const int max_address = SIZE_MATRIX_0 + SIZE_MATRIX_5 + SIZE_MATRIX_8 + SIZE_MATRIX_4 + (SIZE_MATRIX_3 / 2);
};

#endif // WS2811_MATRIX_H
