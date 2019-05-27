//---------------------------------------------------------------
#include <virtuabotixRTC.h>           
#include <stdio.h>
//---------------------------------------------------------------
// Determine the pins connected to the module
// myRTC (clock, data, RST)
virtuabotixRTC myRTC (6, 7, 8);
//---------------------------------------------------------------
byte second, minute, hour, dayOfWeek, dayOfMonth, month;
int  year;
//---------------------------------------------------------------
void setDateDs1302(byte second,        // 0-59
byte minute,        // 0-59
byte hour,          // 1-23
byte dayOfWeek,     // 1-7
byte dayOfMonth,    // 1-28/29/30/31
byte month,         // 1-12
int  year)          // 0-99
{
  myRTC.setDS1302Time(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}
//---------------------------------------------------------------
void getDateDs1302(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
int  *year)
{
  myRTC.updateTime();

  *second     = myRTC.seconds;
  *minute     = myRTC.minutes;
  *hour       = myRTC.hours; 
  *dayOfWeek  = myRTC.dayofweek;
  *dayOfMonth = myRTC.dayofmonth;
  *month      = myRTC.month;
  *year       = myRTC.year;
}
//---------------------------------------------------------------
//---------------------------------------------------------------
void set_current_time(void)
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month;
  int year;
  
  hour   = 21;
  minute = 21;
  second = 54;
  dayOfWeek = 2;
  dayOfMonth = 18;
  month = 11;
  year = 2015;

  setDateDs1302(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}
//---------------------------------------------------------------
//---------------------------------------------------------------
int total0 = 1;
int total1 = 5;
char local_data[100];
void prepare_data(void)
{
  getDateDs1302(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  sprintf(local_data, "%d;%d;%02d:%02d:%02d;%02d.%02d.%d", 
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
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  
  //set_current_time();
}
//---------------------------------------------------------------
void loop(void)
{
#if 0
  prepare_data();
  Serial.println(local_data);
#else
  getDateDs1302(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  Serial.print ("Data ");
  Serial.print (dayOfMonth);
  Serial.print (".");
  Serial.print (month);
  Serial.print (".");
  Serial.print (year);
  Serial.print (" ");
  Serial.print ("Time ");

  Serial.print (hour);
  Serial.print (":");
  Serial.print (minute);
  Serial.print (":");
  Serial.println (second);
#endif  
  
  delay(1000);
}
//---------------------------------------------------------------




