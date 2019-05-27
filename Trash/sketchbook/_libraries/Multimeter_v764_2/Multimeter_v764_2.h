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
#ifndef MULTIMETER_V764_2_HPP
#define MULTIMETER_V764_2_HPP
//--------------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
//--------------------------------------------------------------------------------
#define V764_2_CMD_0x41     0x41
#define V764_2_CMD_0x41_TEXT   tr("Сброс в исходное состояние.")

#define V764_2_CMD_0x42     0x42
#define V764_2_CMD_0x42_TEXT   tr("Установка скорости обмена.")

#define V764_2_CMD_0x45     0x45
#define V764_2_CMD_0x45_TEXT   tr("Инициализация вторичной станции.")

#define V764_2_CMD_0x46     0x46
#define V764_2_CMD_0x46_TEXT   tr("Запрос идентификатора.")

#define V764_2_CMD_0x47     0x47
#define V764_2_CMD_0x47_TEXT   tr("Запрос состояния.")

#define V764_2_CMD_0x48     0x48
#define V764_2_CMD_0x48_TEXT   tr("Переадресация.")

#define V764_2_CMD_0x53     0x53
#define V764_2_CMD_0x53_TEXT   tr("Управление прибором.")
//--------------------------------------------------------------------------------
union CMD_V7642_0x41_QUESTION
{
    struct {
        unsigned char address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x42_QUESTION
{
    struct {
        unsigned char address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned char  baud;
        unsigned char  time;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x45_QUESTION
{
    struct {
        unsigned char address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union CMD_V7642_0x45_ANSWER
{
    struct {
	unsigned char address;
	unsigned char  cmd;
	unsigned char  count_data;
	unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x46_QUESTION
{
    struct {
        unsigned char address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union CMD_V7642_0x46_ANSWER
{
    struct {
	unsigned char address;
	unsigned char  cmd;
	unsigned char  count_data;
	unsigned char  type;
	unsigned char  year;
	unsigned char  month;
	unsigned char  serno_lo;
	unsigned char  serno_hi;
	unsigned char  baud;
	unsigned char  time_waiting;
	unsigned char  address_station;
	unsigned char  byte_test;
	unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x47_QUESTION
{
    struct {
        unsigned char  address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union CMD_V7642_0x47_ANSWER
{
    struct {
	unsigned char  address;
	unsigned char  cmd;
	unsigned char  count_data;
	unsigned char  state;
	unsigned char  error;
	uint32_t       value;
	unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
} ;
//--------------------------------------------------------------------------------
union CMD_V7642_0x48_QUESTION
{
    struct {
        unsigned char  address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned char  data;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union CMD_V7642_0x48_ANSWER
{
    struct {
	unsigned char  address;
	unsigned char  cmd;
	unsigned char  count_data;
	unsigned char  address_station;
	unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//---------------------------------------------------------------
union CMD_V7642_0x53_QUESTION
{
    struct {
        unsigned char  address;
        unsigned char  cmd;
        unsigned char  count_data;
        unsigned char  data;
        unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};

union CMD_V7642_0x53_ANSWER
{
    struct {
	unsigned char  address;
	unsigned char  cmd;
	unsigned char  count_data;
	unsigned char  data;
	unsigned short crc16;
    } data;
    unsigned char buf[sizeof(data)];
};
//---------------------------------------------------------------
#define MAX_LEN 128
//---------------------------------------------------------------
class Multimeter_v764_2
{
  public:
    Multimeter_v764_2();
  bool send_question_and_get_answer(uint8_t *question_buf,
				    int question_len,
				    uint8_t *answer_buf,
				    int *answer_len);
    
  private:
    uint8_t input_buf[MAX_LEN];
    uint8_t input_buf_index;

    uint8_t output_buf[MAX_LEN];
    uint8_t output_buf_index;
    
    uint16_t crc16(unsigned char *buf, int len);
    
    bool check_V764_2_CMD_0x41(void);
    bool check_V764_2_CMD_0x42(void);
    bool check_V764_2_CMD_0x45(void);
    bool check_V764_2_CMD_0x46(void);
    bool check_V764_2_CMD_0x47(void);
    bool check_V764_2_CMD_0x48(void);
    bool check_V764_2_CMD_0x53(void);
};
//--------------------------------------------------------------------------------
#endif // MULTIMETER_V786_2_HPP
