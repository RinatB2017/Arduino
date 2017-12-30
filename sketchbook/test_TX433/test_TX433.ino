int tx433_Pin = 9;

int delay_ms = 50;

void setup()
{
  pinMode(tx433_Pin, OUTPUT);
}

void loop()
{
  digitalWrite(tx433_Pin, HIGH);
  delay(delay_ms);
  digitalWrite(tx433_Pin, LOW);
  delay(delay_ms);
}
