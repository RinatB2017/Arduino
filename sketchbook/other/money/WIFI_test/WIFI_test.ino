//---------------------------------------------------------------
#include <avr/pgmspace.h>		// для PROGMEM
#include <SimpleTimer.h>		// http://playground.arduino.cc//Code/SimpleTimer
#include <WiFiRM04.h>
//---------------------------------------------------------------
char ssid[] = "YOUR SSID";		// your network SSID (name) 
char pass[] = "YOUR NETWORK KEY";	// your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;			// your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
char server[] = "api.pushingbox.com";	// name address for Google (using DNS)
WiFiRM04Client client;

#define ledPin 8
#define weightPin A0
#define tonePin 10
#define weightPowerPin 9

byte tare = 28; // idle weight
byte treshold = 30; // weight sensor value treshold

int i;
int scaleTimeoutID;
byte nameSelectorCount = 0; // counter for name selection
byte stepCount = 0;
byte human = 0; // default setting
byte cat = 0; // default setting

float wt;
long weight, brutto, netto;
long prevWeight = 0;


boolean idleWeight = false;
boolean clearToSend = false;
boolean ishuman = true;
boolean nameSelect = false;
boolean stepCounting = false;
boolean stepTimeout = false;
boolean firstStep = true;

//#define prog_char char

// строки в PROGMEM
prog_char statusString_0[] PROGMEM = "devid1&name="; // User 1
prog_char statusString_1[] PROGMEM = "devid2&name="; // User 2
prog_char statusString_2[] PROGMEM = "devid3&name="; // User 3
prog_char statusString_3[] PROGMEM = "devid4&name="; // Cats
prog_char statusString_4[] PROGMEM = "Юзер 1"; // cyrillic names
prog_char statusString_5[] PROGMEM = "Юзер 2";
prog_char statusString_6[] PROGMEM = "Юзер 3";
prog_char statusString_7[] PROGMEM = "Кот 1";
prog_char statusString_8[] PROGMEM = "Кот 2";
prog_char statusString_9[] PROGMEM = "Кот 3";
prog_char statusString_10[] PROGMEM = "Кот 4";
prog_char statusString_11[] PROGMEM = "Кот 5";
prog_char statusString_12[] PROGMEM = "&name1=User 1"; // latin names for Google Spreadsheet
prog_char statusString_13[] PROGMEM = "&name1=User 2";
prog_char statusString_14[] PROGMEM = "&name1=User 3";
prog_char statusString_15[] PROGMEM = "&name1=Cat 1";
prog_char statusString_16[] PROGMEM = "&name1=Cat 2";
prog_char statusString_17[] PROGMEM = "&name1=Cat 3";
prog_char statusString_18[] PROGMEM = "&name1=Cat 4";
prog_char statusString_19[] PROGMEM = "&name1=Cat 5";
prog_char statusString_20[] PROGMEM = " HTTP/1.1";
prog_char statusString_21[] PROGMEM = "Host: api.pushingbox.com";
prog_char statusString_22[] PROGMEM = "User-Agent: Arduino";


// табличка указателей на строки
PROGMEM const char *statusString[] = 	   
{   
  statusString_0,
  statusString_1,
  statusString_2,
  statusString_3,
  statusString_4,
  statusString_5,
  statusString_6,
  statusString_7,
  statusString_8,
  statusString_9,
  statusString_10,
  statusString_11,
  statusString_12,
  statusString_13,
  statusString_14,
  statusString_15,  
  statusString_16,
  statusString_17,
  statusString_18,
  statusString_19,
  statusString_20,
  statusString_21,
  statusString_22
};

char statusStringBuf[40];    // буфер для чтения строк состояния

SimpleTimer scaleTime;
//---------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);

  pinMode(weightPowerPin, OUTPUT);
  digitalWrite(weightPowerPin, HIGH);

  pinMode(weightPin, INPUT); // weight sensor

  pinMode(ledPin, OUTPUT); // led Power

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); // led GND

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) 
  {
    while(true) 
    {
    }
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) 
  { 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
}
//---------------------------------------------------------------
void loop() 
{
  scaleTime.run();
  averageWeight();

  // CHECK FOR IDLE WEIGHT
  if ((idleWeight == false) && (weight < (tare+treshold))) // check if there is still somebody on table
  {
    idleWeight = true; // set flag to enable measurements in case there is nobody on table
    digitalWrite(ledPin, HIGH); // turn on ready led
  }

  // DETECT STEP-ON
  if ((idleWeight == true) && (weight > (tare+treshold)))  // check if there is still somebody on table
  {
    idleWeight = false;
    digitalWrite(ledPin, LOW); // turn on ready led
    tone(tonePin, 450, 100); // audio confirmation for step-on

    if (stepCounting == false) 
    {
      scaleTime.setTimeout(250, stepDetector);
      stepCounting = true; 	  
    }
  }

  // READY TO SEND
  if (clearToSend == true)  // check for upload permission
  {
    sendWeight(); // upload
  }
}
//---------------------------------------------------------------
// Detect step-on
void stepDetector() 
{
  averageWeight();

  if (weight < (tare+treshold))  // step detected
  {
    if (firstStep == false)  // do not count first step
    {
      stepCount = stepCount + 1; // count step-ons: only announce current name after first step-on; switch names on consecutive step-ons.
      if (stepTimeout == false) // set timeout to confirm last step: i.e. if no one steps on table for specified time, scales must switch to stby or weighing mode
      {
        scaleTimeoutID = scaleTime.setTimeout(1500, stepTotal);
        stepTimeout = true; 
      }
      //          tone(tonePin, 450, 100); // audio confirmation for step-on
      if (stepTimeout == true) 
      {
        scaleTime.restartTimer(scaleTimeoutID);
      }            
    }
    else
    {
      statusNotify(); // announce current status
      stepCount = 0;
    }
    firstStep = false;
  } 
  else 
  {
    if (ishuman == true) 
    {
      getWeight(); 
      netto = weight;
    }
    else 
    {
      getWeight();
      if (clearToSend == true) 
      {
        brutto = weight;
        tone(tonePin, 550, 800);
        delay(3000);
        getWeight();
        if (brutto > weight) 
        {
          netto = brutto - weight;
        } 
        else 
        {
          netto = weight - brutto;
        }
        netto = netto+29;
      }
    }
  }
  stepCounting = false;
}
//---------------------------------------------------------------
void stepTotal() 
{
  // tone(tonePin, 550, 1000);

  if (stepCount == 1) 
  {
    if (ishuman == true) 
    {
      human = human+1;
      if (human > 2) 
      {
        human = 0;
      }
    } 
    else 
    {
      cat = cat+1;
      if (cat > 4) 
      {
        cat = 0;
      }
    }
  }

  if (stepCount == 2) 
  {
    if (ishuman == true) 
    {
      ishuman = false;
    } 
    else 
    {
      ishuman = true;
    }
  }

  if (stepCount > 2) 
  {
    ishuman = true;
    human = 0;
    cat = 0;
    firstStep = true;
  }

  delay(1500);

  statusNotify();

  stepTimeout = false;
  stepCount = 0;
}
//---------------------------------------------------------------
void statusNotify() 
{
  if (ishuman == true) 
  {
    tone (tonePin, 550, 600);
    delay(800);
    makeSound(human+1, 300);
  } 
  else 
  {
    tone (tonePin, 550, 600);
    delay(1000);
    tone (tonePin, 550, 600);
    delay(1000);
    makeSound(cat+1, 300);
  } 
}
//---------------------------------------------------------------
// MEASURE WEIGHT
void getWeight() 
{
  averageWeight();
  if (weight > (tare+treshold)) // object on table still heavier than idle weight
  {
    digitalWrite(ledPin, LOW); // turn off ready led
    delay(3000); // let everything settle
    averageWeight();

    prevWeight = weight;  // save initial weight for future reference
    averageWeight();

    if ((((prevWeight - treshold) < weight) && (weight < (prevWeight + treshold))) && prevWeight > (tare)) // check if measurement average consistent with initial load (ensure object is on table)
    {
      clearToSend = true; // set flag for upload
    } 
    else 
    { 
      makeSound(2, 300); // measurement error
      clearToSend = false; // prevent upload
      idleWeight = false; // set flag to grant subsequent measurements
    }
  }
}
//---------------------------------------------------------------
// HTTP SENDER
void sendWeight() 
{
  netto = netto - tare;
  wt = (float)netto / 7.25;

  if (client.connect(server, 80)) 
  {
    client.print("GET /pushingbox?devid=");
    if (ishuman == true) 
    {
      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[human]))); // devid
      client.print(statusStringBuf);

      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[human+4]))); // name - name for audio notificaion
      client.print(statusStringBuf);

      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[human+12]))); // name1 - name for Google
      client.print(statusStringBuf);
    } 
    else 
    {
      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[3]))); // devid
      client.print(statusStringBuf);

      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[cat+7]))); // name - name for audio notificaion
      client.print(statusStringBuf);

      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[cat+15]))); // name1 - name for Google
      client.print(statusStringBuf);
    }

    client.print("&weight=");
    client.print(wt);

    for (byte clientCounter=20; clientCounter<23; clientCounter++) 
    {
      strcpy_P(statusStringBuf, (char*)pgm_read_word(&(statusString[clientCounter])));
      client.println(statusStringBuf);
    }
    client.println();
    client.stop();  
    makeSound(3, 300); // confirm upload
  }
  else 
  {
    makeSound(2, 300); // upload error
  }

  clearToSend = false; // clear flag
  firstStep = true;
}
//---------------------------------------------------------------
// BEEPER
void makeSound(byte count, byte duration) 
{
  for (i = 0; i<count; i++) 
  {
    tone(tonePin, 550, duration);
    delay(600);
  }
}
//---------------------------------------------------------------
// CALCULATE AVERAGE WEIGHT
void averageWeight() 
{
  weight = 0;
  for (i = 0; i<999; i++) 
  {
    weight = weight+analogRead(weightPin); // capture measurements
  }

  weight = (weight/1000); // measurement average
}
//---------------------------------------------------------------

