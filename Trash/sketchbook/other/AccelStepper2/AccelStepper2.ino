//---------------------------------------------------------------
int pin1 = 8;
int pin2 = 9;
int pin3 = 10;
int pin4 = 11;
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}
//---------------------------------------------------------------
void kick_1pin(int pin)
{
  switch(pin)
  {
  case 0:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    break;

  case 1:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    break;

  case 2:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    break;

  case 3:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    break;

  default:
    break;
  }
}
//---------------------------------------------------------------
void kick_2pin(int pin)
{
  switch(pin)
  {
  case 0:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    break;

  case 1:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    break;

  case 2:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
    break;

  case 3:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    break;

  default:
    break;
  }
}
//---------------------------------------------------------------
void run(int delay_us)
{
  kick_1pin(0);
  delayMicroseconds(delay_us);
  kick_1pin(1);
  delayMicroseconds(delay_us);
  kick_1pin(2);
  delayMicroseconds(delay_us);
  kick_1pin(3);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_2phase(int delay_us)
{
  kick_2pin(0);
  delayMicroseconds(delay_us);
  kick_2pin(1);
  delayMicroseconds(delay_us);
  kick_2pin(2);
  delayMicroseconds(delay_us);
  kick_2pin(3);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_direct(int delay_us)
{
  /*
  PB0 - 3
   */
  PORTB |=  (1 << 0);
  PORTB |=  (1 << 1);
  PORTB &= ~(1 << 2);
  PORTB &= ~(1 << 3);
  delayMicroseconds(delay_us);

  PORTB &= ~(1 << 0);
  PORTB |=  (1 << 1);
  PORTB |=  (1 << 2);
  PORTB &= ~(1 << 3);
  delayMicroseconds(delay_us);

  PORTB &= ~(1 << 0);
  PORTB &= ~(1 << 1);
  PORTB |=  (1 << 2);
  PORTB |=  (1 << 3);
  delayMicroseconds(delay_us);

  PORTB |=  (1 << 0);
  PORTB &= ~(1 << 1);
  PORTB &= ~(1 << 2);
  PORTB |=  (1 << 3);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_left(int delay_us)
{
  kick_2pin(3);
  delayMicroseconds(delay_us);
  kick_2pin(2);
  delayMicroseconds(delay_us);
  kick_2pin(1);
  delayMicroseconds(delay_us);
  kick_2pin(0);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void run_right(int delay_us)
{
  kick_2pin(0);
  delayMicroseconds(delay_us);
  kick_2pin(1);
  delayMicroseconds(delay_us);
  kick_2pin(2);
  delayMicroseconds(delay_us);
  kick_2pin(3);
  delayMicroseconds(delay_us);
}
//---------------------------------------------------------------
void test1(void)
{
  int begin_time = millis();

  for(int n=0; n<(180 * 5.625); n++)
  {
    //run(1850);
    //run(1900);
    //run_2phase(1900);
    //run_direct(1600);
    run_2phase(1640);
  }
  int end_time = millis();
  Serial.println(end_time - begin_time);
}
//---------------------------------------------------------------
void test2(void)
{
  int begin_time = millis();
  for(int n=0; n<(180 * 5.625); n++)
  {
    run_right(1800);
  }
  for(int n=0; n<(180 * 5.625); n++)
  {
    run_left(1800);
  }
  int end_time = millis();
  Serial.println(end_time - begin_time);
}
//---------------------------------------------------------------
int analogPin = 0;     // номер порта к которому подключен потенциометр
int val = 0;           // переменная для хранения считываемого значения
//---------------------------------------------------------------
void loop(void)
{
#if 0
  val = analogRead(analogPin);     // считываем значение
  Serial.println(val);             // выводим полученное значение
  delay(100);
#else
  test1();
#endif
}
//---------------------------------------------------------------









