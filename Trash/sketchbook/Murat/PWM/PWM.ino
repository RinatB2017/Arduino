int ledPin_0 = 9;
int ledPin_1 = 10;
int ledPin_2 = 11;
 
int val_0 = 0;
int val_1 = 0;
int val_2 = 0;

void setup()
{
    pinMode(ledPin_0, OUTPUT);
    pinMode(ledPin_1, OUTPUT);
    pinMode(ledPin_2, OUTPUT);

    analogWrite(ledPin_0, 0);
    analogWrite(ledPin_1, 0);
    analogWrite(ledPin_2, 0);
}
 
void loop()
{
  val_0 = 0;
  for(int n=0; n<255; n++)
  {
    analogWrite(ledPin_0, val_0);
    analogWrite(ledPin_1, val_1);
    analogWrite(ledPin_2, val_2);
    val_0++;
    val_1++;
    val_2++;
    delay(5);
  }
  for(int n=255; n>0; n--)
  {
    analogWrite(ledPin_0, val_0);
    analogWrite(ledPin_1, val_1);
    analogWrite(ledPin_2, val_2);
    val_0--;
    val_1--;
    val_2--;
    delay(5);
  }
  delay(1000);
}
