//---------------------------------------------------------------
#include <virtuabotixRTC.h>           
//---------------------------------------------------------------
// Determine the pins connected to the module
// myRTC (clock, data, RST)
virtuabotixRTC myRTC (6, 7, 8);
//---------------------------------------------------------------
void setup (void) 
{     
  Serial.begin (9600);
  // After to set the entire information, comment the following line
  // (seconds, minutes, hours, day of week, day of month, month, year)
  //myRTC.setDS1302Time (0, 58, 22, 5, 2, 11, 2015);
}
//---------------------------------------------------------------
void loop (void) 
{
  myRTC.updateTime ();

  Serial.print ("Data ");
  Serial.print (myRTC.dayofmonth);
  Serial.print ("/");
  Serial.print (myRTC.month);
  Serial.print ("/");
  Serial.print (myRTC.year);
  Serial.print (" ");
  Serial.print ("Time ");

  Serial.print (myRTC.hours);
  Serial.print (":");
  Serial.print (myRTC.minutes);
  Serial.print (":");
  Serial.println (myRTC.seconds);

  delay (1000);
}
//---------------------------------------------------------------

