//---------------------------------------------------------------
//  суровый говнокод :)
//---------------------------------------------------------------
#include <Wire.h>                           // Подключаем библиотеку Wire                           
#include <TimeLib.h>                        // Подключаем библиотеку TimeLib
#include <DS1307RTC.h>                      // Подключаем библиотеку DS1307RTC
//---------------------------------------------------------------
#include <SD.h>
//---------------------------------------------------------------
File myFile;
//---------------------------------------------------------------
int analogPin_0  = A0;
int analogPin_1  = A1;
int analogPin_2  = A2;
int analogPin_3  = A3;
int analogPin_4  = A4;
int analogPin_5  = A5;

int digitalPin_0  = 14;
int digitalPin_1  = 15;
int digitalPin_2  = 16;
int digitalPin_3  = 17;
int digitalPin_4  = 18;
int digitalPin_5  = 19;

int index = 0;
const int MAX_LEN = 25 * 6;
int buff[MAX_LEN];

tmElements_t tm;
String filename;
//---------------------------------------------------------------
void print2digits(int number) 
{
  if (number >= 0 && number < 10) 
  {
    Serial.write('0');
  }
  Serial.print(number);
}
//---------------------------------------------------------------
void print2digits_file(int number) 
{
  if(myFile)
  {
    if (number >= 0 && number < 10) 
    {
      myFile.write('0');
    }
    myFile.print(number);
  }
}
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
void save()
{
  int n=0;  

//  Serial.println("save");
  if (RTC.read(tm)) 
  {
    myFile = SD.open(filename.c_str(), FILE_WRITE);
    if (myFile) 
    {
      for(int n=0; n<MAX_LEN/6; n+=6)
      {
        myFile.print(String(buff[n + 0]));  
        myFile.write(';');
        myFile.print(String(buff[n + 1]));  
        myFile.write(';');
        myFile.print(String(buff[n + 2]));  
        myFile.write(';');
        myFile.print(String(buff[n + 3]));  
        myFile.write(';');
        myFile.print(String(buff[n + 4]));  
        myFile.write(';');
        myFile.print(String(buff[n + 5]));  
        myFile.write(';');
        myFile.println();
      }
      myFile.close();
    } 
    else 
    {
      Serial.print("error opening [");
      Serial.print(filename);
      Serial.println("]");
      while(1);
    }
  }
  else 
  {
    Serial.println("error RTC");
  }
}
//---------------------------------------------------------------
int blink(int dpin, int apin)
{
  digitalWrite(dpin, HIGH);
  int temp = analogRead(apin);
  digitalWrite(dpin, LOW);
  return temp;
}
//---------------------------------------------------------------
void work()
{
  int temp_0 = blink(digitalPin_0, analogPin_0);
  int temp_1 = blink(digitalPin_1, analogPin_1);
  int temp_2 = blink(digitalPin_2, analogPin_2);
  int temp_3 = blink(digitalPin_3, analogPin_3);
  int temp_4 = blink(digitalPin_4, analogPin_4);
  int temp_5 = blink(digitalPin_5, analogPin_5);

  buff[index] = temp_0;  
  index++;
  buff[index] = temp_1;  
  index++;
  buff[index] = temp_2;  
  index++;
  buff[index] = temp_3;  
  index++;
  buff[index] = temp_4;  
  index++;
  buff[index] = temp_5;  
  index++;
}
//---------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);                       // Устанавливаем скорость передачи данных 

  Serial.println("Test programm");          // Выводим данные на последовательный порт
  Serial.println("-------------------");    // Выводим данные на последовательный порт

  if (RTC.read(tm)) 
  {
    filename += String(tm.Hour);
    filename += "_";
    filename += String(tm.Minute);
    filename += "_";
    filename += String(tm.Second);
    filename += ".csv";
  }
  else
  {
    filename = "noRTC.csv";
  }
  Serial.print("filename = ");
  Serial.println(filename);

  pinMode(digitalPin_0, OUTPUT);
  pinMode(digitalPin_1, OUTPUT);
  pinMode(digitalPin_2, OUTPUT);
  pinMode(digitalPin_3, OUTPUT);
  pinMode(digitalPin_4, OUTPUT);
  pinMode(digitalPin_5, OUTPUT);

  pinMode(10, OUTPUT);
  SD.begin(10);
}
//---------------------------------------------------------------
void loop() 
{
  work();
  if(index >= MAX_LEN)
  {
    save();
    index = 0;
  }
}
//---------------------------------------------------------------






