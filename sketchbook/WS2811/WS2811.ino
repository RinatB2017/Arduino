//---------------------------------------------------------------
#include "FastSPI_LED2.h"
//---------------------------------------------------------------
#define NUM_LEDS_1 6
#define NUM_LEDS_2 6
#define NUM_LEDS_3 12

#define LED_PIN_1 8
#define LED_PIN_2 9
#define LED_PIN_3 10

#define BRIGHTNESS 25 // maximum brightness 96
//---------------------------------------------------------------
enum {
  RED = 0,
  GREEN,
  BLUE 
};
//---------------------------------------------------------------
CRGB leds1[NUM_LEDS_1+1];
CRGB leds2[NUM_LEDS_2+1];
CRGB leds3[NUM_LEDS_3+1];
//---------------------------------------------------------------
int index_1 = 0;
int index_2 = 0;
int index_3 = 0;

int state_1 = RED;
int state_2 = RED;
int state_3 = RED;

bool flag = false;
//---------------------------------------------------------------
void setup()
{
  delay(2000);
  LEDS.setBrightness(BRIGHTNESS);
  LEDS.addLeds<WS2811, LED_PIN_1, RGB>(leds1, NUM_LEDS_1);   
  LEDS.addLeds<WS2811, LED_PIN_2, RGB>(leds2, NUM_LEDS_2);   
  LEDS.addLeds<WS2811, LED_PIN_3, RGB>(leds3, NUM_LEDS_3);   
}
//---------------------------------------------------------------
void clear_1(void)
{
  for(int n=0; n<NUM_LEDS_1; n++) 
  {
    leds1[n] = 0;
  }
}
//---------------------------------------------------------------
void clear_2(void)
{
  for(int n=0; n<NUM_LEDS_2; n++) 
  {
    leds2[n] = 0;
  }
}
//---------------------------------------------------------------
void clear_3(void)
{
  for(int n=0; n<NUM_LEDS_3; n++) 
  {
    leds3[n] = 0;
  }
}
//---------------------------------------------------------------
void update_1(void)
{
  if(index_1 == 0)
  {
    switch(state_1)
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

  switch(state_1)
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

  if(index_1<NUM_LEDS_1) index_1++;
  else index_1 = 0;
}
//---------------------------------------------------------------
void update_2(void)
{
  if(index_2 == 0)
  {
    switch(state_2)
    {
    case RED:   
      state_2 = GREEN; 
      break;
    case GREEN: 
      state_2 = BLUE;  
      break;
    case BLUE:  
      state_2 = RED;   
      break;
    default:    
      break;
    }
  }

  switch(state_2)
  {
  case RED:   
    leds2[index_2] = CRGB::Red;   
    break;
  case GREEN: 
    leds2[index_2] = CRGB::Green; 
    break;
  case BLUE:  
    leds2[index_1] = CRGB::Blue;  
    break;
  default: 
    break;
  }

  if(index_2<NUM_LEDS_2) index_2++;
  else index_2 = 0;
}
//---------------------------------------------------------------
void update_3(void)
{
  if(index_3 == 0)
  {
    switch(state_3)
    {
    case RED:   
      state_3 = GREEN; 
      break;
    case GREEN: 
      state_3 = BLUE;  
      break;
    case BLUE:  
      state_3 = RED;   
      break;
    default:    
      break;
    }
  }

  switch(state_3)
  {
  case RED:   
    leds3[index_3] = CRGB::Red;   
    break;
  case GREEN: 
    leds3[index_3] = CRGB::Green; 
    break;
  case BLUE:  
    leds3[index_3] = CRGB::Blue;  
    break;
  default: 
    break;
  }

  if(index_3<NUM_LEDS_3) index_3++;
  else index_3 = 0;
}
//---------------------------------------------------------------
void loop()
{
  clear_1();
  clear_2();
  clear_3();

  update_1();
  update_2();
  update_3();

  //LEDS.showColor(CRGB::White);  
  //FastLED.show();
  LEDS.show();
  delay(100);
}
//---------------------------------------------------------------



