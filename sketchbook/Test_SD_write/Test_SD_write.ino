//---------------------------------------------------------------
/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file  
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 */
//---------------------------------------------------------------
#include <SD.h>
//---------------------------------------------------------------
File myFile;
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
void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);

  write();
  read();
}
//---------------------------------------------------------------
void loop()
{
  // nothing happens after setup
}
//---------------------------------------------------------------


