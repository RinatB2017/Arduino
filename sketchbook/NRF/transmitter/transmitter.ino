//---------------------------------------------------------------
// передатчик
//---------------------------------------------------------------
// Библиотека для работы с SPI
#include <SPI.h>
// Файл с настройками для библиотеки RF24
#include <nRF24L01.h>
// Библиотека RF24
#include <RF24.h>
//---------------------------------------------------------------
// 9 и 10 - это номера пинов CE и CSN модуля nRF24L01+
RF24 radio(9, 10);
//---------------------------------------------------------------
//аналоговые пины
int analog_pin_1 = A0;
int analog_pin_2 = A1;
int analog_pin_3 = A2;

//пины кнопок
int btn_1_pin = 7;
int btn_2_pin = 8;
int btn_3_pin = 9;
//---------------------------------------------------------------
int value_pin_1 = 0;
int value_pin_2 = 0;
int value_pin_3 = 0;
//---------------------------------------------------------------
void init_gpio()
{
  pinMode(btn_1_pin,  INPUT_PULLUP);
  pinMode(btn_2_pin,  INPUT_PULLUP);
  pinMode(btn_3_pin,  INPUT_PULLUP);
}
//---------------------------------------------------------------
void read_data()
{
  value_pin_1 = analogRead(analog_pin_1);
  value_pin_2 = analogRead(analog_pin_2);
  value_pin_3 = analogRead(analog_pin_3);
}
//---------------------------------------------------------------
bool check_btn_1()
{
  return (digitalRead(btn_1_pin) == LOW);
}
//---------------------------------------------------------------
bool check_btn_2()
{
  return (digitalRead(btn_2_pin) == LOW);
}
//---------------------------------------------------------------
bool check_btn_3()
{
  return (digitalRead(btn_3_pin) == LOW);
}
//---------------------------------------------------------------
void init_transmitter()
{
  // инициализация nRF24L01+
  radio.begin();
  // задаем канал для передачи данных (от 0 до 127)
  radio.setChannel(0);
  // Скорость передачи данных 1Мбит/сек.
  // Возможны: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setDataRate (RF24_1MBPS);
  // Мощность передатчика -6dBm.
  // Возможные мощности:
  // RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm,
  // RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm
  radio.setPALevel (RF24_PA_HIGH);
  // Открываем трубу с идентификатором 0x1234567890 для передачи данных
  // на одном канале можно открыть 6 разных труб
  // они должны отличаться только последним байтом
  radio.openWritingPipe (0x1234567890LL);
}
//---------------------------------------------------------------
void pause()
{
  Serial.println("pause");
  delay(1000);
}
//---------------------------------------------------------------
void send_data(int address, int value)
{
  int data[2] = {0, 0};

  radio.setChannel(address);

  // отправляем данные
  radio.write(&value, sizeof(value));
}
//---------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("Init transmitter");

  init_gpio();
  init_transmitter();
}
//---------------------------------------------------------------
void loop()
{
  read_data();

  //передаем последовательно на 3 адреса (0..2)
  if (check_btn_1())
  {
    send_data(0, value_pin_1);
    send_data(1, value_pin_2);
    send_data(2, value_pin_3);
  }

  //ждем
  pause();
}
//---------------------------------------------------------------

