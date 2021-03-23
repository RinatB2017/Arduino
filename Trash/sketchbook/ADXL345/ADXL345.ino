#include <SPI.h>

const byte READ = 0x80; // бит маркер чтения
const byte MB = 0x40; // бит MB (многобайтовая передача)
const int CS = 10; // пин выбора ведомого

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32); // делитель частоты 500 кГц
  SPI.setDataMode(SPI_MODE3); // задаём 3-ий режим SPI

  byte id[1];
  readRegister(0x00, 1, id); // читаем регистр DEVID
  Serial.print("ID = ");
  Serial.println(id[0], HEX);

  writeRegister(0x2D, 0x08); // переводим ADXL345 в режим измерения
}

void loop() {
  byte buff[6];
  readRegister(0x32, 6, buff); // читаем значения по осям X, Y, Z

  int x = ((int)buff[1] << 8) | buff[0];
  int y = ((int)buff[3] << 8) | buff[2];
  int z = ((int)buff[5] << 8) | buff[4];

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(z);

  delay(10);
}

// записывает значение в регистр
void writeRegister(byte reg, byte value) {
  digitalWrite(CS, LOW);
  SPI.transfer(reg);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

// читает из регистра заданное число байтов
void readRegister(byte reg, int bytesToRead, byte *outBuff) {
  digitalWrite(CS, LOW);
  reg = reg | READ; // покажем акселерометру, что хотим из него читать
  if (bytesToRead > 1) {
    reg = reg | MB; // и читать хотим много байтов
  }
  SPI.transfer(reg); // записываем адрес регистра, с которого начинаем чтение
  for (int i = 0; i < bytesToRead; i++) {
    outBuff[i] = SPI.transfer(0x00); // побайтно читаем ответ ADXL345
  }
  digitalWrite(CS, HIGH);
}
