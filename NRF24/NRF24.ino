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

#include <SFE_BMP180.h>
#include <Wire.h>
#include "LowPower.h"
#include <SPI.h>
#include "nRF24L01.h"  // Беcпроводной модуль надо использовать библиотеку http://tmrh20.github.io/RF24
#include "RF24.h"      // Беcпроводной модуль используются не стандартные функции https://github.com/TMRh20
#include "stmTime.h"   // Time library - https://github.com/PaulStoffregen/Time

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
 struct type_packet_0x30_NRF24                  // Версия 1.1!! адаптация для stm32 Структура передаваемого пакета 32 байта - 32 максимум
    {
        byte id=ID;                             // Идентификатор типа устройства - старшие 4 бита, вторые (младшие) 4 бита серийный номер устройства
        byte error=0;                           // Ошибка блока, пока резерв
        uint16_t  Vcc;                          // Напряжение батареи  Милливольты!!!!!
        int16_t  Temp;                          // Температура датчика  сотые градуса
        uint16_t  relH;                         // Относительная влажность датчика  сотые %
        uint16_t  absH;                         // Абсолютная влажность датчика сотые грамма на куб
        uint16_t  P;                            // Давление  милибары 
        uint16_t count=0;                       // Циклический счетчик пакетов 2 байта хватит на долго - около 3000 часов
        char ver[5] = VERSION;                  // Версия прошивки не более 4 байт + "0" символ 
        char note[13] = LABEL;                  // Примечание не более 12 байт + "0" байт Русские буквы в два раза меньше т.к. UTF-8
    } packet_0x30 __attribute__((section(".noinit")));


struct type_sensors   // структура для усреднения измерений
{      int16_t  num;                           // Число накопленных образцов
       int32_t  Vcc=0;                         // Напряжение батареи  Милливольты!!!!!
       int32_t  Temp=0;                        // Температура датчика  сотые градуса
       int32_t  relH=0;                        // Относительная влажность датчика  сотые %
       int32_t  absH=0;                        // Абсолютная влажность датчика сотые грамма на куб
       int32_t  P=0;                           // Давление  мбары
 } sensor __attribute__((section(".noinit")));

#ifdef LOG    // Структуры для записи лога
      #define NUM_LOG 80    // длина лога в записях!!!
      // Коды ошибок для записи в лог
      // Возвращаемые при инииализации датчика
      #define ERR_SENSOR_B1  1                 // error Data too long to fit in transmit buffer 
      #define ERR_SENSOR_B2  2                 // error Received NACK on transmit of address
      #define ERR_SENSOR_B3  3                 // error Received NACK on transmit of data
      #define ERR_SENSOR_B4  4                        // error Other error
      // Возвращаемые приработе датчика
      #define ERR_SENSOR_PR  5                 // error retrieving pressure measurement
      #define ERR_SENSOR_PS  6                 // error starting pressure measurement
      #define ERR_SENSOR_TR  7                 // error retrieving temperature measurement
      #define ERR_SENSOR_TS  8                 // error starting temperature measurement
      // Возвращаемые радио модулем ошибки
      #define ERR_NRF24_ASK  9                 // ASK не получен - обычно идет после ERR_NRF24_SEND
      #define ERR_NRF24_SEND 10                // Пакет не отправлен
     
      struct type_event     // Cтруктура для хранения одного события лога размер 5 байт.
      {
        unsigned long t;    // время последнего события 
        uint8_t err;        // коды ошибок
      };
      
      struct type_logs   // структура для хранения лога
      {
       bool flag_save=false;        // Признак необходимости записи в лог
       uint8_t  count=0;            // Указатель на последнюю запись в event
       uint16_t err_sensor=0;       // Общее число ошибок чтения датчика
       uint16_t err_nrf24=0;        // Общее число ошибок передачи
       unsigned long last_err=0;    // время последней ошибки
       unsigned long first_err=0;   // время первой  ошибки
       type_event  event[NUM_LOG];  // лог где встречается ошибка на каждую передачу одно число
      };
      
      type_logs logRAM __attribute__((section(".noinit"))); // Рабочая копия  в памяти
      type_logs logEEPROM EEMEM ;     // Копия в eeprom - туда пишем 
#endif 

SFE_BMP180 pressure;                //  датчик BMP180
RF24 radio(PIN_CE, PIN_CSN);        // определение управляющих ног радиомодуля

void setup()
{  char ch;
   S8_tick=0;
   tt=0;
   
   reset_sum();
   #ifdef LOG
     readEeprom();   // Чтение лога из еепром в память
   #endif
   // 1. Проверка питания  
    #ifdef  DEBUG  
    Serial.begin(115200); 
    Serial.flush();
    Serial.print(F("\n1. Version: "));
    Serial.print(F(VERSION));
    Serial.print(F(" "));
    Serial.println(F(VERSION_DATA));
    Serial.print(F("2. Battery voltage: "));
    Serial.println(((float)readVcc())/1000.0,2);
    Serial.print(F("3. NRF24 init . . .  "));
    Serial.flush();
  # endif 
  
 // 2.Инициализация радиомодудя
   char buf[10];
   if (setRadio()==true)     // радио проинициализировано удачно 
    {                
       #ifdef  DEBUG  
       Serial.println(F("OK"));
       // внимание функция read_register сделана в библиотеке публичной
       sprintf(buf,"%02x",radio.read_register(CONFIG));    Serial.print(F("  3.1 Register CONFIG:     0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(SETUP_AW));  Serial.print(F("  3.2 Register SETUP_AW:   0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(SETUP_RETR));Serial.print(F("  3.3 Register SETUP_RETR: 0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(RF_CH));     Serial.print(F("  3.4 Register RF_CH:      0x")); Serial.println(buf); 
       sprintf(buf,"%02x",radio.read_register(RF_SETUP));  Serial.print(F("  3.5 Register RF_SETUP:   0x")); Serial.println(buf);
       sprintf(buf,"%02x",radio.read_register(NRF_STATUS));Serial.print(F("  3.6 Register NRF_STATUS: 0x")); Serial.println(buf);
       #endif 
   //    radio.powerDown();  // Выключить радиомодуль
    }
  else  // радио не работает
    {
       #ifdef  DEBUG  
       Serial.println(F("FAIL"));
       #endif 
    } 
    
   // 3. Проверка сенсора ВМР180 
   Serial.print(F("4.  BMP180 init . . . "));
   if ( BMP180_ON()==true)
        { ;
          #ifdef  DEBUG  
          Serial.print(F(" OK\n"));
          Serial.flush();
          #endif
        }  
        else
        {  ;
          #ifdef  DEBUG 
          Serial.print(F(" FAIL, error:"));
          Serial.print(pressure.getError());
          Serial.print(F("\n"));
          Serial.flush();
           #endif
        } 
    BMP180_OFF();
   
  
   #ifdef  DEBUG 
   while(1)   // ДИАЛОГ ДЛЯ работы с логом
    { Serial.flush();
      Serial.println(F("\nThe available LOG commands: "));
      Serial.println(F("V - View log "));
      Serial.println(F("C - Clear log "));
      Serial.println(F("R - Clear log and RUN measurement"));
      Serial.println(F("G - RUN measurement"));
      Serial.print(F("Command? "));
 
      while(Serial.available()==0) {;} // Ждем команду
        ch=Serial.read();              // читаем первый байт
        Serial.print(F("'"));
        Serial.print(ch);
        Serial.print(F("'"));
        
        switch (ch)  // разбор команды
         {
          case 'V':
          case 'v':
            Serial.print(F("\n")); view_log();   break;
          case 'C':
          case 'c':
     //       Serial.print(F("\n")); clear_log();  break;
          case 'R':  
          case 'r':       
            Serial.print(F("\n")); clear_log();  break;
          case 'G':  
          case 'g':  
            Serial.print(F("\n"));  break;
          default: Serial.print(F(" unknown command.\n")); break; 
          } 
    if ((ch=='R')||(ch=='r')||(ch=='G')||(ch=='g')) break;          // Выход из цикла  
    while(Serial.available()>0) Serial.read();  // очистка входного буфера для новой итерации
    } 
    #endif
   // Ошибки датчика ВМР180 связанные с чтением шины i2c  возвращается СИМВОЛ!!! не число
   // 0 = Success
   // 1 = Data too long to fit in transmit buffer
   // 2 = Received NACK on transmit of address
   // 3 = Received NACK on transmit of data
   // 4 = Other error
   packet_0x30.error=pressure.getError()-'0'; // Ошибка в виде символа переводим в число 
   
   // Для проверки связи сразу посылаем пакет
   measurement();
   packet_0x30.Vcc=sensor.Vcc;
   packet_0x30.Temp=sensor.Temp;
   packet_0x30.relH=sensor.relH;
   packet_0x30.absH=sensor.absH;
   packet_0x30.P=sensor.P/10;
   sendRadio();  // Послать даннные  
   reset_sum(); 
   #ifdef  DEBUG  
    Serial.println(F("Start LOOP . . ."));
    Serial.flush();
   #endif  
}

void loop()
{
  if (S8_tick>=TIME_SCAN_SENSOR-1)   // Пора ли опрашивать датчик
  {
   #ifdef  DEBUG  
    Serial.print(F("PowerUp and scan sensor "));
   #endif  
   S8_tick=0;
   measurement();   // измерение
  } 
  else              
  {
    S8_tick++;         // добавляем счетчик
   #ifdef  DEBUG  
    Serial.print(F("PowerUp "));
    Serial.println(S8_tick);
    Serial.flush();
   #endif  
   } 
  
 if (sensor.num>=TIME_SEND_SENSOR)   // Пора посылать данные
  {
   // Усреднение 
   packet_0x30.Vcc=sensor.Vcc/TIME_SEND_SENSOR;
   packet_0x30.Temp=sensor.Temp/TIME_SEND_SENSOR;
   packet_0x30.relH=sensor.relH/TIME_SEND_SENSOR;
   packet_0x30.absH=sensor.absH/TIME_SEND_SENSOR;
   packet_0x30.P=(sensor.P/TIME_SEND_SENSOR)/10;
   reset_sum();
   sendRadio();  // Послать даннные
   } 
   
   LowPower.powerDown(TIME_WDT, ADC_OFF, BOD_OFF);   // СПАТЬ  
   tt=tt+8;           // Прошло 8 секунд только не для демо
}

// Чтение напряжения питания ----------------------------------------------
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = ConstADC / result; // Back-calculate AVcc in mV
  return result;
  
} 

//  Установка радиомодуля  -----------------------------------------------
bool setRadio(void)
{

   if (radio.begin()==false) radio.begin();  // Если модуль не стартует делаем еще попытку 
 //  radio.begin();
   radio.setDataRate(RF24_250KBPS);         // выбор скорости RF24_250KBPS RF24_1MBPS RF24_2MBPS
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
  radio.powerDown();
  return true;
 }
 
//  Посылка пакета ----------------------------------------
bool sendRadio(void)
{  unsigned long t=0;
   bool send_packet_ok=false;
  //  Включение чипа nrf24
  SetOutput(B,5);     // slk - выход сделать
  SetOutput(B,3);     // mosi - выход сделать
  SPI.begin();        // старт spi заново
  radio.powerUp();
  delay(1);               
  radio.stopListening();     // Остановить приемник перейти в режим передачи
  delay(2);                  // дать время на переключение
  cli();
  radio.writeBlocking(&packet_0x30,sizeof(packet_0x30),200);  // Writes 1 payload to the buffers
  send_packet_ok=radio.txStandBy();
  if ( radio.isAckPayloadAvailable() )            // Ждем получения -- основной блок передает текущее время
           radio.read(&tt,sizeof(t));             //... и имеем переменную tt с временем от приемника.
  #ifdef LOG         
      else save_err(ERR_NRF24_ASK);               // ответ не получен  запишем ошибку
  #endif      
  sei(); 
  if (t>0)  tt=t;                                 // Если пришел ответ обновить время
  #ifdef  DEBUG  
    if (send_packet_ok==true)  Serial.println(F("Packet sending ++++++++++"));
    else                       Serial.println(F("Packet NOT sending -----------"));
    Serial.flush();
   #endif   
   
   #ifdef LOG         
      if (send_packet_ok==false)  save_err(ERR_NRF24_SEND); //  пакет  не послан запишем ошибку
   #endif 
    
  //  Выключение чипа nrf24
  radio.powerDown();  // выключаем чип но это не все!!!
  SPI.end();          // выключаем SPI
  PullUp(B,5);        // slk - сделать входом и подтянуть к 3.3 вольтам
  PullUp(B,3);        // mosi - сделать входом и подтянуть к 3.3 вольтам
  packet_0x30.count++;   // при переполнении сам сбросится
 } 
 
void reset_sum(void)  // Сброс счетчиков накоплений
{  sensor.num=0;
   sensor.Vcc=0;
   sensor.Temp=0;
   sensor.relH=0;
   sensor.absH=0;
   sensor.P=0;  
}

// Измерение датчика -----------------------------------------------
bool measurement(void)
{
  char status;
  double T,P,p0,a;
  packet_0x30.error=0;
  
  if (BMP180_ON()==false) return false; // датчик не работает выходим
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    packet_0x30.error=pressure.getError();  // Запомнить ошибку 
    if (status != 0)
    {
      #ifdef  DEBUG  
      Serial.print(F("Temperature: "));
      Serial.print(T,2);
      #endif
       
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        packet_0x30.error=packet_0x30.error+8*(pressure.getError());  // Запомнить ошибку 
        if (status != 0)
        {;
          #ifdef  DEBUG 
          Serial.print(F(" C absolute pressure: "));
          Serial.print(P,2);
          Serial.println(F(" mb"));
          Serial.flush();
          #endif
         }
        else  
        {;
        #ifdef  DEBUG  
          Serial.println("error retrieving pressure measurement\n"); 
        #endif
        #ifdef LOG         
           save_err(ERR_SENSOR_PR); //  Ошибка чтения датчика
        #endif 
        }
      }
      else 
      {;
      #ifdef  DEBUG 
        Serial.println("error starting pressure measurement\n"); 
      #endif
      #ifdef LOG         
           save_err(ERR_SENSOR_PS); //  Ошибка чтения датчика
      #endif 
      }
    }
    else 
    {;
    #ifdef  DEBUG 
     Serial.println("error retrieving temperature measurement\n"); 
    #endif
    #ifdef LOG         
        save_err(ERR_SENSOR_TR); //  Ошибка чтения датчика
    #endif 
    }
  }
  else 
  {;
  #ifdef  DEBUG 
    Serial.println("error starting temperature measurement\n"); 
  #endif
  #ifdef LOG         
      save_err(ERR_SENSOR_TS);  //  Ошибка чтения датчика
  #endif 
  }
 BMP180_OFF();
if (packet_0x30.error==0)  // Если нет ошибок усредняем и копим сумму
{
   sensor.num++;
   sensor.Vcc=sensor.Vcc+readVcc();
   sensor.Temp=sensor.Temp+T*100;
   sensor.P=sensor.P+P*10;  
   return true;
}
return false;
} 

// Включение датчика BMP180 ----------------------------------
bool BMP180_ON(void)    
{   SetOutput(B,2);       // Подать питание
    SetBit(B,2); 
    //delay(5);
    if(pressure.begin()!=1) // Инициализация BMP180 
    {
     #ifdef LOG   
     save_err(pressure.getError()-'0'); // Если надо запишим ошибку 
     #endif  
     return false;
    } 
    else  return true;
 } 
 
// Выключение датчика BMP180 ---------------------------------
void BMP180_OFF(void)  
{
  PullUp(B,2);  
} 

#ifdef LOG  
// Запись счетчиков в Eeprom --------------------------------------------------
void writeEeprom()
{ 
  if (logRAM.flag_save==true)  // Если не было изменений то выходим без записи
  {
    logRAM.flag_save=false;              //  Сборосить флаг записи
    cli();   
    eeprom_write_block((const void*)&logRAM, (void*) &logEEPROM, sizeof(logRAM)); 
    sei();
  }

}
// Чтение счетчиков из Eeprom --------------------------------------------------
void readEeprom()
{
cli(); 
   eeprom_read_block((void*)&logRAM, (const void*) &logEEPROM, sizeof(logRAM)); 
sei();
}

// Запись ошибки в лог -----------------------------------------------
void save_err(int code)
{
 if (code<ERR_NRF24_ASK) logRAM.err_sensor++; else  logRAM.err_nrf24++;  // добавление счетчиков ошибок
 if (logRAM.first_err==0) logRAM.first_err=tt;
 logRAM.last_err=tt;
 logRAM.event[logRAM.count].t=tt;
 logRAM.event[logRAM.count].err=code;
 logRAM.count++;                               // счетчик записей увеличиваем
 if (logRAM.count==NUM_LOG) logRAM.count=0;    // делаем кольцевой буфер
 logRAM.flag_save=true;                        // Признак необходимости записи
 writeEeprom();                                // Запись в еепром
} 
#endif

#ifdef DEBUG
// Очистка лога  и запись его в еепром -----------------------------------------------
void clear_log(void)
{   int i;
    Serial.print(F("Erase logs . . . "));
    logRAM.err_sensor=0;
    logRAM.err_nrf24=0;
    logRAM.last_err=0;
    logRAM.first_err=0;
    logRAM.count=0;
    logRAM.flag_save=true;
    for (i=0;i<NUM_LOG;i++)
      {
      logRAM.event[i].t=0;
      logRAM.event[i].err=0;
      } 
    writeEeprom();
    Serial.println(F(" OK"));
//    Serial.flush();    
} 
// Вывод лога на экран -----------------------------------------------
void view_log(void)
{   int i, x;
    Serial.println(F("\n- LOG  ----------"));
    Serial.print(F("Number error read sensor: ")); Serial.println(logRAM.err_sensor);
    Serial.print(F("Number error nrf24: ")); Serial.println(logRAM.err_nrf24);
    Serial.print(F("Time first error: "));// Serial.println(logRAM.first_err);
      Serial.print(day(logRAM.first_err)); Serial.print(F("/"));
      Serial.print(month(logRAM.first_err)); Serial.print(F("/")); 
      Serial.print(year(logRAM.first_err)); Serial.print(F(" "));
      Serial.print(hour(logRAM.first_err)); Serial.print(F(":"));
      Serial.print(minute(logRAM.first_err)); Serial.print(F(":"));
      Serial.println(second(logRAM.first_err));
    Serial.print(F("Time last error: "));      //Serial.println(logRAM.last_err); 
      Serial.print(day(logRAM.last_err)); Serial.print(F("/"));
      Serial.print(month(logRAM.last_err)); Serial.print(F("/")); 
      Serial.print(year(logRAM.last_err)); Serial.print(F(" "));
      Serial.print(hour(logRAM.last_err)); Serial.print(F(":"));
      Serial.print(minute(logRAM.last_err)); Serial.print(F(":"));
      Serial.println(second(logRAM.last_err));  
    Serial.print(F("Count log event: ")); Serial.println(logRAM.count);
    Serial.println(F("Detals logs: "));
    if ((logRAM.count<NUM_LOG)&&(logRAM.err_sensor+logRAM.err_nrf24<=NUM_LOG)) x=logRAM.count; else x=NUM_LOG;  // если мало ошибок то выводим не весь лог
      for (i=0;i<x;i++)
   //     { Serial.print(i); Serial.print(F(". time:")); Serial.print(logRAM.event[i].t); Serial.print(F(" err:")); Serial.println(logRAM.event[i].err,HEX);}
    {  // дешефровка времени
      Serial.print(i); Serial.print(F(". Time:"));
      Serial.print(day(logRAM.event[i].t)); Serial.print(F("/"));
      Serial.print(month(logRAM.event[i].t)); Serial.print(F("/")); 
      Serial.print(year(logRAM.event[i].t)); Serial.print(F(" "));
      Serial.print(hour(logRAM.event[i].t)); Serial.print(F(":"));
      Serial.print(minute(logRAM.event[i].t)); Serial.print(F(":"));
      Serial.print(second(logRAM.event[i].t)); Serial.print(F(" "));
      Serial.print(F(" err:")); Serial.println(logRAM.event[i].err,HEX);
    } 
    
    if (logRAM.count==0)  Serial.println(F("Logs empty . . ."));
     
}
 #endif
 
