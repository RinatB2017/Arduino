
int pin = 33;
//int pin = PC13;
//int pin = PB1;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Setup...");
  pinMode(pin, OUTPUT);
}

void loop() 
{
  digitalWrite(pin, HIGH);
  Serial.println("ON");
  delay(1000);
  
  digitalWrite(pin, LOW);
  Serial.println("OFF");
  delay(1000);
}
