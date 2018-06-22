//---------------------------------------------------------------
#include <LiquidCrystal.h>
//---------------------------------------------------------------
#define MAX_X_LCD  16
#define MAX_Y_LCD  1
#define MAX_BUF    128

#define MIN_POS_X  4
#define MAX_POS_X  11

#define POS_D_HOUR   4
#define POS_HOUR     5
#define SEPARATOR_1  6
#define POS_D_MIN    7
#define POS_MIN      8
#define SEPARATOR_2  9
#define POS_D_SEC    10
#define POS_SEC      11
//---------------------------------------------------------------
unsigned int hour_data = 0;
unsigned int min_data  = 0;
unsigned int sec_data  = 0;
unsigned int old_sec_data  = 0;

unsigned long time     = 0;
unsigned long old_time = 0;

unsigned int pos_x = 0;
unsigned int old_pos_x = 0;

enum {
  OFF = 0,
  ON  = 1
};
#ifdef USE_KEYBOARD
int state_keyboard = OFF;
#endif

char buf[MAX_BUF];
//---------------------------------------------------------------
#define pin_rs  8
#define pin_en 9
#define pin_d4 4
#define pin_d5 5
#define pin_d6 6
#define pin_d7 7
LiquidCrystal lcd(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7); 
//---------------------------------------------------------------
void setup(void)
{
  lcd.begin(MAX_X_LCD, MAX_Y_LCD);
  lcd.setCursor(1, 0);
  lcd.write('0');

  old_time = millis();
  pos_x = MIN_POS_X;
  old_pos_x = MIN_POS_X;

#if 0
  lcd.setCursor(pos_x, 1);
  lcd.write((byte)255);
#endif  
}
//---------------------------------------------------------------
void get_time(void)
{
  time = millis();
  if((time - old_time) > 998)
  {
    old_time = time;
    sec_data++;
  }
  if(sec_data > 59)
  {
    sec_data = 0;
    min_data++;
  }
  if(min_data > 59)
  {
    min_data = 0;
    hour_data++;
  }
  if(hour_data > 23)
  {
    hour_data = 0;
  }
}
//---------------------------------------------------------------
void show_clock(void)
{
  if(old_sec_data != sec_data)
  {
    sprintf(buf, "%.2u:%.2u:%.2u", hour_data, min_data, sec_data);
    old_sec_data  = sec_data;
    lcd.setCursor(4, 0);
    lcd.print(buf);
  }
}
//---------------------------------------------------------------
void draw_cursor(void)
{
  if(pos_x < MIN_POS_X)
  {
    pos_x = MIN_POS_X;
    return;
  }
  if(pos_x > MAX_POS_X)
  {
    pos_x = MAX_POS_X;
    return;
  }
#ifdef USE_KEYBOARD
  lcd.setCursor(old_pos_x, 1);
  lcd.print(' ');

  lcd.setCursor(pos_x, 1);
  lcd.write((byte)255);

  old_pos_x = pos_x;
#endif  
}
//---------------------------------------------------------------
void up(void)
{
  //lcd.print ("Up    ");
  if(pos_x == POS_D_HOUR)
  {
    if(hour_data < 48) hour_data+=10;
  }
  if(pos_x == POS_HOUR)
  {
    if(hour_data < 58) hour_data++;
  }

  if(pos_x == POS_D_MIN)
  {
    if(min_data < 48) min_data+=10;
  }
  if(pos_x == POS_MIN)
  {
    if(min_data < 58) min_data++;
  }

  if(pos_x == POS_D_SEC)
  {
    if(sec_data < 48) sec_data+=10;
  }
  if(pos_x == POS_SEC)
  {
    if(sec_data < 58) sec_data++;
  }
}
//---------------------------------------------------------------
void down(void)
{
  //lcd.print ("Down  ");
  if(pos_x == POS_D_HOUR)
  {
    if(hour_data>10) hour_data-=10;
  }
  if(pos_x == POS_HOUR)
  {
    if(hour_data > 0) hour_data--;
  }

  if(pos_x == POS_D_MIN)
  {
    if(min_data>10) min_data-=10;
  }
  if(pos_x == POS_MIN)
  {
    if(min_data > 0) min_data--;
  }

  if(pos_x == POS_D_SEC)
  {
    if(sec_data>10) sec_data-=10;
  }
  if(pos_x == POS_SEC)
  {
    if(sec_data > 0) sec_data--;
  }
}
//---------------------------------------------------------------
void left(void)
{
  //lcd.print ("Left  ");
  pos_x--;
  if((pos_x == SEPARATOR_1) || (pos_x == SEPARATOR_2))
    pos_x--;
}
//---------------------------------------------------------------
void right(void)
{
  //lcd.print ("Right ");
  pos_x++;
  if((pos_x == SEPARATOR_1) || (pos_x == SEPARATOR_2))
    pos_x++;
}
//---------------------------------------------------------------
#ifdef USE_KEYBOARD
void menu(void)
{
  int x;
  x = analogRead (0);
  if (x < 60) 
  {
    if(state_keyboard == OFF)
    {
      state_keyboard = ON;
      right();
      draw_cursor();
    }
  }
  else if (x < 200) 
  {
    if(state_keyboard == OFF)
    {
      state_keyboard = ON;
      up();
    }
  }
  else if (x < 400)
  {
    if(state_keyboard == OFF)
    {
      state_keyboard = ON;
      down();
    }
  }
  else if (x < 600)
  {
    if(state_keyboard == OFF)
    {
      state_keyboard = ON;
      left();
      draw_cursor();
    }
  }
  else
  {
    state_keyboard = OFF;
  }
}
#endif
//---------------------------------------------------------------
void loop(void)
{
#if 0  
  get_time();
  show_clock();
#ifdef USE_KEYBOARD
  menu();
#endif  
#endif
}
//---------------------------------------------------------------




