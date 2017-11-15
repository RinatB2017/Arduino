//---------------------------------------------------------------
#define RESET_PIN     11
#define RESTORE_PIN   12

#define SPEED_115200  115200
#define SPEED_57600   57600
#define SPEED_38400   38400
#define SPEED_28800   28800
#define SPEED_19200   19200
#define SPEED_14400   14400
#define SPEED_9600    9600

#define MAX_LEN  1024
char input_buf[MAX_LEN];
int input_buf_index;
//---------------------------------------------------------------
void reset(void)
{
  Serial.println("reset");
  digitalWrite(RESET_PIN, LOW);
  delay(200);
  digitalWrite(RESET_PIN, HIGH);
  delay(100);
}
//---------------------------------------------------------------
void hard_reset(void)
{
  Serial.println("hard reset");
  digitalWrite(RESET_PIN, LOW);
  delay(7000);
  digitalWrite(RESET_PIN, HIGH);
  delay(100);
}
//---------------------------------------------------------------
void restore_default(void)
{
  Serial.println("restore default");
  digitalWrite(RESTORE_PIN, LOW);
  delay(200);
  digitalWrite(RESTORE_PIN, HIGH);
  delay(100);
}
//---------------------------------------------------------------
void setup() 
{
  Serial.begin(SPEED_9600);
  Serial.println("Test Begin");

  Serial1.begin(SPEED_115200);

  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);

  pinMode(RESTORE_PIN, OUTPUT);
  digitalWrite(RESTORE_PIN, HIGH);
  delay(1000);
}
//---------------------------------------------------------------
void clean_buf(void)
{
  for(int n=0; n<MAX_LEN; n++)
    input_buf[n] = 0;
}
//---------------------------------------------------------------
int data_receive(void)
{
  uint8_t i;
  uint8_t s;

  input_buf_index = 0;
  while(true) 
  {
    if(!Serial1.available()) 
    {
      i = 0;
      while (!Serial1.available()) 
      {
        delay(1);
        if (++i == 100) 
        {
          /* Too late, bye */
          return -1;
        }
      }
    }
    s = Serial1.read();
    if(s > 0)
    {
      if(input_buf_index < MAX_LEN)
      {
        input_buf[input_buf_index] = s;
        input_buf_index++;
      }
    }
  }
  return input_buf_index;
}
//---------------------------------------------------------------
void loop() 
{
  Serial.println("waiting 10 second...");
  delay(10000);
  reset();
  
#if 0
  hard_reset();
#endif

#if 0
  restore_default();
#endif  
  
#if 0
  reset();
  restore_default();
  Serial1.print("at+uart=57600,8,n,1 \r\n");
  delay(1000);
#endif  

  while(1)
  {
    Serial.println("Send cmd");
    //Serial1.print("at+remoteip=? \r");
    //Serial1.print("at+dhcpd_eip=? \r");
    //Serial1.print("at+net_eip=? \r");
    //Serial1.print("at+remotepro=? \r");
    //Serial1.print("at+netmode=? \r");
    //Serial1.print("at+wifi_conf=? \r");
    Serial1.print("at+ver=? \r");
    //Serial1.write("at+uart=? \r");
    //Serial1.print("at+Get_MAC=? \r");

    clean_buf();
    input_buf_index = 0;
    data_receive();
    if(input_buf_index > 0)
    {
      Serial.println(input_buf);
    }
    delay(1000);
  }
}
//---------------------------------------------------------------







