
int D1 = 2;
int D2 = 3;
int D3 = 4;
int D4 = 5;
int D5 = 6;
int D6 = 7;
int D7 = 8;
int D8 = 9;

int delay_ms = 100;

void setup()
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop()
{
  digitalWrite(D1, HIGH);
  delay(delay_ms);
  digitalWrite(D1, LOW);
  delay(delay_ms);

  digitalWrite(D2, HIGH);
  delay(delay_ms);
  digitalWrite(D2, LOW);
  delay(delay_ms);

  digitalWrite(D3, HIGH);
  delay(delay_ms);
  digitalWrite(D3, LOW);
  delay(delay_ms);

  digitalWrite(D4, HIGH);
  delay(delay_ms);
  digitalWrite(D4, LOW);
  delay(delay_ms);

  digitalWrite(D5, HIGH);
  delay(delay_ms);
  digitalWrite(D5, LOW);
  delay(delay_ms);

  digitalWrite(D6, HIGH);
  delay(delay_ms);
  digitalWrite(D6, LOW);
  delay(delay_ms);

  digitalWrite(D7, HIGH);
  delay(delay_ms);
  digitalWrite(D7, LOW);
  delay(delay_ms);

  digitalWrite(D8, HIGH);
  delay(delay_ms);
  digitalWrite(D8, LOW);
  delay(delay_ms);
}

