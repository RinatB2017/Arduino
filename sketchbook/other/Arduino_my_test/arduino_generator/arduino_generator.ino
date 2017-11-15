//---------------------------------------------------------------
#include <Modbusino.h>
//---------------------------------------------------------------
#define MAX_REG     64
const int regs = MAX_REG;  // количество регистров
uint16_t tab_reg[regs];    // задаем массив регистров

#define MAX_BUFFER  512
uint16_t buf[MAX_BUFFER];

const int ID_slave = 1;

// Инициализация SLAVE, идентификатор (адрес) в сети ID = 1
ModbusinoSlave modbusino_slave(ID_slave);

uint16_t value = 0;
int index_regs = 0;
//---------------------------------------------------------------
void setup() 
{
  modbusino_slave.setup(115200);
  for(int n=0; n<MAX_BUFFER; n++)
  {
    buf[n] = n;
  }
}
//---------------------------------------------------------------
void loop() 
{
  modbusino_slave.loop(tab_reg, regs);
/*  
  if(index_regs < (MAX_BUFFER - MAX_REG)) 
  {
    index_regs+=MAX_REG;
  }
  else 
  {
    index_regs = 0;
  }
*/  
  for(int n=0; n<MAX_REG; n++)
  {
    tab_reg[n]=buf[index_regs+n];
  }
}
//---------------------------------------------------------------

