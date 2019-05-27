//-------------------------------------------------------------------------------------
#define NOP_04_us __asm__ __volatile__("nop; nop; nop; nop; nop; nop;")
#define NOP_08_us __asm__ __volatile__("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;")

//#define NOP_04_us __asm__ __volatile__("nop; nop; nop;")
//#define NOP_08_us __asm__ __volatile__("nop; nop; nop; nop; nop; nop;")

#define RGB_ON     PORTD = (1 << PIN4);
#define RGB_OFF    PORTD = (0 << PIN4);

#define LED_ON     PORTB = (1 << PIN4);
#define LED_OFF    PORTB = (0 << PIN4);
//-------------------------------------------------------------------------------------
//NOP 62.5ns
//-------------------------------------------------------------------------------------
int outPin_LEDS = 4;
int outPin_LED  = 12;
//-------------------------------------------------------------------------------------
void set_1(void)
{
  RGB_ON;
  NOP_08_us;
  
  RGB_OFF;
  NOP_04_us;
}
//-------------------------------------------------------------------------------------
void set_0(void)
{
  RGB_ON;
  NOP_04_us;
  
  RGB_OFF;
  NOP_08_us;
}
//-------------------------------------------------------------------------------------
void treset(void)
{
  RGB_OFF;
  //delayMicroseconds(50);
  delay(50);
}
//-------------------------------------------------------------------------------------
void test(void)
{
  set_1(); set_0();
  set_1(); set_0();
  set_1(); set_0();
  set_1(); set_0();

  set_1(); set_0();
  set_1(); set_0();
  set_1(); set_0();
  set_1(); set_0();

  set_1(); set_0();
  set_1(); set_0();
  set_1(); set_0();
  set_1(); set_0();
}
//-------------------------------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);

  //pinMode(outPin_LEDS, OUTPUT);
  //pinMode(outPin_LED,  OUTPUT);
  
  DDRB = 0xFF;
  DDRD = 0xFF;
}
//-------------------------------------------------------------------------------------
void loop(void)
{
  Serial.println("loop()");
  
#if 0  
  unsigned long time1 = 0;
  unsigned long time2 = 0;
  
  time1 = micros();
  
  treset();
  test();
  treset();
  
  time2 = micros();
  Serial.print("Time ");
  Serial.print(time2 - time1);
  Serial.println(" msec");
#endif
  
  treset();
  while(1)
  {
    test();
    test();
    test();
    test();
    test();
    test();
    treset();
  
    LED_ON;
    delay(500);
    LED_OFF;
    delay(500);
  }
}
//-------------------------------------------------------------------------------------

