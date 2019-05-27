//---------------------------------------------------------------
//#define TEST
//---------------------------------------------------------------
#include <SimpleModbusSlave.h>
//---------------------------------------------------------------
enum {
  CMD_ZERO        = 0,

  CMD_SET_COLOR_R = 1,
  CMD_SET_COLOR_G = 2,
  CMD_SET_COLOR_B = 3,
  CMD_SET_COLOR_W = 4,
  CMD_SET_ALL_COLOR = 5,

  CMD_RUN_MOTOR_1 = 6,
  CMD_RUN_MOTOR_2 = 7,
  CMD_RUN_ALL_MOTOR = 8,
  
  CMD_SET_ALL = 9
};

const int motor_1_pin1 = 15;
const int motor_1_pin2 = 16;
const int motor_1_pin3 = 17;
const int motor_1_pin4 = 18;

const int motor_2_pin1 = 26;
const int motor_2_pin2 = 24;
const int motor_2_pin3 = 28;
const int motor_2_pin4 = 30;

const int stop_motor_up   = 40;
const int stop_motor_down = 42;

const int stop_motor_left  = 44;
const int stop_motor_right = 46;

int max_step_horizontal = 0;
int max_step_vertical   = 0;
int current_step_horizontal = 0;
int current_step_vertical   = 0;

const int RedPin     = 2;
const int GreenPin   = 3;
const int BluePin    = 4;
const int WhitePin   = 5;

unsigned int value_COMMAND = 0;
unsigned int value_R = 0;
unsigned int value_G = 0;
unsigned int value_B = 0;
unsigned int value_W = 0;
unsigned int value_MOTOR_1 = 0;
unsigned int value_MOTOR_2 = 0;
//---------------------------------------------------------------
enum 
{     
  // The first register starts at address 0
  COMMAND,
  VALUE_R,     
  VALUE_G,  
  VALUE_B,  
  VALUE_W,  
  VALUE_MOTOR_1,
  VALUE_MOTOR_2,
  TOTAL_ERRORS,  
  TOTAL_REGS_SIZE
};
// function 3 and 16 register array
unsigned int holdingRegs[TOTAL_REGS_SIZE]; 
//---------------------------------------------------------------
void setup(void)
{
  modbus_configure(&Serial, 
  9600, 
  SERIAL_8N1, 
  1, 
  2, 
  TOTAL_REGS_SIZE, 
  holdingRegs); 

  pinMode(RedPin,   OUTPUT);  
  pinMode(GreenPin, OUTPUT);  
  pinMode(BluePin,  OUTPUT);  
  pinMode(WhitePin, OUTPUT);  

  pinMode(motor_1_pin1, OUTPUT);
  pinMode(motor_1_pin2, OUTPUT);
  pinMode(motor_1_pin3, OUTPUT);
  pinMode(motor_1_pin4, OUTPUT);

  pinMode(motor_2_pin1, OUTPUT);
  pinMode(motor_2_pin2, OUTPUT);
  pinMode(motor_2_pin3, OUTPUT);
  pinMode(motor_2_pin4, OUTPUT);

  pinMode(stop_motor_up,   INPUT);
  pinMode(stop_motor_down, INPUT);

  pinMode(stop_motor_up,   INPUT);
  pinMode(stop_motor_down, INPUT);
  
  calibrate_motors();
}
//---------------------------------------------------------------
void normalize_color(void)
{
  if(value_R > 255) value_R = 255;
  if(value_G > 255) value_G = 255;
  if(value_B > 255) value_B = 255;
  if(value_W > 255) value_W = 255;
}
//---------------------------------------------------------------
void kick_motor_1(int pin)
{
  switch(pin)
  {
  case 0:
    digitalWrite(motor_1_pin1, HIGH);
    digitalWrite(motor_1_pin2, HIGH);
    digitalWrite(motor_1_pin3, LOW);
    digitalWrite(motor_1_pin4, LOW);
    break;

  case 1:
    digitalWrite(motor_1_pin1, LOW);
    digitalWrite(motor_1_pin2, HIGH);
    digitalWrite(motor_1_pin3, HIGH);
    digitalWrite(motor_1_pin4, LOW);
    break;

  case 2:
    digitalWrite(motor_1_pin1, LOW);
    digitalWrite(motor_1_pin2, LOW);
    digitalWrite(motor_1_pin3, HIGH);
    digitalWrite(motor_1_pin4, HIGH);
    break;

  case 3:
    digitalWrite(motor_1_pin1, HIGH);
    digitalWrite(motor_1_pin2, LOW);
    digitalWrite(motor_1_pin3, LOW);
    digitalWrite(motor_1_pin4, HIGH);
    break;

  default:
    break;
  }
}
//---------------------------------------------------------------
void kick_motor_2(int pin)
{
  switch(pin)
  {
  case 0:
    digitalWrite(motor_2_pin1, HIGH);
    digitalWrite(motor_2_pin2, HIGH);
    digitalWrite(motor_2_pin3, LOW);
    digitalWrite(motor_2_pin4, LOW);
    break;

  case 1:
    digitalWrite(motor_2_pin1, LOW);
    digitalWrite(motor_2_pin2, HIGH);
    digitalWrite(motor_2_pin3, HIGH);
    digitalWrite(motor_2_pin4, LOW);
    break;

  case 2:
    digitalWrite(motor_2_pin1, LOW);
    digitalWrite(motor_2_pin2, LOW);
    digitalWrite(motor_2_pin3, HIGH);
    digitalWrite(motor_2_pin4, HIGH);
    break;

  case 3:
    digitalWrite(motor_2_pin1, HIGH);
    digitalWrite(motor_2_pin2, LOW);
    digitalWrite(motor_2_pin3, LOW);
    digitalWrite(motor_2_pin4, HIGH);
    break;

  default:
    break;
  }
}
//---------------------------------------------------------------
void run_motor_up(int delay_us)
{
  kick_motor_1(0);
  delayMicroseconds(delay_us);
  kick_motor_1(1);
  delayMicroseconds(delay_us);
  kick_motor_1(2);
  delayMicroseconds(delay_us);
  kick_motor_1(3);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_motor_down(int delay_us)
{
  kick_motor_1(3);
  delayMicroseconds(delay_us);
  kick_motor_1(2);
  delayMicroseconds(delay_us);
  kick_motor_1(1);
  delayMicroseconds(delay_us);
  kick_motor_1(0);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_motor_left(int delay_us)
{
  kick_motor_2(0);
  delayMicroseconds(delay_us);
  kick_motor_2(1);
  delayMicroseconds(delay_us);
  kick_motor_2(2);
  delayMicroseconds(delay_us);
  kick_motor_2(3);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_motor_right(int delay_us)
{
  kick_motor_2(3);
  delayMicroseconds(delay_us);
  kick_motor_2(2);
  delayMicroseconds(delay_us);
  kick_motor_2(1);
  delayMicroseconds(delay_us);
  kick_motor_2(0);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void calibrate_motors(void)
{
  int flag = 0;

  max_step_vertical  = 0;
  while(true)
  {
    run_motor_up(1800);
    flag  = digitalRead(stop_motor_up);
    if(flag == LOW)
      break;
  }
  while(true)
  {
    max_step_vertical++;
    run_motor_down(1800);
    flag  = digitalRead(stop_motor_down);
    if(flag == LOW)
      break;
  }

  max_step_horizontal = 0;
  while(true)
  {
    run_motor_left(1800);
    flag  = digitalRead(stop_motor_left);
    if(flag == LOW)
      break;
  }
  while(true)
  {
    max_step_horizontal++;
    run_motor_right(1800);
    flag  = digitalRead(stop_motor_right);
    if(flag == LOW)
      break;
  }  
}
//---------------------------------------------------------------
void up_down(void)
{
  int flag = 0;

  while(true)
  {
    run_motor_up(1800);
    flag  = digitalRead(stop_motor_up);
    if(flag == LOW)
      break;
  }
  while(true)
  {
    run_motor_down(1800);
    flag  = digitalRead(stop_motor_down);
    if(flag == LOW)
      break;
  }
}
//---------------------------------------------------------------
void left_right(void)
{
  int flag = 0;

  while(true)
  {
    run_motor_left(1800);
    flag  = digitalRead(stop_motor_left);
    if(flag == LOW)
      break;
  }
  while(true)
  {
    run_motor_right(1800);
    flag  = digitalRead(stop_motor_right);
    if(flag == LOW)
      break;
  }
}
//---------------------------------------------------------------
void run_vertical_motor(void)
{
    int vertical = map(value_MOTOR_2, 0, 255, 0, max_step_vertical);
    int delta = vertical - current_step_vertical;
    if(delta > 0)
    {
      for(int n=0; n<delta; n++)
      {
        run_motor_up(1800);
        current_step_vertical++;
      }
    }
    if(delta < 0)
    {
      for(int n=0; n<abs(delta); n++)
      {
        run_motor_down(1800);
        current_step_vertical--;
      }
    }
}
//---------------------------------------------------------------
void run_horizontal_motor(void)
{
    int horizontal = map(value_MOTOR_1, 0, 255, 0, max_step_horizontal);
    int delta = horizontal - current_step_horizontal;
    if(delta > 0)
    {
      for(int n=0; n<delta; n++)
      {
        run_motor_left(1800);
        current_step_horizontal++;
      }
    }
    if(delta < 0)
    {
      for(int n=0; n<abs(delta); n++)
      {
        run_motor_right(1800);
        current_step_horizontal--;
      }
    }
}
//---------------------------------------------------------------
void loop(void)
{
#ifdef TEST  
  analogWrite(WhitePin, 0);
  for(int n=0; n<(max_step_horizontal/2); n++) run_motor_left(1800);
  for(int n=0; n<(max_step_vertical/2);   n++) run_motor_up(1800);
  analogWrite(WhitePin, 10);

  while(1)
  {
  }
#endif

  holdingRegs[TOTAL_ERRORS] = modbus_update();

  value_COMMAND = holdingRegs[COMMAND];
  int horizontal = 0;
  int vertical = 0;
  int delta = 0;
  switch(value_COMMAND)
  {
  case CMD_SET_COLOR_R:
    value_R = holdingRegs[VALUE_R];
    if(value_R > 255) value_R = 255;
    analogWrite(RedPin, value_R);
    break;

  case CMD_SET_COLOR_G:
    value_G = holdingRegs[VALUE_G];
    if(value_G > 255) value_G = 255;
    analogWrite(GreenPin, value_G);
    break;

  case CMD_SET_COLOR_B:
    value_B = holdingRegs[VALUE_B];
    if(value_B > 255) value_B = 255;
    analogWrite(BluePin, value_B);
    break;

  case CMD_SET_COLOR_W:
    value_W = holdingRegs[VALUE_W];
    if(value_W > 255) value_W = 255;
    analogWrite(WhitePin, value_W);
    break;

  case CMD_SET_ALL_COLOR:
    value_R = holdingRegs[VALUE_R];
    value_G = holdingRegs[VALUE_G];
    value_B = holdingRegs[VALUE_B];
    value_W = holdingRegs[VALUE_W];
    normalize_color();
    analogWrite(RedPin,   value_R);
    analogWrite(GreenPin, value_G);
    analogWrite(BluePin,  value_B);
    analogWrite(WhitePin, value_W);
    break;

  case CMD_RUN_MOTOR_1:
    value_MOTOR_1 = holdingRegs[VALUE_MOTOR_1];
    run_horizontal_motor();
    break;

  case CMD_RUN_MOTOR_2:
    value_MOTOR_2 = holdingRegs[VALUE_MOTOR_2];
    run_vertical_motor();
    break;

  case CMD_RUN_ALL_MOTOR:
    value_MOTOR_1 = holdingRegs[VALUE_MOTOR_1];
    value_MOTOR_2 = holdingRegs[VALUE_MOTOR_2];
    run_horizontal_motor();
    run_vertical_motor();
    break;

  case CMD_SET_ALL:
    value_R = holdingRegs[VALUE_R];
    value_G = holdingRegs[VALUE_G];
    value_B = holdingRegs[VALUE_B];
    value_W = holdingRegs[VALUE_W];
    normalize_color();
    value_MOTOR_1 = holdingRegs[VALUE_MOTOR_1];
    value_MOTOR_2 = holdingRegs[VALUE_MOTOR_2];
    analogWrite(RedPin,   value_R);
    analogWrite(GreenPin, value_G);
    analogWrite(BluePin,  value_B);
    analogWrite(WhitePin, value_W);
    run_horizontal_motor();
    run_vertical_motor();
    break;

  default:
    break;
  }
}
//---------------------------------------------------------------

















