//-------------------------------------------------------------
//
//-------------------------------------------------------------
const int leds[8] = { 31, 33, 35, 37, 39, 41, 43, 45 };
//-------------------------------------------------------------
union LED {
  uint8_t value;
  struct {
    unsigned bit_0: 1;
    unsigned bit_1: 1;
    unsigned bit_2: 1;
    unsigned bit_3: 1;
    unsigned bit_4: 1;
    unsigned bit_5: 1;
    unsigned bit_6: 1;
    unsigned bit_7: 1;
  } bites;
};
//-------------------------------------------------------------
void draw(uint8_t value)
{
  LED data;
  data.value = value;
  
  digitalWrite(leds[0], data.bites.bit_0);
  digitalWrite(leds[1], data.bites.bit_1);
  digitalWrite(leds[2], data.bites.bit_2);
  digitalWrite(leds[3], data.bites.bit_3);
  digitalWrite(leds[4], data.bites.bit_4);
  digitalWrite(leds[5], data.bites.bit_5);
  digitalWrite(leds[6], data.bites.bit_6);
  digitalWrite(leds[7], data.bites.bit_7);
}
//-------------------------------------------------------------
void setup(void)
{
  pinMode(12, OUTPUT); 
    
  for(int n=0; n<8; n++)
    pinMode(leds[n], OUTPUT); 
}
//-------------------------------------------------------------
int x = 1;
void loop(void)
{
  digitalWrite(12, true);
  delay(500);
  digitalWrite(12, false);
  delay(500);
  
  draw(x++);
}
//-------------------------------------------------------------

