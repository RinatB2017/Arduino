/* SFE_BMP180 library example sketch
Hardware connections:
- (GND) to GND
+ (VDD) to 3.3V
(WARNING: do not connect + to 5V or the sensor will be damaged!)
You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:
Any Arduino pins labeled:  SDA  SCL
Uno, Redboard, Pro:        A4   A5
Mega2560, Due:             20   21
Leonardo:                   2    3
*/

#include <Wire.h>
#include <SPI.h>
#include "nRF24L01.h"  // Беcпроводной модуль надо использовать библиотеку http://tmrh20.github.io/RF24
#include "RF24.h"      // Беcпроводной модуль используются не стандартные функции https://github.com/TMRh20

// - ОПЦИИ  при сборке окончательной версии все отключить-----------------------------
//#define LOG                                     // Признак записи лога в еепром
//#define DEBUG                                   // Отладочную  информацию в ком порт посылает  и есть меню управления логом должен быть включен #define LOG 
//#define DEMO                                    // Признак демонстрации - данные с датчиков генерятся рандом и быстрее

// Константы
#define VERSION_DATA "121215"                   // Дата текущей версии  в формате ДДММГГ
#define VERSION      "0.25"                     // Текущая версия прошивки
#define ID            0x31                      // уникально Идентификатор устройства (тип) - старшие 4 бита, вторые (младшие) 4 бита серийный номер устройства
#define LABEL "BM-180"                          // Название блока
#define NRF24_CHANEL  100                       // Номер канала nrf24

/* Memory Map */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

// Макросы для работы с портами  скорость и место
#define SetOutput(port,bit)       DDR ## port |= _BV(bit)
#define SetInput(port,bit)        DDR ## port &= ~_BV(bit)
#define SetBit(port,bit)          PORT ## port |= _BV(bit)
#define ClearBit(port,bit)        PORT ## port &= ~_BV(bit)
#define WritePort(port,bit,value) PORT ## port = (PORT ## port & ~_BV(bit)) | ((value & 1) << bit)
#define ReadPort(port,bit)        (PIN ## port >> bit) & 1
#define PullUp(port,bit)          { SetInput(port,bit); SetBit(port,bit); }
#define Release(port,bit)         { SetInput(port,bit); ClearBit(port,bit); }

// Ноги куда подключаем переферию
#define PIN_CE          7                       // nrf24 ce
#define PIN_CSN         6                       // nrf24 csn
#define PIN_VCC_BMP180  10                      // Нога питания ВМР180 использую SetOutput(B,2)
#define PIN_SDA_BMP180  A4                      // Нога SDA ВМР180 
#define PIN_SCL_BMP180  A5                      // Нога SCL ВМР180 


// - ВРЕМЕНА ---------------------------------------
#ifdef DEMO                                     // Для демо все быстрее
    #define TIME_WDT SLEEP_2S                   // Период сторожевого таймера
    #define TIME_SCAN_SENSOR 2                  // Время опроса датчиков в 8 секундных интервалах (сторожевого таймера)
    #define TIME_SEND_SENSOR 4                  // Время посылки данных (равно усреднению)
#else   
    #define TIME_WDT SLEEP_8S                   // Период сторожевого таймера
    #define TIME_SCAN_SENSOR 9                  // Время опроса датчиков в 8 секундных интервалах (сторожевого таймера)
    #define TIME_SEND_SENSOR 4                  // Время посылки данных (равно усреднению) 288 секунд почти пять минут
#endif

// АЦП ----------------------------------------
const long ConstADC=1126400;                    // Калибровка встроенного АЦП (встроенный ИОН) по умолчанию 1126400

// Переменные которые сохраняются в памяти без инициализации
int S8_tick __attribute__((section(".noinit")));           // число 8 секундных интервалов с последнего измерения
unsigned long tt __attribute__((section(".noinit")));      // Время пришедшее от головного блока если 0 то время не приходило
// Пакет передаваемый, используется также для хранения УСРЕДНЕННЫХ результатов. 

RF24 radio(PIN_CE, PIN_CSN);        // определение управляющих ног радиомодуля

void setup()
{  char ch;
   S8_tick=0;
   tt=0;
   
   Serial.begin(115200); 
   Serial.flush();
   
 // 2.Инициализация радиомодудя
   char buf[10];
   if (setRadio()==true)     // радио проинициализировано удачно 
    {                
       Serial.println(F("OK"));
       // внимание функция read_register сделана в библиотеке публичной
       sprintf(buf,"%02x",radio.read_register(CONFIG));    Serial.print(F("  3.1 Register CONFIG:     0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(SETUP_AW));  Serial.print(F("  3.2 Register SETUP_AW:   0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(SETUP_RETR));Serial.print(F("  3.3 Register SETUP_RETR: 0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(RF_CH));     Serial.print(F("  3.4 Register RF_CH:      0x")); Serial.println(buf); 
       sprintf(buf,"%02x",radio.read_register(RF_SETUP));  Serial.print(F("  3.5 Register RF_SETUP:   0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(NRF_STATUS));Serial.print(F("  3.6 Register NRF_STATUS: 0x")); Serial.println(buf);
       radio.powerUp();
    }
  else  // радио не работает
    {
       Serial.println(F("FAIL"));
    } 
}

void loop()
{
  unsigned long t=0;
  
  if ( radio.isAckPayloadAvailable() ) 
  {
    Serial.println("read...");
    radio.read(&tt,sizeof(t));
  }
}

//  Установка радиомодуля  -----------------------------------------------
bool setRadio(void)
{
   if (radio.begin()==false) radio.begin();  // Если модуль не стартует делаем еще попытку 
//   radio.setDataRate(RF24_250KBPS);         // выбор скорости RF24_250KBPS RF24_1MBPS RF24_2MBPS
   radio.setDataRate(RF24_2MBPS);         // выбор скорости RF24_250KBPS RF24_1MBPS RF24_2MBPS
   radio.setPALevel(RF24_PA_MAX);           // выходная мощность передатчика RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX,
   radio.setChannel(NRF24_CHANEL);          // тут установка канала
   radio.setCRCLength(RF24_CRC_16);         // использовать контрольную сумму в 16 бит
   radio.setAutoAck(true);                  // выключить аппаратное потверждение
// radio.enableDynamicPayloads();           // разрешить Dynamic Payloads
   radio.enableAckPayload();                // Разрешить ответ приемника AckPayload
   radio.setRetries(50,10);                 // Количество пауза и количество повторов 
  // Рекомендуют первые 2-4 байта адреса устанавливать в E7 или 18 он проще детектируется чипом
  radio.openWritingPipe(0xE7E7E7E7E1LL);    // передатчик 
  radio.openReadingPipe(1,0xE7E7E7E7D2LL);  // приемник
  radio.startListening();
  //radio.powerDown();
  return true;
}


