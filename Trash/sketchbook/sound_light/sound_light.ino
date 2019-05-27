//--------------------------------------------------------------
//
//--------------------------------------------------------------
int pin_sound = A0;
int pin_light = A2;
int pin_output = 9;
//--------------------------------------------------------------
int val_sound = 0;
int val_light = 0;
//--------------------------------------------------------------
enum {
  LED_IDLE,
  LED_OFF,
  LED_ON
};
int cnt_delay = 0;  //в мсек
int state_led = LED_OFF;
//--------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  
  pinMode(pin_sound, INPUT);
  pinMode(pin_light, INPUT);
  pinMode(pin_output, OUTPUT);
}
//--------------------------------------------------------------
void loop()
{
  val_sound = analogRead(pin_sound);
  val_light = analogRead(pin_light);
 
  switch(state_led)
  {
    case LED_IDLE:
      analogWrite(pin_output, 255 / 10);
      if(val_sound > 512)
      {
        cnt_delay = 10000;
        state_led = LED_ON;
      }
      break;
      
    case LED_OFF:
      analogWrite(pin_output, 0);
      if(val_light > 512)
      {
        state_led = LED_IDLE;
      }
      break;
      
    case LED_ON:
      if(cnt_delay > 0)
      {
        cnt_delay--;
        delay(1);
        analogWrite(pin_output, 255);
      }
      else
      {
        state_led = LED_OFF;
      }
      break;
  }
}
//--------------------------------------------------------------

