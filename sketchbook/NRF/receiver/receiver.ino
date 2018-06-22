// приемник

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10);

void setup() {
  // инициализация nRF24L01+
  radio.begin();
  // задаем канал для приёма данных. Идентично передатчику
  radio.setChannel(0);
  // Скорость передачи данных. Идентично передатчику
  radio.setDataRate (RF24_1MBPS);
  // Мощность передатчика. Идентично передатчику
  radio.setPALevel (RF24_PA_HIGH);
  // Открываем 1 трубу с идентификатором 0x1234567890
  radio.openReadingPipe (1, 0x1234567890LL);
  // Включаем приемник и слушаем открытую трубу
  radio.startListening ();

  // монитор порта
  Serial.begin(9600);
}

void loop() {
  // массив, для получения данных
  int data[2] = {};

  // если что-то удалось получить
  if (radio.available()) {
    // читаем данные
    radio.read(&data, sizeof(data));
    // вывод первого элемента массива
    Serial.print("data[0]: ");
    Serial.print(data[0]);

    // вывод второго элемента массива
    Serial.print(" data[1]: ");
    Serial.println(data[1]);
  }
}
