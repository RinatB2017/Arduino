//---------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------
#include <Wire.h>
//---------------------------------------------------------------
int pin_SDA = A4;
int pin_SCL = A5;
//---------------------------------------------------------------
char local_data[100];
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
char week[8][10] = {
  "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
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
void setDateDs1307(byte second,            // 0-59
                              byte minute,           // 0-59
                              byte hour,              // 1-23
                              byte dayOfWeek,     // 1-7
                              byte dayOfMonth,    // 1-28/29/30/31
                              byte month,           // 1-12
                              byte year)              // 0-99
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
void prepare_data(void)
{
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  sprintf(local_data, "%02d:%02d;%02d/%02d/%02d", 
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
  minute = 12;
  hour     = 10;
  dayOfWeek = 0;
  dayOfMonth = 26;
  month = 10;
  year = 15;

  setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}
//---------------------------------------------------------------
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  Wire.begin();

  // выполняется один раз при смене батарейки
  // лучше запускать по условию
  set_current_time();
}
//---------------------------------------------------------------
void loop(void)
{
    prepare_data();
    Serial.println(local_data);
}
//---------------------------------------------------------------




