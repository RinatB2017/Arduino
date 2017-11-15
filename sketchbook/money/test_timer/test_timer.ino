//---------------------------------------------------------------
#include <SD.h>
#include <Timer.h>
#include <Event.h>
//---------------------------------------------------------------
Timer t;
int cnt=0;
//---------------------------------------------------------------
File myFile;
char buf[100];
//---------------------------------------------------------------
void takeReading(void)
{
  sprintf(buf, "%d;%d;%d;%d;%d", analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), millis());
  if (myFile) 
  {
    myFile.println(buf);
  }
  cnt++;
}
//---------------------------------------------------------------
void test(void)
{
  randomSeed(analogRead(5));
  long randNumber = random(1000);
  sprintf(buf, "file%d.dat", randNumber);
  Serial.print(buf);
  Serial.println(" open");
  myFile = SD.open(buf, FILE_WRITE);
  unsigned long t = 0;
  int r0 = 0;
  int r1 = 0;
  int r2 = 0;
  int r3 = 0;
  while(t<1000000)
  {
    r0 = analogRead(A0);
    r1 = analogRead(A1);
    r2 = analogRead(A2);
    r3 = analogRead(A3);
    t = millis();
    if(!(t % 1000)) Serial.println(t);
    sprintf(buf, "%d %d %d %d %lu", r0, r1, r2, r3, t);
    myFile.println(buf);
  }
  myFile.close();
  Serial.println("test the end!");
  while(1);
}
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);

  if (!SD.begin(10)) 
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  test();

  myFile = SD.open("test.txt", FILE_WRITE);
  t.every(10, takeReading);
}
//---------------------------------------------------------------
void loop(void)
{
  t.update();
}
//---------------------------------------------------------------









