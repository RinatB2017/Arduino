//---------------------------------------------------------------
#if 0
Плата        Arduino
 SHDN  10  -  6
-CS    11  -  10
-SDI   12  -  11
-SDO   13  -  12
-CLK   14  -  13
 RS    15  -  7
 GND   16  -  
#endif
//---------------------------------------------------------------
//opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2
//---------------------------------------------------------------
//#define FAST_SPI
//---------------------------------------------------------------
#include <SPI.h>
//---------------------------------------------------------------
union DATA {
  uint8_t value;
  struct {
    unsigned data    : 6;
    unsigned address : 2;
  } bites;
};
//---------------------------------------------------------------
// set pin 10 as the slave select for the digital pot:
const int pin_CS = 10;
const int pin_SHDN = 6;
const int pin_RS   = 7;
//---------------------------------------------------------------
//---------------------------------------------------------------
char spi_transfer(volatile char data)
{
  SPDR = data;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
  {
  };
  return SPDR;                    // return the received byte
}
//---------------------------------------------------------------
void SPI_write(int value) 
{
  digitalWrite(pin_CS,LOW);
#ifdef FAST_SPI
  spi_transfer(value);
#else  
  SPI.transfer(value);
#endif  
  digitalWrite(pin_CS,HIGH); 
}
//---------------------------------------------------------------
int value = 0;
//---------------------------------------------------------------
void led_data(int address, int value)
{
  union DATA data;
  
  data.bites.address = address;
  data.bites.data    = value;
  SPI_write(data.value);
}
byte clr;
//---------------------------------------------------------------
void setup(void) 
{
  Serial.begin(9600);
  
  pinMode (pin_CS, OUTPUT);

  pinMode (pin_SHDN, OUTPUT);
  pinMode (pin_RS,   OUTPUT);
  
#ifdef FAST_SPI  
  SPCR = (1<<SPE)|(1<<MSTR);
  clr=SPSR;
  clr=SPDR;
  
  SPI_write(WREN);
#else  
  SPI.begin(); 
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
#endif

  digitalWrite(pin_SHDN, HIGH);
  digitalWrite(pin_RS,   HIGH);

  led_data(1, 63);
  led_data(2, 63);
  led_data(3, 63);
  led_data(4, 63);
}
//---------------------------------------------------------------
#if 0
void loop(void) 
{
  led_data(1, value);
  led_data(2, value);
  led_data(3, value);
  led_data(4, value);
  
  delay(5);
  value ++;
  if(value > 63) value = 0;
}
#endif
//---------------------------------------------------------------
//int addr = 1;
int addr = 4;
//---------------------------------------------------------------
void loop(void) 
{
  while(1)
  {
  led_data(addr, 0);
  //delay(100);
  led_data(addr, 63);
  //delay(100);
  }
}
//---------------------------------------------------------------

