
//--------------------------------------------------------------------------------
#pragma pack (push, 1)
//--------------------------------------------------------------------------------
union LED
{
  uint32_t value;
  struct BODY
  {
    uint8_t alpha;
    uint8_t B;
    uint8_t G;
    uint8_t R;
  } body;
};
//--------------------------------------------------------------------------------
#pragma pack(pop)
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  
  LED led;
  led.value = 0x01020304;

  Serial.println(led.body.R);
  Serial.println(led.body.G);
  Serial.println(led.body.B);
  Serial.println(led.body.alpha);
}
//--------------------------------------------------------------------------------
void loop() 
{
  // put your main code here, to run repeatedly:

}
//--------------------------------------------------------------------------------

