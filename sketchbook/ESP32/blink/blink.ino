
#include "lcd.h"

void setup() {
  lcd_init();
}

void loop() {
  lcd_clear();
  lcd_print_str(0, "11111111111111");
  lcd_print_str(1, "11111111111111");
  lcd_print_str(2, "11111111111111");
  lcd_print_str(3, "11111111111111");
  delay(500);

  lcd_clear();
  lcd_print_str(0, "00000000000000");
  lcd_print_str(1, "00000000000000");
  lcd_print_str(2, "00000000000000");
  lcd_print_str(3, "00000000000000");
  delay(500);
}
