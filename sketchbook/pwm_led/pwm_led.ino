int ledPin_0 = 5;
int ledPin_1 = 6;
 
void setup()
{
    pinMode(ledPin_0, OUTPUT);
    pinMode(ledPin_1, OUTPUT);

}
 
void loop()
{
#if 0  
  for(int n=0; n<100; n++)
  {
    analogWrite(ledPin_1, n);
    delay(100);
  }
#endif  
    analogWrite(ledPin_0, 1);
    analogWrite(ledPin_1, 1);
}
