//--------------------------------------------------------------
// File     : stm32_ub_lcd_st7783.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_LCD_ST7783_H
#define __STM32F4_UB_LCD_ST7783_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_fsmc.h"


//--------------------------------------------------------------
// Стандартные цвета
// 16-битный цветовой режим(R5G6B5) 
// Red   (5bit) -> Bit15-Bit11
// Green (6bit) -> Bit10-Bit5
// Blue  (5bit) -> Bit4-Bit0
//--------------------------------------------------------------
#define  RGB_COL_BLACK          0x0000
#define  RGB_COL_BLUE           0x001F
#define  RGB_COL_GREEN          0x07E0
#define  RGB_COL_RED            0xF800
#define  RGB_COL_WHITE          0xFFFF

#define  RGB_COL_CYAN           0x07FF
#define  RGB_COL_MAGENTA        0xF81F
#define  RGB_COL_YELLOW         0xFFE0

#define  RGB_COL_GREY           0xF7DE


//--------------------------------------------------------------
// Режим дисплея
//--------------------------------------------------------------
typedef enum {
  PORTRAIT =0,
  LANDSCAPE
}LCD_MODE_t;
LCD_MODE_t  LCD_DISPLAY_MODE;


//--------------------------------------------------------------
// Параметры окна дисплея
//--------------------------------------------------------------
typedef struct {
  uint16_t xstart;
  uint16_t ystart;
  uint16_t xend;
  uint16_t yend;
  uint32_t pixel;
}LCD_WINDOW_t;
LCD_WINDOW_t LCD_WINDOW;


//--------------------------------------------------------------
// Адреса доступа от FSMC к экрану
// Bank   = Bank-1 / PSRAM-1        => BaseAdr 0x60000000
// RS-Pin = PE3=FSMC_A19 = BitNr 19 => Offset  0x00100000
// (смотреть страницы 1316+1317 в мануале)
//--------------------------------------------------------------
#define LCD_REG  (*((volatile unsigned short *) 0x60000000)) // RS = 0
#define LCD_RAM  (*((volatile unsigned short *) 0x60100000)) // RS = 1
#define LCD_RAM_ADR   0x60100000  // Адрес в RAM

//--------------------------------------------------------------
// Определение дисплея
//--------------------------------------------------------------
#define  LCD_ST7783_ID  0x7783  // ID у ST7783
#define  LCD_MAXX  240          // Пикселей по оси X
#define  LCD_MAXY  320          // Пикселей по оси Y
#define  LCD_PIXEL  LCD_MAXX*LCD_MAXY
#define  LCD_ST7783_PAUSE   5000
#define  LCD_ST7783_FSMC_AST  9 // AdressSetupTime  (AST >= 9)
#define  LCD_ST7783_FSMC_DST  7 // DataSetupTime    (DST >= 7)
#define  LCD_ST7783_PORTRAIT  0x1030  // Режим = Portrait
#define  LCD_ST7783_LANDSCAPE 0x1038  // Режим = Landscape



//--------------------------------------------------------------
// Регистрация адреса контроллера дисплея
//--------------------------------------------------------------
#define  LCD_ST7783_REG_00  0x00   // Display-ID
#define  LCD_ST7783_REG_03  0x03   // Display-Mode
#define  LCD_ST7783_REG_20  0x20   // Cursor-Pos (X)
#define  LCD_ST7783_REG_21  0x21   // Cursor-Pos (Y)
#define  LCD_ST7783_REG_22  0x22   // RAM Start

#define  LCD_ST7783_REG_50  0x50   // X-Start
#define  LCD_ST7783_REG_51  0x51   // X-End
#define  LCD_ST7783_REG_52  0x52   // Y-Start
#define  LCD_ST7783_REG_53  0x53   // Y-End

//--------------------------------------------------------------
// Глобальная функция
//--------------------------------------------------------------
ErrorStatus UB_LCD_Init(void);
void UB_LCD_SetCursor2Draw(uint16_t xpos, uint16_t ypos);
void UB_LCD_FillScreen(uint16_t color);
void UB_LCD_Backlight_On(void);
void UB_LCD_Backlight_Off(void);
void UB_LCD_SetMode(LCD_MODE_t mode);
void UB_LCD_SetWindow(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend);


//--------------------------------------------------------------
#endif // __STM32F4_UB_LCD_ST7783_H
