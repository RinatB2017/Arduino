//--------------------------------------------------------------
// File     : stm32_ub_lcd_st7783.c
// Datum    : 31.03.2013
// Version  : 1.6
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : GPIO,FSMC
// Funktion : Функция графического LCD (Контроллер - ST7783)
//            Доступ осуществляется через FSMC-контроллер
//            по 16 битной шине в режиме 8080 (5R6G5B = RGB565)
// Hinweis  : Дисплей использует следующие выводы процессора:
//             PB0  -> LCD_Backlight   PE3  -> LCD_RS
//             PD0  -> LCD_DB2         PE7  -> LCD_DB4
//             PD1  -> LCD_DB3         PE8  -> LCD_DB5
//             PD4  -> LCD_RD          PE9  -> LCD_DB6
//             PD5  -> LCD_WR          PE10 -> LCD_DB7
//             PD7  -> LCD_CS          PE11 -> LCD_DB10
//             PD8  -> LCD_DB15        PE12 -> LCD_DB11
//             PD9  -> LCD_DB16        PE13 -> LCD_DB12
//             PD10 -> LCD_DB17        PE14 -> LCD_DB13
//             PD14 -> LCD_DB0         PE15 -> LCD_DB14
//             PD15 -> LCD_DB1
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_lcd_st7783.h"



//--------------------------------------------------------------
// Внутренние функции
//--------------------------------------------------------------
void P_LCD7783_InitIO(void);
void P_LCD7783_InitFSMC(void);
void P_LCD7783_InitChip(uint16_t mode);
uint16_t P_LCD7783_ReadReg(uint8_t reg_adr);
void P_LCD7783_WriteReg(uint8_t reg_adr, uint16_t reg_value);
void P_LCD7783_Delay(volatile uint32_t nCount);


//--------------------------------------------------------------
// Инициализация LCD дисплея
// Return_wert :
//  -> ERROR   , когда дисплей не найден
//  -> SUCCESS , когда дисплей обнаружен (ID=7783)
//--------------------------------------------------------------
ErrorStatus UB_LCD_Init(void)
{ 
  ErrorStatus ret_wert=ERROR;
  uint16_t lcdid = 0;

  // инициализация IO-линий
  P_LCD7783_InitIO();        
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  // инициализация FSMC
  P_LCD7783_InitFSMC();
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  
  // Зачитать ID LCD
  lcdid = P_LCD7783_ReadReg(LCD_ST7783_REG_00);
  if(lcdid==LCD_ST7783_ID) {
    // Дисплей найден
    ret_wert=SUCCESS;
    // Инициализация ЖК-дисплея(портретный режим)
    P_LCD7783_InitChip(LCD_ST7783_PORTRAIT);
    LCD_DISPLAY_MODE=PORTRAIT;
    // Включение подсветки
    UB_LCD_Backlight_On();
  }  

  LCD_WINDOW.xstart=0;
  LCD_WINDOW.ystart=0;
  LCD_WINDOW.xend=LCD_MAXX-1;
  LCD_WINDOW.yend=LCD_MAXY-1;
  LCD_WINDOW.pixel=LCD_PIXEL;

  return(ret_wert);
}


//--------------------------------------------------------------
// установить курсор в позицию x, y
// и приготовиться к записи в видеопамять дисплея
//--------------------------------------------------------------
void UB_LCD_SetCursor2Draw(uint16_t xpos, uint16_t ypos)
{
  // установка курсора
  P_LCD7783_WriteReg(LCD_ST7783_REG_20, xpos);
  P_LCD7783_WriteReg(LCD_ST7783_REG_21, ypos);

  // задание адреса
  LCD_REG=LCD_ST7783_REG_22;
}


//--------------------------------------------------------------
// Если экран цветной
//--------------------------------------------------------------
void UB_LCD_FillScreen(uint16_t color)
{
  uint32_t n = 0;

  // установка курсора в 0
  UB_LCD_SetCursor2Draw(LCD_WINDOW.xstart,LCD_WINDOW.ystart);
  // описать полный экран
  for(n=0;n<LCD_WINDOW.pixel;n++) {
    LCD_RAM = color;
  }
}


//--------------------------------------------------------------
// Включить подсветку
//--------------------------------------------------------------
void UB_LCD_Backlight_On(void)
{
  GPIOB->BSRRH = GPIO_Pin_0;
}


//--------------------------------------------------------------
// Выключить подсветку
//--------------------------------------------------------------
void UB_LCD_Backlight_Off(void)
{
  GPIOB->BSRRL = GPIO_Pin_0;
}

//--------------------------------------------------------------
// Установка режима экрана
// должно быть сделанно сразу после инициализации
//
// Режим: [PORTRAIT=по умолчанию, LANDSCAPE]
//--------------------------------------------------------------
void UB_LCD_SetMode(LCD_MODE_t mode)
{
  if(mode==PORTRAIT) {
    P_LCD7783_InitChip(LCD_ST7783_PORTRAIT);
    LCD_DISPLAY_MODE=PORTRAIT;
  }
  else {
    P_LCD7783_InitChip(LCD_ST7783_LANDSCAPE);
    LCD_DISPLAY_MODE=LANDSCAPE;
  }
}


//--------------------------------------------------------------
// Установка окна для рисования на дисплее
// от xtart,ystart до xend,yend
//--------------------------------------------------------------
void UB_LCD_SetWindow(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
  P_LCD7783_WriteReg(LCD_ST7783_REG_50, xstart);
  P_LCD7783_WriteReg(LCD_ST7783_REG_51, xend);
  P_LCD7783_WriteReg(LCD_ST7783_REG_52, ystart);
  P_LCD7783_WriteReg(LCD_ST7783_REG_53, yend);

  LCD_WINDOW.xstart=xstart;
  LCD_WINDOW.ystart=ystart;
  LCD_WINDOW.xend=xend;
  LCD_WINDOW.yend=yend;
  LCD_WINDOW.pixel=(xend-xstart+1)*(yend-ystart+1);
}


//--------------------------------------------------------------
// Внутренняя функция
// Инициализации всех выводов IO для дисплея
//--------------------------------------------------------------
void P_LCD7783_InitIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  //-----------------------------------------
  // включение тактирования Port-B, Port-D и Port-E
  //-----------------------------------------
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  
  //-----------------------------------------
  // Инициализация выводов порта B
  //-----------------------------------------
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;              //PB0 -> включение подсветки
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // конфигурация порта B
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
  //-----------------------------------------
  // Инициализация выводов порта D
  //-----------------------------------------
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0,  GPIO_AF_FSMC); // PD0=FSMC_D2   -> DB2
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1,  GPIO_AF_FSMC); // PD1=FSMC_D3   -> DB3
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4,  GPIO_AF_FSMC); // PD4=FSMC_NOE  -> RD
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,  GPIO_AF_FSMC); // PD5=FSMC_NWE  -> WR
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource7,  GPIO_AF_FSMC); // PD7=FSMC_NE1  -> CS
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF_FSMC); // PD8=FSMC_D13  -> DB15
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF_FSMC); // PD9=FSMC_D14  -> DB16
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC); // PD10=FSMC_D15 -> DB17  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC); // PD14=FSMC_D0  -> DB0
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC); // PD15=FSMC_D1  -> DB1
  
  // структура порта D
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_14 | GPIO_Pin_15;
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  // конфигурация порта D
  GPIO_Init(GPIOD, &GPIO_InitStructure);   
  
  //-----------------------------------------
  // Инициализация выводов порта E
  //-----------------------------------------
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource3,  GPIO_AF_FSMC); // PE3=FSMC_A19  -> RS
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF_FSMC); // PE7=FSMC_D4   -> DB4
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8,  GPIO_AF_FSMC); // PE8=FSMC_D5   -> DB5  
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,  GPIO_AF_FSMC); // PE9=FSMC_D6   -> DB6
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC); // PE10=FSMC_D7  -> DB7
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC); // PE11=FSMC_D8  -> DB10
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC); // PE12=FSMC_D9  -> DB11
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC); // PE13=FSMC_D10 -> DB12
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC); // PE14=FSMC_D11 -> DB13
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC); // PE15=FSMC_D12 -> DB14

  // структура порта E
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |
                                GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 |
                                GPIO_Pin_14 | GPIO_Pin_15;
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  // конфигурация порта E
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
}

//--------------------------------------------------------------
// Внутренняя функция 
// Инициализация FSMC для дисплея
// CS на PD7=FSMC_NE1 = Bank-1 / PSRAM-1
//--------------------------------------------------------------
void P_LCD7783_InitFSMC(void)
{
  FSMC_NORSRAMInitTypeDef        FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTimingInitStructure;
  
  //-----------------------------------------
  // Включение тактирования на FSMC
  //-----------------------------------------
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);  
  
  //-----------------------------------------
  // Структура для таймера
  //-----------------------------------------  
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = LCD_ST7783_FSMC_AST;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 1;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = LCD_ST7783_FSMC_DST;
  FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;

  //-----------------------------------------
  // Структура для Bank-1 / PSRAM-1
  //-----------------------------------------  
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;  
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;  
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;  
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;  
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure; 
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
  
  // Конфигурация FSMC
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  
  // Включение Bank-1 / PSRAM-1
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

//--------------------------------------------------------------
// Внутренняя функция
// Инициализирует контроллер ST7783 по положению дисплея
// Режим: 0x1030 = портретная ориентация, 0x1038 = альбомная
//--------------------------------------------------------------
void P_LCD7783_InitChip(uint16_t mode)
{
  P_LCD7783_WriteReg(0x00FF,0x0001);
  P_LCD7783_WriteReg(0x00F3,0x0008);
  P_LCD7783_WriteReg(0x0001,0x0100);
  P_LCD7783_WriteReg(0x0002,0x0700);
  P_LCD7783_WriteReg(LCD_ST7783_REG_03,mode);   // портрет, альбом
  P_LCD7783_WriteReg(0x0008,0x0207);
  P_LCD7783_WriteReg(0x0009,0x0000);
  P_LCD7783_WriteReg(0x000A,0x0000);
  P_LCD7783_WriteReg(0x0010,0x0000);  
  P_LCD7783_WriteReg(0x0011,0x0005);
  P_LCD7783_WriteReg(0x0012,0x0000);
  P_LCD7783_WriteReg(0x0013,0x0000);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  P_LCD7783_WriteReg(0x0010,0x12B0);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  P_LCD7783_WriteReg(0x0011,0x0007);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  P_LCD7783_WriteReg(0x0012,0x008B);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  P_LCD7783_WriteReg(0x0013,0x1700);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  P_LCD7783_WriteReg(0x0029,0x0022);		
  P_LCD7783_WriteReg(0x0030,0x0000);
  P_LCD7783_WriteReg(0x0031,0x0707);
  P_LCD7783_WriteReg(0x0032,0x0505);
  P_LCD7783_WriteReg(0x0035,0x0107);
  P_LCD7783_WriteReg(0x0036,0x0008);
  P_LCD7783_WriteReg(0x0037,0x0000);
  P_LCD7783_WriteReg(0x0038,0x0202);
  P_LCD7783_WriteReg(0x0039,0x0106);
  P_LCD7783_WriteReg(0x003C,0x0202);
  P_LCD7783_WriteReg(0x003D,0x0408);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
  P_LCD7783_WriteReg(0x0050,0x0000); // Начало по-горизонтале
  P_LCD7783_WriteReg(0x0051,0x00EF); // Конец по-горизонтале
  P_LCD7783_WriteReg(0x0052,0x0000); // Начало по-вертикале
  P_LCD7783_WriteReg(0x0053,0x013F); // Конец по-вертикале
  P_LCD7783_WriteReg(0x0060,0xA700);		
  P_LCD7783_WriteReg(0x0061,0x0001);
  P_LCD7783_WriteReg(0x0090,0x0033);				
  P_LCD7783_WriteReg(0x002B,0x000B);		
  P_LCD7783_WriteReg(0x0007,0x0133);
  // небольшая пауза
  P_LCD7783_Delay(LCD_ST7783_PAUSE);
}

//--------------------------------------------------------------
// Внутренняя функция
// Чтение значения из реестра
//--------------------------------------------------------------
uint16_t P_LCD7783_ReadReg(uint8_t reg_adr)
{
  // Указать адрес
  LCD_REG = reg_adr;
  // Зачитать значение  
  return LCD_RAM;
}

//--------------------------------------------------------------
// Внутренняя функция
// Запись значения в реестр
//--------------------------------------------------------------
void P_LCD7783_WriteReg(uint8_t reg_adr, uint16_t reg_value)
{
  // Указать адрес
  LCD_REG = reg_adr;
  // записать значение
  LCD_RAM = reg_value;  
}


//--------------------------------------------------------------
// небольшая пауза
//--------------------------------------------------------------
void P_LCD7783_Delay(volatile uint32_t nCount)
{
  while(nCount--)
  {
  }
}
