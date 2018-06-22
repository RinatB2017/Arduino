// передатчик

// Библиотека для работы с SPI
#include <SPI.h>
// Файл с настройками для библиотеки RF24
#include <nRF24L01.h>
// Библиотека RF24
#include <RF24.h>

// 9 и 10 - это номера пинов CE и CSN модуля nRF24L01+
RF24 radio(9, 10);

void setup() {
  Serial.begin(9600);
  Serial.println("Init transmitter");

  // инициализация nRF24L01+
  radio.begin();
  // задаем канал для передачи данных (от 0 до 127)
  radio.setChannel(0);
  // Скорость передачи данных 1Мбит/сек.
  // Возможны: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setDataRate (RF24_1MBPS);
  // Мощность передатчика -6dBm.
  // Возможные можности:
  // RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm,
  // RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm
  radio.setPALevel (RF24_PA_HIGH);
  // Открываем трубу с идентификатором 0x1234567890 для передачи данных
  // на одном канале можно открыть 6 разных труб
  // они должны отличаться только последним байтом
  radio.openWritingPipe (0x1234567890LL);
}

void loop() {
  // массив для тестовых данных
  int data[2] = {0, 0};
  // читаем значение с аналогового пина для получения тестового числа
  data[0] = analogRead(0);
  // второе тестовое значение будет фиксированным
  data[1] = 80;
  // отправляем данные
  radio.write(&data, sizeof(data));

  Serial.println("send data...");
  delay(1000);
}
