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
//--------------------------------------------------------------------------------
#pragma pack (push, 1)

//union UINT16
//{
//  uint16_t value;
//  struct {
//    uint8_t a;
//    uint8_t b;
//    uint8_t c;
//    uint8_t d;
//  } bytes;
//};

#pragma pack(pop)
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
//--------------------------------------------------------------------------------
void convert_data(uint8_t input, char *output)
{
  switch (input)
  {
    case 0x00: *output = '0'; break;
    case 0x01: *output = '1'; break;
    case 0x02: *output = '2'; break;
    case 0x03: *output = '3'; break;
    case 0x04: *output = '4'; break;
    case 0x05: *output = '5'; break;
    case 0x06: *output = '6'; break;
    case 0x07: *output = '7'; break;
    case 0x08: *output = '8'; break;
    case 0x09: *output = '9'; break;
    case 0x0A: *output = 'A'; break;
    case 0x0B: *output = 'B'; break;
    case 0x0C: *output = 'C'; break;
    case 0x0D: *output = 'D'; break;
    case 0x0E: *output = 'E'; break;
    case 0x0F: *output = 'F'; break;
    default: break;
  }
}
//--------------------------------------------------------------------------------
//void convert_data_to_ascii(uint16_t value,
//                           uint8_t *a,
//                           uint8_t *b,
//                           uint8_t *c,
//                           uint8_t *d)
//{
//  UINT16 data16;
//  data16.value = value;
//
//  convert_data(data16.bytes.a, *a);
//  convert_data(data16.bytes.b, *b);
//  convert_data(data16.bytes.c, *c);
//  convert_data(data16.bytes.d, *d);
//}
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

  //  char a = 0;
  //  char b = 0;
  //  char c = 0;
  //  char d = 0;
  //
  //  convert_data_to_ascii(value,
  //                        &a,
  //                        &b,
  //                        &c,
  //                        &d);

  //PACKET packet;
  //packet.data = value;

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

