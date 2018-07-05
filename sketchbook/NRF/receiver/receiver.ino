//---------------------------------------------------------------
// приемник
//---------------------------------------------------------------
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//---------------------------------------------------------------
RF24 radio(9, 10);
//---------------------------------------------------------------
//адресные пины
int address_pin_0 = 2;
int address_pin_1 = 3;

//пин шима
int pin_output = 5;

int divider = 5;

uint16_t old_data = 0;
//---------------------------------------------------------------
#pragma pack (push, 1)

union U_BYTE
{
  uint8_t value;
  struct
  {
    uint8_t bit0: 1;
    uint8_t bit1: 1;
    uint8_t bit2: 1;
    uint8_t bit3: 1;
    uint8_t bit4: 1;
    uint8_t bit5: 1;
    uint8_t bit6: 1;
    uint8_t bit7: 1;
  } bites;
};

#pragma pack(pop)
//---------------------------------------------------------------
void init_gpio()
{
  pinMode(address_pin_0,  INPUT_PULLUP);
  pinMode(address_pin_1,  INPUT_PULLUP);

  pinMode(pin_output, OUTPUT);
  analogWrite(pin_output, 1023 / divider);
}
//---------------------------------------------------------------
int get_address()
{
  union U_BYTE temp;
  temp.value = 0;
  temp.bites.bit0 = (digitalRead(address_pin_0) == LOW);
  temp.bites.bit1 = (digitalRead(address_pin_1) == LOW);
  return temp.value;
}
//---------------------------------------------------------------
void init_receiver()
{
  // инициализация nRF24L01+
  radio.begin();
  // задаем канал для приёма данных. Идентично передатчику
  radio.setChannel(get_address());
  Serial.println(get_address()); //посмотреть адрес
  // Скорость передачи данных. Идентично передатчику
  radio.setDataRate (RF24_1MBPS);
  // Мощность передатчика. Идентично передатчику
  radio.setPALevel (RF24_PA_HIGH);
  // Открываем 1 трубу с идентификатором 0x1234567890
  radio.openReadingPipe (1, 0x1234567890LL);
  // Включаем приемник и слушаем открытую трубу
  radio.startListening ();
}
//---------------------------------------------------------------
void setup()
{
  // монитор порта
  Serial.begin(9600);
  Serial.println("Init receiver");

  init_gpio();
  init_receiver();

  analogWrite(pin_output, 1023 / divider);
}
//---------------------------------------------------------------
void loop()
{
  uint16_t data = 0;

  // если что-то удалось получить
  if (radio.available())
  {
    // читаем данные
    radio.read(&data, sizeof(data));
    analogWrite(pin_output, data / divider);

    if (data != old_data)
    {
      old_data = data;
      Serial.println("value " + String(data / divider));
    }
  }
}
//---------------------------------------------------------------

