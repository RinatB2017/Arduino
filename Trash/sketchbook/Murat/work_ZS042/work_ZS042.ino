//---------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------
#include <Wire.h>
#include <SD.h>
//---------------------------------------------------------------
int pin_SDA = A4;
int pin_SCL = A5;

int pin_SCK  = 13;
int pin_MISO = 12;
int pin_MOSI = 11;
int pin_CS   = 10;
//---------------------------------------------------------------
int newValA0; //новое значение с сенсора
int oldValA0; //старое значение с сенсора
int newValA1;
int oldValA1;

int dif0;    //разность между ними
int total0;  //сумма разностных значений по модулю
int dif1;
int total1;

int i; 
int n = 25; // счетчик измерений
//---------------------------------------------------------------
char local_data[100];
char filename[100];
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
char week[8][10] = {
  "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
//---------------------------------------------------------------
File myFile;
//---------------------------------------------------------------
byte decToBcd(byte val)
{
  return ((val/10*16) + (val%10));
}
//---------------------------------------------------------------
byte bcdToDec(byte val)
{
  return ((val/16*10) + (val%16));
}
//---------------------------------------------------------------
void setDateDs1307(byte second,        // 0-59
byte minute,        // 0-59
byte hour,          // 1-23
byte dayOfWeek,     // 1-7
byte dayOfMonth,    // 1-28/29/30/31
byte month,         // 1-12
byte year)          // 0-99
{
  Wire.beginTransmission(0x68);
  Wire.write(0);
  Wire.write(decToBcd(second));    
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));     
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}
//---------------------------------------------------------------
void getDateDs1307(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{

  Wire.beginTransmission(0x68);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(0x68, 7);

  *second     = bcdToDec(Wire.read() & 0x7f);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f); 
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());
}
//---------------------------------------------------------------
float get3231Temp(void)
{
  byte tMSB, tLSB; 
  float temp3231;

  Wire.beginTransmission(0x68);
  Wire.write(0x11);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 2);

  if(Wire.available()) 
  {
    tMSB = Wire.read(); //2's complement int portion
    tLSB = Wire.read(); //fraction portion

    temp3231 = (tMSB & B01111111); //do 2's math on Tmsb
    temp3231 += ( (tLSB >> 6) * 0.25 ); //only care about bits 7 & 8
  }
  else 
  {
    //oh noes, no data!
  }

  return temp3231;
}
//---------------------------------------------------------------
//---------------------------------------------------------------
bool write(void)
{
  // if the file opened okay, write to it:
  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    myFile.close();
    Serial.println("done.");
    return true;
  }
  Serial.println("error opening test.txt");
  return false;
}
//---------------------------------------------------------------
bool read(void)
{
  myFile = SD.open("test.txt");
  if (myFile) 
  {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) 
    {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    return true;
  }
  Serial.println("error opening test.txt");
  return false;
}
//---------------------------------------------------------------
void prepare_data(void)
{
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  sprintf(local_data, "%d;%d;%02d:%02d:%02d;%02d/%02d/%02d", 
  total0,
  total1,
  hour, 
  minute, 
  second, 
  dayOfMonth, 
  month, 
  year);
}
//---------------------------------------------------------------
void set_current_time(void)
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  second = 0;
  minute = 26;
  hour   = 13;
  dayOfWeek = 6;
  dayOfMonth = 26;
  month = 10;
  year = 15;

  setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}
//---------------------------------------------------------------
bool prepare_SD(void)
{
  //if (!SD.begin(pin_CS)) 
  if (!SD.begin()) 
  {
    Serial.println("SD initialization failed!");
    return false;
  }
  Serial.println("SD initialization done.");

  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  sprintf(filename, "%02d%02d%02d.csv", hour, minute, second);
  //myFile = SD.open(filename, FILE_WRITE);
  return true;
}
//---------------------------------------------------------------
bool measuring(void)
{
  if (i < n)
  { 
    oldValA0 = analogRead(0);
    oldValA1 = analogRead(1);
    delay(200);

    newValA0 = analogRead(0);
    newValA1 = analogRead(1);
    delay(200);        

    dif0 = abs(newValA0 - oldValA0);
    dif1 = abs(newValA1 - oldValA1);

    total0 += dif0;
    total1 += dif1;

    i++;
  }
  else
  {
    //результаты готовы
    return true;
  }
  return false;
}
//---------------------------------------------------------------
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  Wire.begin();

  bool ok = prepare_SD();
  if(!ok)
  {
    while(1);
    //зависнем сознательно
  }

  total0 = 0; 
  total1 = 0; 
  i = 0;
}
//---------------------------------------------------------------
void loop(void)
{
  bool ok = measuring();
  if(ok)
  {
    prepare_data();
    total0 = 0; 
    total1 = 0; 
    i = 0;

    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) 
    {
      myFile.println(local_data);
    }
    myFile.close();
  }
}
//---------------------------------------------------------------




