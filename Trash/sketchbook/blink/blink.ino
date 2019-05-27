/*
   тест
*/

int pin_led = 13;

void setup() {
  Serial.begin(57600);
  Serial.println("Init");
  
  pinMode(pin_led,  OUTPUT);
}

void loop() {
  digitalWrite(pin_led, HIGH);
  delay(500);
  digitalWrite(pin_led, LOW);
  delay(500);
}

