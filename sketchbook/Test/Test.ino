//---------------------------------------------------------------
const int buttonPin0 = 5;
const int buttonPin1 = 7;
const int buttonPin2 = 9;
const int buttonPin3 = 11;

const int ledPin0 = 4;
const int ledPin1 = 6;
const int ledPin2 = 8;
const int ledPin3 = 10;
//---------------------------------------------------------------
int r0 = 0;
int r1 = 0;
int r2 = 0;
int r3 = 0;

int led = 0;
//---------------------------------------------------------------
void setup(void)
{
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  randomSeed(analogRead(0));
}
//---------------------------------------------------------------
void light(int led)
{
  switch(led)
  {
  case 0:
    digitalWrite(ledPin0, HIGH);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    break;

  case 1:
    digitalWrite(ledPin0, LOW);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    break;

  case 2:
    digitalWrite(ledPin0, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    break;

  case 3:
    digitalWrite(ledPin0, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    break;

  default:
    break;
  }
}
//---------------------------------------------------------------
bool check_button(int led)
{
  r0 = digitalRead(buttonPin0);
  r1 = digitalRead(buttonPin1);
  r2 = digitalRead(buttonPin2);
  r3 = digitalRead(buttonPin3);

  bool ok = false;
  switch(led)
  {
  case 0:
    if(r0 == LOW) ok = true;
    if(r1 == LOW) ok = false;
    if(r2 == LOW) ok = false;
    if(r3 == LOW) ok = false;
    break;

  case 1:
    if(r0 == LOW) ok = false;
    if(r1 == LOW) ok = true;
    if(r2 == LOW) ok = false;
    if(r3 == LOW) ok = false;
    break;

  case 2:
    if(r0 == LOW) ok = false;
    if(r1 == LOW) ok = false;
    if(r2 == LOW) ok = true;
    if(r3 == LOW) ok = false;
    break;

  case 3:
    if(r0 == LOW) ok = false;
    if(r1 == LOW) ok = false;
    if(r2 == LOW) ok = false;
    if(r3 == LOW) ok = true;
    break;

  default:
    break;
  }
  return ok;
}
//---------------------------------------------------------------
void loop(void)
{
  led = random(4);
  light(led);

  while(!check_button(led))
  {
//    delay(10);
  }
}
//---------------------------------------------------------------













