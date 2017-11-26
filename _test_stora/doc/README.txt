https://geektimes.ru/post/295469/

/usr/bin/avrdude
-c arduino -p m328p -P /dev/ttyACM0 -U flash:w:../bin/led-blink.hex:i
