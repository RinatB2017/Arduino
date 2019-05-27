//---------------------------------------------------------------

//---------------------------------------------------------------
#include <LiquidCrystal.h>
//--------------------------------------------------------------------------------
#define MAX_X_LCD  16
#define MAX_Y_LCD  2
//--------------------------------------------------------------------------------
#define pin_rs 8
#define pin_en 9
#define pin_d4 4
#define pin_d5 5
#define pin_d6 6
#define pin_d7 7
LiquidCrystal lcd(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7); 
//---------------------------------------------------------------
int pump_left_top = 7;
int drop_left_top = 6;

int pump_right_top = 5;
int drop_right_top = 4;

int pump_left_bottom = 3;
int drop_left_bottom = 2;

int pump_right_bottom = 1;
int drop_right_bottom = 0;
//---------------------------------------------------------------
int sensorPin_3 = A2;
int sensorPin_2 = A3;
int sensorPin_1 = A4;
int sensorPin_0 = A5;
//---------------------------------------------------------------
int sensor_3 = 0;
int sensor_2 = 0;
int sensor_1 = 0;
int sensor_0 = 0;
//---------------------------------------------------------------
void push_LT(bool state)
{
  digitalWrite(pump_left_top, (state ? HIGH : LOW));
  lcd.setCursor(1, 0);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void drop_LT(bool state)
{
  digitalWrite(drop_left_top, (state ? HIGH : LOW));
  lcd.setCursor(2, 0);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void push_RT(bool state)
{
  digitalWrite(pump_right_top, (state ? HIGH : LOW));
  lcd.setCursor(9, 0);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void drop_RT(bool state)
{
  digitalWrite(drop_right_top, (state ? HIGH : LOW));
  lcd.setCursor(10, 0);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void push_LB(bool state)
{
  digitalWrite(pump_left_bottom, (state ? HIGH : LOW));
  lcd.setCursor(1, 1);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void drop_LB(bool state)
{
  digitalWrite(drop_left_bottom, (state ? HIGH : LOW));
  lcd.setCursor(2, 1);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void push_RB(bool state)
{
  digitalWrite(pump_right_bottom, (state ? HIGH : LOW));
  lcd.setCursor(9, 1);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
void drop_RB(bool state)
{
  digitalWrite(drop_right_bottom, (state ? HIGH : LOW));
  lcd.setCursor(10, 1);
  lcd.print(state ? "1" : "0");
}
//---------------------------------------------------------------
union BYTE {
  uint8_t value;
  struct {
    unsigned bit7 : 1;
    unsigned bit6 : 1;
    unsigned bit5 : 1;
    unsigned bit4 : 1;
    unsigned bit3 : 1;
    unsigned bit2 : 1;
    unsigned bit1 : 1;
    unsigned bit0 : 1;
  } bites;
};
//---------------------------------------------------------------
void draw_value(uint8_t value)
{
  BYTE b;
  b.value = value;
  
  push_LT(b.bites.bit7);
  drop_LT(b.bites.bit6);
  
  push_RT(b.bites.bit5);
  drop_RT(b.bites.bit4);
  
  push_LB(b.bites.bit3);
  drop_LB(b.bites.bit2);
  
  push_RB(b.bites.bit1);
  drop_RB(b.bites.bit0);
}
//---------------------------------------------------------------
void setup() 
{
#if 0  
  pinMode(pump_left_top, OUTPUT);  
  pinMode(drop_left_top, OUTPUT);  
  pinMode(pump_right_top, OUTPUT);  
  pinMode(drop_right_top, OUTPUT);  
  pinMode(pump_left_bottom, OUTPUT);  
  pinMode(drop_left_bottom, OUTPUT);  
  pinMode(pump_right_bottom, OUTPUT);  
  pinMode(drop_right_bottom, OUTPUT);  
#endif  
  
  lcd.begin(MAX_X_LCD, MAX_Y_LCD);
  lcd.clear();
}
//---------------------------------------------------------------
void loop() 
{
  sensor_0 = analogRead(sensorPin_0);    
  sensor_1 = analogRead(sensorPin_1);    
  sensor_2 = analogRead(sensorPin_2);    
  sensor_3 = analogRead(sensorPin_3);    
  
  lcd.clear();
  
  lcd.setCursor(4, 0);
  lcd.print(sensor_0);
  
  lcd.setCursor(4, 1);
  lcd.print(sensor_1);
  
  lcd.setCursor(12, 0);
  lcd.print(sensor_2);
  
  lcd.setCursor(12, 1);
  lcd.print(sensor_3);
  
  int value_sensor_0 = map(sensor_0, 0, 1024, 0, 256);
  //int value_sensor_1 = map(sensor_1, 0, 1024, 0, 256);
  //int value_sensor_2 = map(sensor_2, 0, 1024, 0, 256);
  //int value_sensor_3 = map(sensor_3, 0, 1024, 0, 256);
  
  draw_value(value_sensor_0);
  
  delay(100);
}
//---------------------------------------------------------------

