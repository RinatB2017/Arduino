/**
   The MIT License (MIT)

   Copyright (c) 2016 by Daniel Eichhorn

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

  This sketch created by JohnnyFRX 17Jun17
*/

#include <lcd_display.h>

void setup() {
  lcd_init();

  lcd_clear();
  //lcd_print(0, 0,  "WWWWWWWW0");
  //lcd_print(0, 15, "wwwwwwwwww0");
  //lcd_print(0, 30, "01234567890123");
  //lcd_print(0, 45, "String 3");

  lcd_print_str(0, "String 0");
  lcd_print_str(1, "String 1");
  lcd_print_str(2, "String 2");
  lcd_print_str(3, "String 3");
}

void loop() {

}

