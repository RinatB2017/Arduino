//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include <Wire.h>
#include <PCA9685.h>
//-------------------------------------------------------------------
PCA9685 ledDriver_0;
PCA9685 ledDriver_1; 
PCA9685 ledDriver_2;
//-------------------------------------------------------------------
byte address_0;
byte address_1;
byte address_2;
//-------------------------------------------------------------------
int delay_ms;
//-------------------------------------------------------------------
void test_0()
{
  for(int level=5; level>=0; level--)  
  {
    for(int i=0; i<16; i++)  
    {
      ledDriver_0.setLEDDimmed(i,level*20);
      delay(delay_ms);     
    }
  }
  for(int level=0; level<=5; level++)  
  {
    for(int i=0; i<16; i++)  
    {
      ledDriver_0.setLEDDimmed(i,level*20);
      delay(delay_ms);     
    }
  }
}
//-------------------------------------------------------------------
void test_1()
{
  for(int level=5; level>=0; level--)  
  {
    for(int i=0; i<16; i++)  
    {
      ledDriver_1.setLEDDimmed(i,level*20);
      delay(delay_ms);     
    }
  }
  for(int level=0; level<=5; level++)  
  {
    for(int i=0; i<16; i++)  
    {
      ledDriver_1.setLEDDimmed(i,level*20);
      delay(delay_ms);     
    }
  }
}
//-------------------------------------------------------------------
void test_2()
{
  for(int level=5; level>=0; level--)  
  {
    for(int i=0; i<16; i++)  
    {
      ledDriver_2.setLEDDimmed(i,level*20);
      delay(delay_ms);     
    }
  }
  for(int level=0; level<=5; level++)  
  {
    for(int i=0; i<16; i++)  
    {
      ledDriver_2.setLEDDimmed(i,level*20);
      delay(delay_ms);     
    }
  }
}
//-------------------------------------------------------------------
void setup()
{
  address_0 = 0x40;
  address_1 = 0x41;
  address_2 = 0x42;
  
  delay_ms = 100;
  
  Serial.begin(9600);
  Serial.println("Serial Started");
  
  Wire.begin();

  ledDriver_0.begin(address_0); 
  ledDriver_1.begin(address_1);
  ledDriver_2.begin(address_2);

  ledDriver_0.init();
  ledDriver_1.init();
  ledDriver_2.init();

  clear_all();
}
//-------------------------------------------------------------------
void clear_all()
{
  // 0   max
  // 100 min
  
  for(int i=0; i<16; i++)  
  {
    ledDriver_0.setLEDDimmed(i, 100);
    ledDriver_1.setLEDDimmed(i, 100);
    ledDriver_2.setLEDDimmed(i, 100);
  }
}
//-------------------------------------------------------------------
void loop()
{
  //test_0();
  //test_1();
  //test_2();
  
  //ledDriver_0.setLEDDimmed(0, 0);
  //ledDriver_0.setLEDDimmed(1, 0);
  //ledDriver_0.setLEDDimmed(2, 0);

  //ledDriver_1.setLEDDimmed(0, 0);
  //ledDriver_1.setLEDDimmed(1, 0);
  //ledDriver_1.setLEDDimmed(2, 0);

  //ledDriver_2.setLEDDimmed(0, 99);
  //ledDriver_2.setLEDDimmed(1, 99);
  //ledDriver_2.setLEDDimmed(2, 99);

  int value = 99;

  clear_all();
  for(int i=0; i<16; i++)  
  {
    ledDriver_0.setLEDDimmed(i, value);
  }
  delay(1000);

  clear_all();
  for(int i=0; i<16; i++)  
  {
    ledDriver_1.setLEDDimmed(i, value);
  }
  delay(1000);

  clear_all();
  for(int i=0; i<16; i++)  
  {
    ledDriver_2.setLEDDimmed(i, value);
  }
  delay(1000);

  //clear_all();
  //while(1)
  //{
  //}
} 
//-------------------------------------------------------------------

