// Тестировалось на Arduino IDE 1.0.1
#include <VirtualWire.h>

void setup(void)
{
  vw_set_ptt_inverted(true); // Необходимо для DR3100
  vw_setup(2000); // Устанавливаем скорость передачи (бит/с)
}

void loop(void)
{
  int number = 123;
  char symbol = 'c';
  
  String strMsg = "z ";
  strMsg += symbol;
  strMsg += " ";
  strMsg += number;
  strMsg += " ";
  
  char msg[255];
  
  strMsg.toCharArray(msg, 255);
  
  Serial.println(msg);
  
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Ждем пока передача будет окончена
  delay(200);
}
