//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'
//--------------------------------------------------------------------------------
// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5, 4);
//--------------------------------------------------------------------------------
void lcd_init() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
}
//--------------------------------------------------------------------------------
void lcd_clear() {
  display.clear();
}
//--------------------------------------------------------------------------------
void lcd_print(int x, int y, String text) {
  /*
    "WWWWWWWW0"
    "wwwwwwwwww0"
    "01234567890123"
  */

  display.setColor(WHITE);
  //display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(x, y, text);
  display.display();
}
//--------------------------------------------------------------------------------
void lcd_print_str(int num_str, String text) {
  if (num_str > 3) num_str = 3;
  switch (num_str)
  {
    case 0:
      lcd_print(0, 0,  text);
      break;

    case 1:
      lcd_print(0, 15,  text);
      break;

    case 2:
      lcd_print(0, 30,  text);
      break;

    case 3:
      lcd_print(0, 45,  text);
      break;
  }
}
//--------------------------------------------------------------------------------
void lcd_draw_led(int x, int y, int r, bool on) {
  if (on)
    display.setColor(WHITE);
  else
    display.setColor(BLACK);
    
  for (int n = 0; n < (r - 1); n++) {
    display.drawCircle(x, y, n);
  }
  display.setColor(WHITE);
  display.drawCircle(x, y, r);

  display.display();
}
//--------------------------------------------------------------------------------
