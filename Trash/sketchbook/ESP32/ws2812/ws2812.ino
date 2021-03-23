//---------------------------------------------------------------
//
//---------------------------------------------------------------
#include<FastLED.h>
//---------------------------------------------------------------
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const char* ble_name = "ESP32test";
//---------------------------------------------------------------
#define NUM_LEDS  24
//---------------------------------------------------------------
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
//---------------------------------------------------------------
//CRGB line0[NUM_LEDS];
CRGB matrix0[SIZE_MATRIX_0];
CRGB matrix1[SIZE_MATRIX_1];
CRGB matrix2[SIZE_MATRIX_2];
CRGB matrix3[SIZE_MATRIX_3];
CRGB matrix4[SIZE_MATRIX_4];
CRGB matrix5[SIZE_MATRIX_5];
CRGB matrix6[SIZE_MATRIX_6];
CRGB matrix7[SIZE_MATRIX_7];
CRGB matrix8[SIZE_MATRIX_8];
//---------------------------------------------------------------
CLEDController *controllers[NUM_STRIPS];
//---------------------------------------------------------------
//CLEDController *controllers_0;
int brightness = 255;
int color = 0;
//---------------------------------------------------------------
#define LED_PIN_1 0
#define LED_PIN_2 2
#define LED_PIN_3 4
#define LED_PIN_4 5
#define LED_PIN_5 12
#define LED_PIN_6 13
#define LED_PIN_7 14
#define LED_PIN_8 15
#define LED_PIN_9 16
//---------------------------------------------------------------
void init_leds(void)
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
//---------------------------------------------------------------
void show_leds(void)
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
//---------------------------------------------------------------
void clear_leds(void)
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
//---------------------------------------------------------------
bool set_pixel(unsigned int addr, CRGB color)
{
  if (addr < NUM_LEDS)
  {
    matrix0[addr] = color;
    return true;
  }

  return false;
}
//---------------------------------------------------------------
void setup() {
  init_leds();

  Serial.begin(115200);
  SerialBT.begin(ble_name); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
//---------------------------------------------------------------
void loop() {
  for (int n = 0; n < NUM_LEDS; n++)
  {
    clear_leds();
    set_pixel(n,  color ? CRGB::Red : CRGB::Green);
    show_leds();
    delay(100);
  }
  if (SerialBT.available()) {
    int s = SerialBT.read();
    if (s == '1')
      color = 1;
    else
      color = 0;
  }
}
