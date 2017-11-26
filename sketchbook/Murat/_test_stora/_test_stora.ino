//---------------------------------------------------------------
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
//---------------------------------------------------------------
#include <SD.h>
//---------------------------------------------------------------
File root;
//---------------------------------------------------------------
// Determine the pins connected to the module
// myRTC (clock, data, RST)
virtuabotixRTC myRTC (A5, A6, A7);
//---------------------------------------------------------------
void printDirectory(File dir, int numTabs)
{
  while (true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      if (numTabs == 0)
        Serial.println("** Done **");
      return;
    }
    for (uint8_t i = 0; i < numTabs; i++)
      Serial.print('\t');
    Serial.print(entry.name());
    if (entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      Serial.print("\t\t");
      Serial.println(entry.size());
    }
    entry.close();
  }
}
//---------------------------------------------------------------
void create_new_file(void)
{
  File myFile;
  
  myFile = SD.open("test.txt", FILE_WRITE);
 
  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    myFile.close();
    Serial.println("done.");
  } 
  else 
  {
    Serial.println("error opening test.txt");
  }
  myFile.close();  
}
//---------------------------------------------------------------
void remove_files(void)
{
  SD.remove("101457.CSV");
  SD.remove("101459.CSV");
  SD.remove("101517.CSV");
  SD.remove("101527.CSV");
  SD.remove("101549.CSV");
  SD.remove("101556.CSV");
  SD.remove("101559.CSV");
  SD.remove("101612.CSV");
}
//---------------------------------------------------------------
void test_SD(void)
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  
  SD.begin(10);

  //create_new_file();
  //remove_files();

  root = SD.open("/");
  printDirectory(root, 0);
  delay(2000);
  Serial.println();
  Serial.println("Files:" );
  Serial.println();
  delay(2000);
  root.rewindDirectory();
  printDirectory(root, 0);
  root.close();
}
//---------------------------------------------------------------
void test_RTC(void)
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
void setup(void)
{
  Serial.begin(9600);
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time"); 
}
//---------------------------------------------------------------
void loop(void)
{
  test_RTC();
}
//---------------------------------------------------------------

