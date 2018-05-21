/*  draw number's APP
 drawNumber(long long_num,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
 drawFloat(float floatNumber,INT8U decimal,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
 drawFloat(float floatNumber,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
 */

#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

#define max_data 59
#define ScreenWidth 239
#define ScreenHeight 319
#define Orientation 0
//#define ChartHeight 170 //170
#define StepX 4 //=240/60
#define CT_POROG 100

unsigned long GM_imp;
unsigned int color=0;
unsigned int color1=WHITE;
unsigned int color2=RED;
unsigned int ct=0;
unsigned int data[max_data+1];
unsigned int datamax=0;
unsigned int uk=0;
unsigned int uk1=0;
byte i=0;
int interval_s=120 ; //60;
long interval_ms=(long)interval_s*1000;
int tube_const=18;

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void SetupTimer1()
{
  TCCR1B |= (1<<CS10) | (1<<CS11) | (1<<CS12);                        // Use external clock (T1)
  TCCR1B &= ~((1<<ICNC1) | (1<<ICES1));                               // Disable input capture
  TCCR1B &= ~((1<<WGM12) | (1<<WGM13));                               // Use normal mode
  TIMSK2 &= ~((1<<ICIE1) | (1<<OCIE1B) | (1<<OCIE1A) | (1<<TOIE1));   // Disable all interrupts
  // Set WGM11 and WGM10 to zero in TCCR1A.
  //sbi(TCCR1A, WGM10);
  TCCR1A &= ~((1<<WGM10) | (1<<WGM11));
  TCNT1=0;
  // RESET_TIMER1;
}

void setup()
{
  Serial.begin(57600); 

  SetupTimer1();                      //Setup Timer1 for input counting
  //       SetupTimer2();                      //Setup Timer2 for time counting
  sei();
  //     oldSecond = second;
  pinMode(5,INPUT);


  TFT_BL_ON;                                      // turn on the background light

  Tft.TFTinit();                                  // init TFT library

  //  char s1[]="Glonass-Radiometer";
  //  char s2[]="Sergey Dronsky(C)2014"; 

  // Tft.drawString(s1, 0, 0, 1, RED);
  /*
   RED	LITERAL1
   GREEN	LITERAL1
   BLUE	LITERAL1
   BLACK	LITERAL1
   YELLOW	LITERAL1
   WHITE	LITERAL1
   CYAN	LITERAL1
   BRIGHT_RED	LITERAL1
   GRAY1	LITERAL1
   GRAY2	LITERAL1
   */
  Tft.drawString("Radiometer", 0, 20, 4, BLUE);

  Tft.drawString("Beta-2 sensor", 0, 70, 3, GREEN);

  Tft.drawString("Glonass-GPS", 0, 110, 3, RED);

  Tft.drawString("ML8088s", 0, 150, 3, YELLOW);

  Tft.drawString("Sergey", 0, 190, 4, BRIGHT_RED);
  Tft.drawString("Dronsky", 0, 230, 4, BRIGHT_RED);

  Tft.drawString("(C) 2014", 0, ScreenHeight-40, 4, CYAN);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);

  delay(5000);
  color=RED;
  Tft.fillScreen();
  uk=0;
  Tft.drawString("Checking Glns data...", 0, 0, 2, GREEN);
  //check if ML8088 started OK    
  if( Serial.available()==0) {


    //Reset ML8088s
    Tft.drawString("Resetting ML8088s...", 0, 20, 2, GREEN);
    pinMode(A0, OUTPUT);
    digitalWrite(A0, LOW);
    delay(500);
    digitalWrite(A0, HIGH);
    pinMode(A0, INPUT);

  }
  Tft.drawString("Starting OK.", 0, 40, 2, GREEN);
  Tft.drawString("imp         ",0,0,4,color);
  Serial.println("\nOn skazal - poehali!");
}

void loop()
{

  TCNT1=0; //Reset counter
  long timestart=millis(); //Fix start time


  String gloGPRMC;
  String gloGPGGA;
  String gloGPVTG;

  byte p0=77;
  byte p1=77;
  byte p2=95;
  byte p3=114;
  byte p4=132;
  byte r1=0;
  byte r2=80;
  byte r3=200;
  byte r4=160;
  byte StepY=18;

  do {
    Tft.drawNumber(TCNT1, 70+uk*2,0, 4, color);

    for (int i=0; i<30; i++)
    {
      gloGPRMC=Serial.readStringUntil('\n');
      if (gloGPRMC.startsWith("$GPRMC"))
      {
        break;
      }
    }

    for (int i=0; i<30; i++)
    {
      gloGPGGA=Serial.readStringUntil('\n');
      if(gloGPGGA.startsWith("$GPGGA")) 
      {
        break;
      }
    }

    for (int i=0; i<30; i++)

    {
      gloGPVTG=Serial.readStringUntil('\n');
      if(gloGPVTG.startsWith("$GPVTG")) 
      {
        break;
      }
    }
    //    Serial.println(gloGPRMC);
    //    Serial.println(gloGPGGA);
    //    Serial.println(gloGPVTG);


    //   if (gloGPRMC.startsWith("$GPRMC") && gloGPGGA.startsWith("$GPGGA") && gloGPVTG.startsWith("$GPVTG")){

    char x[30];
    int mc[13];
    int k=0;

    p1=p0+random(2*StepY);
    p2=p1+StepY;
    p3=p2+StepY;
    p4=p3+StepY;

    // if (glo.startsWith("$GPRMC")) {
    // Serial.print(glo);

    for (int j=0; j<gloGPRMC.length() ; j++)
    {
      if (gloGPRMC.charAt(j)==',') 
      {
        mc[k++]=j;
      }
    }

    Tft.fillRectangle(0, p0, ScreenWidth, 6*StepY,  BLACK); 
    // Time UTC
    gloGPRMC.substring(mc[0]+1, mc[1]).toCharArray(x, 7); 
    Tft.drawString(x,r1,p1,2,color);

    // Date
    gloGPRMC.substring(mc[8]+1, mc[9]).toCharArray(x, 7);
    Tft.drawString(x,r2,p1,2,color);

    //A - data valid, V - data invalid
    gloGPRMC.substring(mc[1]+1, mc[2]).toCharArray(x, 2);
    Tft.drawString(x,r3,p1,2,color);

    // Longitude 
    gloGPRMC.substring(mc[2]+1, mc[4]).toCharArray(x, 30);
    Tft.drawString(x,r1,p2,2,color);

    // Latitude
    gloGPRMC.substring(mc[4]+1, mc[6]).toCharArray(x, 30);
    Tft.drawString(x,r1,p3,2,color);

    // Speed (knots), direction, degrees
    gloGPRMC.substring(mc[6]+1, mc[8]).toCharArray(x, 30);
    Tft.drawString(x,r1,p4,2,color);

    //     break;
    //      }

    //       if (glo.startsWith("$GPGGA")) {

    //   Serial.print(glo);
    k=0;         
    for (int j=0; j<gloGPGGA.length() ; j++)
    {
      if (gloGPGGA.charAt(j)==',') 
      {
        mc[k++]=j;
      }
    }

    // Number of sattelites
    gloGPGGA.substring(mc[6]+1, mc[7]).toCharArray(x, 3); 

    Tft.drawString(x,r4,p1,2,color);

    // Height, meters 
    gloGPGGA.substring(mc[8]+1, mc[10]).toCharArray(x, 9);
    Tft.drawString(x,ScreenWidth-10*10,p4,2,color);

    //       break;
    //        }

    //        if (glo.startsWith("$GPVTG")) {
    k=0;             
    for (int j=0; j<gloGPVTG.length(); j++)
    {
      if (gloGPVTG.charAt(j)==',') 
      {
        mc[k++]=j;
      }
    }

    // Speed km\h
    gloGPVTG.substring(mc[6]+1, mc[7]).toCharArray(x, 6); 
    // Serial.println(gloGPVTG); //.substring(mc[7]+1, mc[8]));
    //  String glo1="199.9";
    //  glo1.toCharArray(x,6);          
    Tft.drawString(x,ScreenWidth-6*10,p2,2,color);

    //        break;
    //       }

    //  }

    // Serial.print(TCNT1);
    //Serial.print(" mem ");
    //Serial.println(freeRam());

  } 
  while (((timestart+interval_ms) > millis())&& (TCNT1 < CT_POROG)); // && (TCNT1 < CT_POROG)  && (TCNT1 < CT_POROG)

  //Serial.println("while");

  GM_imp=TCNT1;
  long timestop=millis(); 


  long timedelta=timestop-timestart;
  float sec=(float)timedelta/1000;

  int mkrh = (float)GM_imp/sec*18; // mkr\hour

  data[uk]=mkrh;

  //mkrh = 2200;

  Tft.drawString("imp       ",uk*2,0,4,color);
  // Tft.drawNumber(GM_imp, 80,0, 4, color);
  byte dx=random(20);
  byte dy=random(4);

  Tft.fillRectangle(0, 40, ScreenWidth, 36,  BLACK); 

  if(mkrh < 999) 
  {
    Tft.drawString("mkr\\h     ",dx,40+dy,4,color);
    Tft.drawNumber(mkrh, 130+dx,40+dy, 4,color);
  }
  else 
  {
    float mrh=(float)mkrh/1000;
    Tft.drawString("MR\\h     ",dx,40+dy,4,RED);
    Tft.drawFloat(mrh, 2, 130+dx,40+dy, 4,RED);
  }

  Serial.print(millis());
  Serial.print(", ");
  Serial.print(GM_imp);
  Serial.print(" imp, ");
  Serial.print(sec); //zamenit na (float)timedelta/1000
  Serial.print(" sec, ");
  Serial.print(mkrh);
  Serial.println(" mkr\\hour");

  // finding max in data
  datamax=0;
  for (i=0; i<60; i++)
  {
    if (data[i] > datamax)
    {
      datamax=data[i];
    }
  } 

  uk++;
  if(uk > 59) 
  {
    uk=0; 
    Tft.fillScreen(); 
    Tft.drawString("imp       ",0,0,4,color);
  } 
  uk1=uk;

  color2=random(0, 0xffff); 
  color1=random(0, 0xffff); 

  // drawVerticalLine( INT16U poX, INT16U poY, INT16U length,INT16U color)
  unsigned int ChartBegin=205; //170;
  unsigned int ChartEnd=ScreenHeight;
  unsigned int ChartHeight=ChartEnd-ChartBegin;

  for (i=0; i < 60; i++) 
  {
    unsigned int current_data=(float)data[uk1]*ChartHeight/datamax; //normir  
    unsigned int xbegin=i*StepX;
    //    unsigned int xend=xbegin+StepX; //2;
    //   unsigned int ybegin=ScreenHeight-current_data; //150;
    int Ca=ChartHeight-current_data;
    //     Tft.drawVerticalLine( xbegin, ChartBegin, Ca, color2);
    //    Tft.drawVerticalLine( xbegin, ChartBegin+Ca, current_data, color1);
    Tft.fillRectangle(xbegin, ChartBegin, StepX, Ca, color2);
    Tft.fillRectangle(xbegin, ChartBegin+Ca, StepX, current_data, color1);

    //     Tft.fillRectangle(xbegin, ybegin, 4, current_data,  color2); 

    //     int yd;
    //     yd=ScreenHeight-ChartHeight-current_data;
    // if (yd > 0) {
    //   Tft.fillRectangle(xbegin, ChartHeight, StepX, yd,  color1); 
    //  }
    uk1++;
    if (uk1 > max_data) 
    {
      uk1 = 0;
    } // проверить - куда показывает после отрисовки всего массива
  }
  Tft.drawString("Max mkr\\h     ",uk,ChartBegin-17,2,YELLOW);
  Tft.drawNumber(datamax, 120+uk,ChartBegin-17, 2,YELLOW);
  Tft.drawString("Sergey Dronsky (C) 2014",uk*2,ScreenHeight-8,1,color++);

  //Serial.print(" mem ");
  //Serial.println(freeRam());
}

/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/


