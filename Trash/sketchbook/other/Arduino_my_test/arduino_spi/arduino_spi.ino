//---------------------------------------------------------------
//#define USE_LCD
#define USE_SPI
//---------------------------------------------------------------
#ifdef USE_LCD
  #include <LiquidCrystal.h>
#endif
//---------------------------------------------------------------
#include <SimpleModbusSlave.h>
//---------------------------------------------------------------
#ifdef USE_LCD
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#endif  
//---------------------------------------------------------------
#define CMD_TO_DAC_WRITE_N_REGISTER             0b00000000
#define CMD_TO_DAC_UPDATE_DAC_REGISTER     	0b00001000
#define CMD_TO_DAC_WRITE_N_UPDATE_ALL_REG      	0b00010000
#define CMD_TO_DAC_WRITE_N_UPDATE_DAC_N_REG	0b00011000
#define CMD_TO_DAC_POWER_DOWN                   0b00100000
#define CMD_TO_DAC_RESET                                  0b00101000
#define CMD_TO_DAC_LDAC_REGISTER_SETUP      	0b00110000
#define CMD_TO_DAC_INTERNAL_REFERENCE       	0b00111000

#define ADRESS_SEL_IN_DAC_CHANNEL_A		0b00000000
#define ADRESS_SEL_IN_DAC_CHANNEL_B		0b00000001
#define ADRESS_SEL_IN_DAC_CHANNEL_ALL		0b00000111
//---------------------------------------------------------------
#define PIN_LDAC      7
#define PIN_CLR         6
//---------------------------------------------------------------
#define SPI_PORTX 	PORTB
#define SPI_DDRX 	DDRB

#define SPI_MISO	4 
#define SPI_MOSI	3
#define SPI_SCK		5
#define SPI_SS		2

uint16_t  value_U  = 0;
uint16_t  value_I   = 0;
//---------------------------------------------------------------
enum 
{     
  // The first register starts at address 0
  VALUE_U,     
  VALUE_I,  
  TOTAL_ERRORS,  
  TOTAL_REGS_SIZE
};
unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
//---------------------------------------------------------------
#ifdef USE_SPI
void SPI_Init(void)
{
    /*настройка портов ввода-вывода
    все выводы, кроме MISO выходы*/
    SPI_DDRX  |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS) | (0<<SPI_MISO);
    SPI_PORTX |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS) | (1<<SPI_MISO);

    /*разрешение spi,старший бит вперед,мастер, режим 0*/
    SPCR = (1<<SPE) | (1<<MSTR) | (0<<CPHA) | (0<<SPR1) | (1<<SPR0) | (1<<CPOL);  // рабочий вариант
    //SPCR = (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (1<<SPR1) | (0<<SPR0);
    SPSR = (0<<SPI2X);
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void SPI_WriteByte(uint8_t data)
{
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
/*Передача и прием одного байта данных по SPI*/
uint8_t SPI_ReadByte(uint8_t data)
{
    uint8_t report;
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    report = SPDR;
    return report; 
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
/* Передача нескольких байтов данных по SPI 
 *data – указатель на массив передаваемых данных, а num – размерность массива
*/
void SPI_WriteArray(uint8_t num, uint8_t *data)
{
  while(num--)
  {
      SPDR = *data++;
      while(!(SPSR & (1<<SPIF)));
  }
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_power_on(void)
{
  
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_ddr_select_second(bool state)
{

}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_select(bool state)
{
    if(state)
	SPI_PORTX |= (1<<SPI_SS); 
    else
	SPI_PORTX &= ~(1<<SPI_SS); 
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_set_U(uint16_t value_U)
{
    //disable_interrupt();
    dac_power_on();  // Включить источник

    // Для варианта ЦАП AD5663
    dac_ddr_select_second(0);
    dac_select(0);	// выставить выбор ЦАП напряжения и тока - низкий уровень
    delay(5);	// Без задержки вообще не происходит установка ЦАП
			// Сделано для надёжности работы при больших токах, 
                        // т.к. если ЦАП сбросится по питанию - сбросится и LDAC регистр
			// ЦАП принимает вторую команду только по перевыбора по линии SS
    SPI_WriteByte(CMD_TO_DAC_WRITE_N_UPDATE_DAC_N_REG | ADRESS_SEL_IN_DAC_CHANNEL_A);	        // Канал A-напряжение
    SPI_WriteByte((value_U >> 8) & 0xff);							// ст байт
    SPI_WriteByte(value_U & 0xff);								// мл байт
    dac_select(1);	
    delay(5);									                // сбросить выбор ЦАП
    //enable_interrupt();
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_set_I(uint16_t value_I)
{
    //disable_interrupt();
    dac_power_on();  // Включить источник

    // Для варианта ЦАП AD5663
    dac_ddr_select_second(0);
    dac_select(0);	// выставить выбор ЦАП напряжения и тока - низкий уровень
    delay(5);	 // Без задержки вообще не происходит установка ЦАП
			// Сделано для надёжности работы при больших токах, 
                        // т.к. если ЦАП сбросится по питанию - сбросится и LDAC регистр
			// ЦАП принимает вторую команду только по перевыбора по линии SS
    SPI_WriteByte(CMD_TO_DAC_WRITE_N_UPDATE_DAC_N_REG | ADRESS_SEL_IN_DAC_CHANNEL_B);	        // Канал B-ток
    SPI_WriteByte((value_I >> 8) & 0xff);							// ст байт
    SPI_WriteByte(value_I & 0xff);								        // мл байт
    dac_select(1);										                // сбросить выбор ЦАП
    delay(5);									                // сбросить выбор ЦАП
    //enable_interrupt();
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_power_off(void)
{
    dac_select(0);
    delay(5);
    //SPI_WriteByte(CMD_TO_DAC_LDAC_REGISTER_SETUP);
    SPI_WriteByte(CMD_TO_DAC_POWER_DOWN);
    SPI_WriteByte(0b00000000);
    SPI_WriteByte(0b00000011);
    dac_select(1);
    delay(5);
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void dac_reset(void)
{
    dac_select(0);
    delay(5);
    SPI_WriteByte(CMD_TO_DAC_RESET);
    SPI_WriteByte(0b00000000);
    SPI_WriteByte(0b00000000);
    dac_select(1);
    delay(5);									                // сбросить выбор ЦАП
}
#endif
//---------------------------------------------------------------
#ifdef USE_SPI
void draw_SPCR(void)
{
    unsigned char old_reg    = (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (1<<SPR1) | (0<<SPR0);
    unsigned char new_reg  = (1<<SPE) | (1<<MSTR) | (0<<CPHA) | (0<<SPR1) | (1<<SPR0) | (1<<CPOL);  // включить SPI, первый - старший
    Serial.println(old_reg, HEX);
    Serial.println(new_reg, HEX);
}
#endif
//---------------------------------------------------------------
void setup(void)
{
  modbus_configure(&Serial, 
                    9600, 
                    SERIAL_8N1, 
                    1, 
                    2, 
                    TOTAL_REGS_SIZE, 
                    holdingRegs); 
  
#ifdef USE_LCD
    lcd.begin(16, 2);
#endif  
    Serial.begin(9600);
    
#ifdef USE_SPI
    SPI_Init();  
    
    pinMode(PIN_CLR, OUTPUT); 
    pinMode(PIN_LDAC, OUTPUT); 

    digitalWrite(PIN_LDAC, LOW);
    digitalWrite(PIN_CLR, LOW);
    
     //dac_power_off();
#endif     
}
//---------------------------------------------------------------
void loop(void)
{
    holdingRegs[TOTAL_ERRORS] = modbus_update();
  
    value_U = holdingRegs[VALUE_U];
    value_I = holdingRegs[VALUE_I];
    
#ifdef USE_LCD
    lcd.setCursor(0, 0);
    lcd.print("update ");
    lcd.print(holdingRegs[TOTAL_ERRORS]);
    lcd.print(" ");
    lcd.print(get_my_error());
    
    lcd.setCursor(0, 1);
    lcd.print(holdingRegs[VALUE_U]);
    lcd.print(' ');
    lcd.print(holdingRegs[VALUE_I]);
#endif  


#ifdef USE_SPI
    dac_set_U(value_U);
    dac_set_I(value_I);
#endif    
    
#if 0  
    sprintf(buf, "value_U %u value_I %u\n", value_U, value_I);
    Serial.write(buf);
    delay(100);  
#endif
}
//---------------------------------------------------------------

