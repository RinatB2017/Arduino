
void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

int x = 0;
void loop(void)
{
  if(x)
  {
    digitalWrite(0, HIGH); 
    digitalWrite(1, LOW); 
    digitalWrite(2, HIGH); 
    digitalWrite(3, LOW); 
    digitalWrite(4, HIGH); 
    digitalWrite(5, LOW); 
    digitalWrite(6, HIGH); 
    digitalWrite(7, LOW); 
  }
  else
    {
    digitalWrite(0, LOW); 
    digitalWrite(1, HIGH); 
    digitalWrite(2, LOW); 
    digitalWrite(3, HIGH); 
    digitalWrite(4, LOW); 
    digitalWrite(5, HIGH); 
    digitalWrite(6, LOW); 
    digitalWrite(7, HIGH); 
  }
  
  x = !x;
  delay(1000);
}
