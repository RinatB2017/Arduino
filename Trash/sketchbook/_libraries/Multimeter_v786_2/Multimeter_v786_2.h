/*********************************************************************************
**                                                                              **
**     Copyright (C) 2014                                                       **
**                                                                              **
**     This program is free software: you can redistribute it and/or modify     **
**     it under the terms of the GNU General Public License as published by     **
**     the Free Software Foundation, either version 3 of the License, or        **
**     (at your option) any later version.                                      **
**                                                                              **
**     This program is distributed in the hope that it will be useful,          **
**     but WITHOUT ANY WARRANTY; without even the implied warranty of           **
**     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            **
**     GNU General Public License for more details.                             **
**                                                                              **
**     You should have received a copy of the GNU General Public License        **
**     along with this program.  If not, see http://www.gnu.org/licenses/.      **
**                                                                              **
**********************************************************************************
**                   Author: Bikbao Rinat Zinorovich                            **
**********************************************************************************/
#ifndef MULTIMETER_V786_2_HPP
#define MULTIMETER_V786_2_HPP
//--------------------------------------------------------------------------------
enum
{
    E_NO_ERROR = 0,
    E_ERROR_MULTIMETR,
    E_ERROR_INDEX_NOT_CORRECT,
    E_ERROR_PORT_NOT_OPEN,
    E_ERROR_BREAK,
    E_ERROR_MAX_REPEAT,
    E_ERROR_NO_ANSWER,
    E_ERROR_BIG_ANSWER,
    E_ERROR_SMALL_ANSWER,
    E_ERROR_BAD_SERNO,
    E_ERROR_BAD_ADDRESS,
    E_ERROR_BAD_CRC,
    E_ERROR_BAD_CMD,
    E_ERROR_BAD_LEN,
    E_ERROR_UNKNOWN_CMD,
    E_UNKNOWN_ERROR,
    E_INVALID_FLOAT,
    E_INVALID_LIMIT,
    E_INVALID_DELTA,
    E_BREAK_MEASURING
};
//--------------------------------------------------------------------------------
union QUESTIONS_DATA_0_BYTE
{
    struct {
        unsigned char address;
        unsigned char channel;
        unsigned char cmd;
        unsigned char count;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union QUESTIONS_DATA_1_BYTE
{
    struct {
        unsigned char address;
        unsigned char channel;
        unsigned char cmd;
        unsigned char count;
        unsigned char step;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union QUESTIONS_DATA_2_BYTE
{
    struct {
        unsigned char address;
        unsigned char channel;
        unsigned char cmd;
        unsigned char count;
        unsigned char step_a;
        unsigned char step_b;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//--------------------------------------------------------------------------------
union BYTE_MEASURING
{
    unsigned char value;
    struct
    {
        unsigned limit:3;
        unsigned auto_limit:1;
        unsigned deviation:2; // отклонение
        unsigned retention:2; // удержание
    } data;
};

union BYTE_LIMITS
{
    unsigned char value;
    struct
    {
        unsigned limit:3;
        unsigned auto_limit:1;
        unsigned reserved:4;
    } data;
};

union BYTE_DEVIATION_RETENTION
{
    unsigned char value;
    struct
    {
        unsigned deviation:2;
        unsigned retention:2;
        unsigned reserved:4;
    } data;
};

typedef struct
{
    unsigned short SerialNo;
    unsigned short SerialYear;
} SERIAL;

typedef struct
{
    unsigned char address;
    unsigned char cmd;
    unsigned char count_data;
} B7_86_HEADER;

typedef struct
{
    B7_86_HEADER header;
    unsigned short crc16;
} B7_86_STATE;

typedef struct
{
    B7_86_HEADER header;
    char password[6];
    unsigned short crc16;
} B7_86_SERVICE;

typedef struct
{
    B7_86_HEADER header;
    SERIAL serial_year;
    char DisplaySymbols[7];
    unsigned char Range; // предел
    unsigned char Mode;  // режим
    unsigned char Math_Hold;
    unsigned short BattVoltage;
    unsigned short crc16;
} B7_86_STATE_ANSWER;

typedef struct
{
    B7_86_HEADER header;
    SERIAL serial_year;
    char DisplaySymbols[7];
    unsigned char limits;
    unsigned char deviation_retention;
    unsigned short crc16;
} B7_86_MEASURING;

typedef struct
{
    B7_86_HEADER header;
    SERIAL serial_year;
    unsigned short current;
    unsigned short voltage;
    unsigned short crc16;
} B7_86_BATTERY;

typedef struct
{
    B7_86_HEADER header;
    SERIAL serial_year;
    unsigned char err;
    unsigned short crc16;
} B7_86_ERROR;

typedef struct
{
    B7_86_HEADER header;
    unsigned char data_0;
    unsigned char data_1;
    unsigned short crc16;
} B7_86_CMD;

typedef struct
{
    B7_86_HEADER header;
    SERIAL serial_year;
    unsigned short crc16;
} B7_86_EMPTY;
//--------------------------------------------------------------------------------
#define CMD_GET_STATE                       0x01
#define CMD_GET_STATE_TEXT                  tr("Запрос статуса прибора.")

#define CMD_REMOTE_CONTROL_ON               0x02
#define CMD_REMOTE_CONTROL_ON_TEXT          tr("Включение удаленного управления")

#define CMD_REMOTE_CONTROL_OFF              0x03
#define CMD_REMOTE_CONTROL_OFF_TEXT         tr("Отключение удаленного управления")

#define CMD_SERVICE_ON                      0x04
#define CMD_SERVICE_ON_TEXT                 tr("Включение сервисных команд (защищено паролем)")

#define CMD_POWER_OFF                       0x05
#define CMD_POWER_OFF_TEXT                  tr("Отключение питания прибора")


#define CMD_MEASURING_DC_VOLTAGE            0x06
#define CMD_MEASURING_DC_VOLTAGE_TEXT       tr("Измерение напряжения постоянного тока")

#define CMD_MEASURING_AC_VOLTAGE            0x07
#define CMD_MEASURING_AC_VOLTAGE_TEXT       tr("Измерение напряжения переменного тока")

#define CMD_MEASURING_DC_CURRENT            0x08
#define CMD_MEASURING_DC_CURRENT_TEXT       tr("Измерение силы постоянного тока")

#define CMD_MEASURING_AC_CURRENT            0x09
#define CMD_MEASURING_AC_CURRENT_TEXT       tr("Измерение силы переменного тока")

#define CMD_MEASURING_R                     0x0A
#define CMD_MEASURING_R_TEXT                tr("Измерение сопротивления")

#define CMD_MEASURING_C                     0x0B
#define CMD_MEASURING_C_TEXT                tr("Измерение емкости")

#define CMD_MEASURING_L                     0x0C
#define CMD_MEASURING_L_TEXT                tr("Измерение индуктивности")

#define CMD_CONTINUITY                      0x0D
#define CMD_CONTINUITY_TEXT                 tr("Прозвонка цепи")

#define CMD_MEASURING_F                     0x0E
#define CMD_MEASURING_F_TEXT                tr("Измерение частоты")

#define CMD_MEASURING_ACTIVE_POWER          0x0F
#define CMD_MEASURING_ACTIVE_POWER_TEXT     tr("Измерение активной мощности")

#define CMD_MEASURING_REACTIVE_POWER        0x10
#define CMD_MEASURING_REACTIVE_POWER_TEXT   tr("Измерение реактивной мощности")

#define CMD_MEASURING_FULL_POWER            0x11
#define CMD_MEASURING_FULL_POWER_TEXT       tr("Измерение полной мощности")

#define CMD_MEASURING_POWER_FACTOR          0x12
#define CMD_MEASURING_POWER_FACTOR_TEXT     tr("Измерение коэффициента мощности")


#define CMD_CALIBRATION_DC_VOLTAGE          0x13
#define CMD_CALIBRATION_DC_VOLTAGE_TEXT     tr("Калибровка напряжения постоянного тока")

#define CMD_CALIBRATION_AC_VOLTAGE          0x14
#define CMD_CALIBRATION_AC_VOLTAGE_TEXT     tr("Калибровка напряжения переменного тока")

#define CMD_CALIBRATION_DC_CURRENT          0x15
#define CMD_CALIBRATION_DC_CURRENT_TEXT     tr("Калибровка силы постоянного тока")

#define CMD_CALIBRATION_AC_CURRENT          0x16
#define CMD_CALIBRATION_AC_CURRENT_TEXT     tr("Калибровка силы переменного тока")

#define CMD_CALIBRATION_R                   0x17
#define CMD_CALIBRATION_R_TEXT              tr("Калибровка сопротивления")


#define CMD_ENABLING_CHARGE                 0x18
#define CMD_ENABLING_CHARGE_TEXT            tr("Включение режима заряда АКБ")

#define CMD_DISABLING_CHARGE                0x19
#define CMD_DISABLING_CHARGE_TEXT           tr("Выключение режима заряда АКБ")

#define CMD_REQUEST_SETTINGS_CHARGE         0x1A
#define CMD_REQUEST_SETTINGS_CHARGE_TEXT    tr("Запрос параметров заряда АКБ")


#define CMD_WRITE_TO_FLASH                  0x1B
#define CMD_WRITE_TO_FLASH_TEXT             tr("Запись коэффициентов во flash")
//--------------------------------------------------------------------------------
#define ERROR_01 0x01
#define ERROR_01_TEXT   tr("Команда не опознана")

#define ERROR_02 0x02
#define ERROR_02_TEXT   tr("Ошибка CRC")

#define ERROR_03 0x03
#define ERROR_03_TEXT   tr("Значение в поле данных не является допустимым для данной команды.")

#define ERROR_04 0x04
#define ERROR_04_TEXT   tr("Выполнение текущей команды прервано.")

#define ERROR_05 0x05
#define ERROR_05_TEXT   tr("Прибор принял команду, но будет выполнять ее длительное время (предотвращает ошибку по таймауту)")

#define ERROR_06 0x06
#define ERROR_06_TEXT   tr("Длина посылки меньше возможной")

#define ERROR_07 0x07
#define ERROR_07_TEXT   tr("Длина посылки больше допустимой")

#define ERROR_08 0x08
#define ERROR_08_TEXT   tr("Длина области данных не совпадает с указанной")

#define ERROR_09 0x09
#define ERROR_09_TEXT   tr("Удаленное управление не включено")

#define ERROR_0A 0x0A
#define ERROR_0A_TEXT   tr("Ошибка записи во flash память прибора")

#define ERROR_0B 0x0B
#define ERROR_0B_TEXT   tr("Прибор занят зарядом АКБ")

#define ERROR_0C 0x0C
#define ERROR_0C_TEXT   tr("Напряжение заряда выше допустимого")

#define ERROR_0D 0x0D
#define ERROR_0D_TEXT   tr("Напряжение заряда ниже допустимого")

#define ERROR_0E 0x0E
#define ERROR_0E_TEXT   tr("Батарея не заряжаемая или неисправна")

#define ERROR_0F 0x0F
#define ERROR_0F_TEXT   tr("Нагрузочная способность источника недостаточна для заряда")

#define ERROR_10 0x10
#define ERROR_10_TEXT   tr("Не проведена калибровка запрашиваемого режима измерения")

#define ERROR_11 0x11
#define ERROR_11_TEXT   tr("Величина, подаваемая на вход при калибровке, больше или меньше допустимой (± 25%)")

#define ERROR_12 0x12
#define ERROR_12_TEXT   tr("Ошибка доступа.")

#define ERROR_13 0x13
#define ERROR_13_TEXT   tr("Перегрузка (в бОльшую сторону)")

#define ERROR_14 0x14
#define ERROR_14_TEXT   tr("Перегрузка (в меньшую сторону)")

#define ERROR_15 0x15
#define ERROR_15_TEXT   tr("Недостаточная частота или постоянное напряжение на входе")

#define ERROR_16 0x16
#define ERROR_16_TEXT   tr("Не выполнена калибровка 0 требуемого режима")

#define ERROR_17 0x17
#define ERROR_17_TEXT   tr("Режим заряда не включен")
//--------------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
//---------------------------------------------------------------
#define MAX_LEN 128
//---------------------------------------------------------------
class Multimeter_v786_2
{
  public:
    Multimeter_v786_2();
  bool send_question_and_get_answer(uint8_t *question_buf,
				    int question_len,
				    uint8_t *answer_buf,
				    int answer_len);
    
  private:
    uint8_t input_buf[MAX_LEN];
    uint8_t input_buf_index;

    uint8_t output_buf[MAX_LEN];
    uint8_t output_buf_index;
    
    uint16_t ModRTU_CRC(unsigned char *buf, int len);
    
    bool check_CMD_GET_STATE(void);
    bool check_CMD_REMOTE_CONTROL_ON(void);
    bool check_CMD_REMOTE_CONTROL_OFF(void);
    bool check_CMD_SERVICE_ON(void);
    bool check_CMD_POWER_OFF(void);
    bool check_CMD_MEASURING_DC_VOLTAGE(void);
    bool check_CMD_MEASURING_AC_VOLTAGE(void);
    bool check_CMD_MEASURING_DC_CURRENT(void);
    bool check_CMD_MEASURING_AC_CURRENT(void);
    bool check_CMD_MEASURING_R(void);
    bool check_CMD_MEASURING_C(void);
    bool check_CMD_MEASURING_L(void);
    bool check_CMD_CONTINUITY(void);
    bool check_CMD_MEASURING_F(void);
    bool check_CMD_MEASURING_ACTIVE_POWER(void);
    bool check_CMD_MEASURING_REACTIVE_POWER(void);
    bool check_CMD_MEASURING_FULL_POWER(void);
    bool check_CMD_MEASURING_POWER_FACTOR(void);
    bool check_CMD_CALIBRATION_DC_VOLTAGE(void);
    bool check_CMD_CALIBRATION_AC_VOLTAGE(void);
    bool check_CMD_CALIBRATION_DC_CURRENT(void);
    bool check_CMD_CALIBRATION_AC_CURRENT(void);
    bool check_CMD_CALIBRATION_R(void);
    bool check_CMD_ENABLING_CHARGE(void);
    bool check_CMD_DISABLING_CHARGE(void);
    bool check_CMD_REQUEST_SETTINGS_CHARGE(void);
    bool check_CMD_WRITE_TO_FLASH(void);

};
//--------------------------------------------------------------------------------
#endif // MULTIMETER_V786_2_HPP
