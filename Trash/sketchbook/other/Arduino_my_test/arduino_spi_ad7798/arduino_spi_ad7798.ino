//---------------------------------------------------------------
#include <SPI.h>
//---------------------------------------------------------------
enum {
  ADDRESS_STATUS_REGISTER		= 0,
  ADDRESS_MODE_REGISTER			= 1,
  ADDRESS_CONFIGURATION_REGISTER	= 2,
  ADDRESS_DATA_REGISTER			= 3,
  ADDRESS_ID_REGISTER			= 4,
  ADDRESS_IO_REGISTER			= 5,
  ADDRESS_OFFSET_REGISTER		= 6,
  ADDRESS_FULL_SCALE_REGISTER		= 7
};

union COMMUNICATION_REG {
  uint8_t value;
  struct {
    unsigned CR0_1    : 2;
    unsigned CREAD    : 1;
    unsigned ADDRESS  : 3;
    unsigned RW	      : 1;
    unsigned WEN      : 1;
  } 
  bites;
};

union MODE_REG {
  uint16_t value;
  struct {
    unsigned FS0_3  : 4;
    unsigned MR4_11 : 8;
    unsigned PSW    : 1;
    unsigned MD0_2  : 3;
  } 
  bites;
};

#define RW_WRITE   0
#define RW_READ    1

#define WEN_WRITE  0
#define WEN_READ   1
//---------------------------------------------------------------
uint8_t data = 0;
const int ssPin = 10;
uint8_t state_mode = 0;
uint8_t state_divider = 0;
uint8_t state_bit_order = 0;
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  pinMode(ssPin, OUTPUT);
}
//---------------------------------------------------------------
void set_spi_mode(void)
{
  switch(state_mode)
  {
  case 0:
    Serial.print("mode 0 ");
    SPI.setDataMode(SPI_MODE0);
    break;

  case 1:
    Serial.print("mode 1 ");
    SPI.setDataMode(SPI_MODE1);
    break;

  case 2:
    Serial.print("mode 2 ");
    SPI.setDataMode(SPI_MODE2);
    break;

  case 3:
    Serial.print("mode 3 ");
    SPI.setDataMode(SPI_MODE3);
    break;

  default:
    Serial.print("UNKNOWN mode ");
    break;
  }
  //if(state_mode < 3) state_mode++;
  //else state_mode = 0;
}
//---------------------------------------------------------------
void set_spi_divider(void)
{
  switch(state_divider)
  {
  case 0:
    Serial.print("SPI_CLOCK_DIV2 ");
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    break;

  case 1:
    Serial.print("SPI_CLOCK_DIV4 ");
    SPI.setClockDivider(SPI_CLOCK_DIV4);
    break;

  case 2:
    Serial.print("SPI_CLOCK_DIV8 ");
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    break;

  case 3:
    Serial.print("SPI_CLOCK_DIV16 ");
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    break;

  case 4:
    Serial.print("SPI_CLOCK_DIV32 ");
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    break;

  case 5:
    Serial.print("SPI_CLOCK_DIV64 ");
    SPI.setClockDivider(SPI_CLOCK_DIV64);
    break;

  case 6:
    Serial.print("SPI_CLOCK_DIV128 ");
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    break;

  default:
    Serial.print("UNKNOWN divider ");
    break;
  }
  //if(state_divider < 6) state_divider++;
  //else state_divider = 0;
}
//---------------------------------------------------------------
void set_bit_order(void)
{
  switch(state_bit_order)
  {
  case 0:
    Serial.print("LSBFIRST ");
    SPI.setBitOrder(LSBFIRST);
    break;

  case 1:  
    Serial.print("MSBFIRST ");
    SPI.setBitOrder(MSBFIRST);
    break;

  default:
    Serial.print("UNKNOWN bit order ");
    break;
  }
  //if(state_bit_order < 2) state_bit_order++;
  //else state_bit_order = 0;
}
//---------------------------------------------------------------
void reset(void)
{
  digitalWrite(ssPin, LOW);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  digitalWrite(ssPin, HIGH);
}
//---------------------------------------------------------------
uint8_t show_ID(void)
{
  union COMMUNICATION_REG comm_reg;
  uint8_t ID = 0;

  digitalWrite(ssPin, LOW);

  comm_reg.value = 0;
  comm_reg.bites.RW  = RW_READ;    //1
  comm_reg.bites.WEN = WEN_WRITE;  //0
  comm_reg.bites.ADDRESS = ADDRESS_ID_REGISTER;

  SPI.transfer(comm_reg.value);
  delay(5);

  comm_reg.value = 0;
  comm_reg.bites.RW  = RW_WRITE;    //0
  comm_reg.bites.WEN = WEN_READ;    //1
  comm_reg.bites.ADDRESS = ADDRESS_ID_REGISTER;

  ID = SPI.transfer(comm_reg.value);
  delay(5);

  digitalWrite(ssPin, HIGH);

  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  return ID;
}
//---------------------------------------------------------------
void set_mode(void)
{
  union COMMUNICATION_REG comm_reg;
  union MODE_REG mode_reg;

  digitalWrite(ssPin, LOW);

  comm_reg.value = 0;
  comm_reg.bites.RW  = RW_WRITE;
  comm_reg.bites.WEN = WEN_READ;
  comm_reg.bites.ADDRESS = ADDRESS_MODE_REGISTER;

  SPI.transfer(comm_reg.value);
  delay(5);

  mode_reg.value = 0;
  mode_reg.bites.MD0_2 = 2;
  mode_reg.bites.PSW = 1;
  mode_reg.bites.FS0_3 = 15;
  SPI.transfer(mode_reg.value);
  delay(5);
  
  digitalWrite(ssPin, HIGH);
}
//---------------------------------------------------------------
uint8_t test(uint8_t time_ms)
{
  uint8_t ID = 0;
  
  SPI.begin();
  //digitalWrite(ssPin, LOW);
  
#if 1  
  set_bit_order();
  set_spi_divider();
  set_spi_mode();
#else  
  // Для ЦАП необходимо, чтобы CPHA = 0 CPOL = 1
  // Для АЦП необходимо, чтобы CPHA = 1 CPOL = 1
  SPCR = (1<<SPE) | (1<<MSTR) | (0<<SPR1) | (1<<SPR0) | (1<<CPHA) | (1<<CPOL);
#endif  
  
  reset();
  delay(time_ms);
  
  set_mode();
  delay(time_ms);
  
  ID = show_ID();
  delay(time_ms);

  //digitalWrite(ssPin, HIGH);
  SPI.end();
  
  return ID;
}
//---------------------------------------------------------------
void loop(void)
{
  uint8_t ID = 0;
  int cnt = 0;
  int time_ms = 0;

#if 0  
  Serial.println("Begin");
  for(time_ms = 0; time_ms < 100; time_ms++)
  {
    ID = test(time_ms);
    if(ID) Serial.println(ID, HEX);
  }
  Serial.println("End!");
  while(1) ;
#endif  

  Serial.println("Begin");
  for(time_ms = 0; time_ms < 1000; time_ms++)
  {
    for(state_bit_order = 0; state_bit_order < 2; state_bit_order++)
    {
      for(state_divider = 0; state_divider < 7; state_divider++)
      {
        for(state_mode = 0; state_mode < 4; state_mode++)
        {
          Serial.print("cnt = ");
          Serial.print(cnt);
          Serial.print(" ");
          cnt++;
  
          ID = test(time_ms);
          if(((ID & 0x0F) == 8) || ((ID & 0x0F) == 9))
          {
            Serial.println(" ");
            Serial.println("########################## ");
            Serial.println(ID, HEX);
            Serial.println("########################## ");
            Serial.println(" ");
            while(1) ;
          }      
        }
      }
    }
  }
  Serial.println("End!");
  while(1) ;
}
//---------------------------------------------------------------








