
#include "lcd.h"

void draw_1() {
  lcd_clear();
  lcd_print_str(0, "11111111111111");
  lcd_print_str(1, "11111111111111");
  lcd_print_str(2, "11111111111111");
  lcd_print_str(3, "11111111111111");
}

void draw_0() {
  lcd_clear();
  lcd_print_str(0, "00000000000000");
  lcd_print_str(1, "00000000000000");
  lcd_print_str(2, "00000000000000");
  lcd_print_str(3, "00000000000000");
}

void setup() {
  lcd_init();

  lcd_print_str(0, "test");
}

void loop() {
  //draw_1();
  draw_led(64, 32, 10, 1);
  delay(500);

  //draw_0();
  draw_led(64, 32, 10, 0);
  delay(500);
}
