/*
   тест
*/

int pin_0 = 13;

void setup() {
  pinMode(pin_0,  OUTPUT);
}

void loop() {
  digitalWrite(pin_0, HIGH);
  delay(250);
  digitalWrite(pin_0, LOW);
  delay(250);
}

