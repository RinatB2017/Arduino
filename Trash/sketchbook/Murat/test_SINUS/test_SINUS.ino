//---------------------------------------------------------------
#define MAX_LEN  360
unsigned char buf[MAX_LEN];
//---------------------------------------------------------------
void send_data(unsigned char data)
{
  PORTD = data;
}
//---------------------------------------------------------------
void setup(void) 
{
  DDRD = 0xFF;
}
//---------------------------------------------------------------
void test(void)
{
  for(int n=0; n<MAX_LEN; n++)
  {
    send_data(128 + 127*sin(float(n)*float(M_PI)/float(180.0)));
    //delay(1);
  }
}
//---------------------------------------------------------------
void test2(void)
{
  for(int n=0; n<MAX_LEN; n++)
  {
    buf[n] = 128 + 127*sin(float(n)*float(M_PI)/float(180.0));
  }
  while(1)
  {
    for(int n=0; n<MAX_LEN; n++)
    {
      send_data(buf[n]);
      delay(1);
    }
  }
}
//---------------------------------------------------------------
void loop(void) 
{
  //test();
  test2();
}
//---------------------------------------------------------------


