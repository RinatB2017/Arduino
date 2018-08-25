//---------------------------------------------------------------
#include <PN532.h>
#include <SPI.h>
//---------------------------------------------------------------
#define NFC_SS 10

PN532 nfc(NFC_SS);

uint32_t tagId=0;
uint32_t xmitId=0;
char  tagIdString [11]= "1234567890";

unsigned long time;

uint32_t flowState =0;

#define STATE_IDDLE 0
#define STATE_SENDDATA 15
//---------------------------------------------------------------
void setup(void)
{
  pinMode (NFC_SS, OUTPUT);  

  time = millis();
  Serial.begin(9600);
  Serial.println("Starting setup method...");

  //Initialise NFC reader
  nfc.backupSPIConf();
  nfc.begin();
  nfc.RFConfiguration(0x14);  // default is 0xFF (try forever; ultimately it does time out but after a long while
  // modifies NFC library to set up a timeout while searching for RFID tags
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) 
  {
    Serial.println("Didn't find PN53x board");
    // stop
    for(;;);
  }    
  // ok, print received data!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); 
  Serial.println(versiondata & 0xFF, HEX);
  // configure board to read RFID tags and cards
  nfc.SAMConfig();
  nfc.restoreSPIConf();

  Serial.println("NFC initialised OK");   
}
//---------------------------------------------------------------
void loop(void)
{
  if ((millis()-time > 1000)&&(flowState==STATE_IDDLE)) 
  {
    Serial.println("Checking NFC...");
    // look for Mifare type cards every second
    time=millis();
    digitalWrite(10, HIGH);//SPI deselect Ethernet    
    nfc.backupSPIConf();
    Serial.println("Start NFC read");
    tagId = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);
    Serial.println("End NFC read");
    nfc.restoreSPIConf();
    if (tagId != 0) 
    { 
      Serial.print("Read card #"); 
      Serial.println(tagId);
      xmitId=0;
      uint32_t divisor= 1000000000;
      for (int i=0;i<10; i++){
        tagIdString [i]= char(48 + tagId/divisor);
        tagId=tagId%divisor;
        divisor /=10;
      }
      Serial.print("Converted String: "); 
      Serial.println(tagIdString);
      time=millis();
      flowState=STATE_SENDDATA;
      return;
    }
  }   
}
//---------------------------------------------------------------




