//---------------------------------------------------------------
int sensorPinX = A0;
int sensorPinY = A1;
int sensorValueX = 0;
int sensorValueY = 0;
int old_sensorValueX = 0;
int old_sensorValueY = 0;

char buf[1024];
//---------------------------------------------------------------
void setup(void)
{
  //Serial.begin(300); 
  //Serial.begin(1200);
  //Serial.begin(2400);
  //Serial.begin(4800);
  Serial.begin(9600);
  //Serial.begin(14400);
  //Serial.begin(19200);
  //Serial.begin(28800);
  //Serial.begin(38400);
  //Serial.begin(57600);
  //Serial.begin(115200);  
}
//---------------------------------------------------------------
void loop(void)
{
  sensorValueX = analogRead(sensorPinX);
  sensorValueY = analogRead(sensorPinX);
  if((old_sensorValueX != sensorValueX) || (old_sensorValueY != sensorValueY))
  {
    sprintf(buf, "X=%d Y=%d\n", sensorValueX, sensorValueY);
    old_sensorValueX = sensorValueX;
    old_sensorValueY = sensorValueY;

    Serial.write(buf);
    delay(100);
  }
}
//---------------------------------------------------------------
