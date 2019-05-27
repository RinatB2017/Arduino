//--------------------------------------------------------------
// File     : main.c
// Datum    : 18.02.2013
// Version  : 1.1
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Funktion : Demo der LCD-Library (ST7783)
// Hinweis  : Diese zwei Files muessen auf 8MHz stehen
//              "cmsis_boot/stm32f4xx.h"
//              "cmsis_boot/system_stm32f4xx.c"
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_lcd_st7783.h"

int main(void)
{
  uint32_t n;

  SystemInit(); // Инициализация настроек кварца

  UB_LCD_Init(); // Инициализация LCD

  // Удалить цвета с дисплей
  UB_LCD_FillScreen(RGB_COL_BLUE);

  // Перемещение курсора
  UB_LCD_SetCursor2Draw(10,50);
  // Нарисовать красную линию
  for(n=0;n<100;n++) {
    LCD_RAM=RGB_COL_RED;
  }

  while(1)
  {

  }
}
