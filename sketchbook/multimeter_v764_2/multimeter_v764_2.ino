//--------------------------------------------------------------------------------
#include <LiquidCrystal.h>
//--------------------------------------------------------------------------------
#define MAX_X_LCD  16
#define MAX_Y_LCD  2
//--------------------------------------------------------------------------------
enum {
  SPEED_300     = 300,
  SPEED_1200    = 1200,
  SPEED_2400    = 2400,
  SPEED_4800    = 4800,
  SPEED_9600    = 9600,
  SPEED_14400   = 14400,
  SPEED_19200   = 19200,
  SPEED_28800   = 28800,
  SPEED_38400   = 38400,
  SPEED_57600   = 57600,
  SPEED_115200  = 115200
};
#define BUTTON_NUMBER_UDC  5
#define BUTTON_NUMBER_IDC  6
#define BUTTON_NUMBER_R    7
#define BUTTON_NUMBER_UAC  8
#define BUTTON_NUMBER_IAC  9
#define BUTTON_NUMBER_HZ   10
#define BUTTON_NUMBER_MHZ  11
#define BUTTON_NUMBER_AVR  12

#define BUTTON_CODE_UDC  0x35
#define BUTTON_CODE_IDC  0x36
#define BUTTON_CODE_R    0x37
#define BUTTON_CODE_UAC  0x38
#define BUTTON_CODE_IAC  0x39
#define BUTTON_CODE_HZ   0x41
#define BUTTON_CODE_MHZ  0x42
#define BUTTON_CODE_AVR  0x43

#define MODE_UDC  0
#define MODE_IDC  1
#define MODE_R    2
#define MODE_UAC  3
#define MODE_IAC  4
#define MODE_HZ   5
#define MODE_MHZ  6
//--------------------------------------------------------------------------------
#define pin_rs 8
#define pin_en 9
#define pin_d4 4
#define pin_d5 5
#define pin_d6 6
#define pin_d7 7
LiquidCrystal lcd(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7); 
//--------------------------------------------------------------------------------
#define MAX_LEN 128

uint8_t input_buf[MAX_LEN];
uint8_t output_buf[MAX_LEN];
int input_buf_index;

int measuring_value;
unsigned char code_button;
unsigned char mode_measuring;

int value_U = 0;
int value_I = 0;
int old_value_U = 0;
int old_value_I = 0;
//--------------------------------------------------------------------------------
int pin_U = A1;
int pin_I = A2;
//--------------------------------------------------------------------------------
#define V764_2_CMD_0x41     0x41
#define V764_2_CMD_0x41_TEXT   tr("В7-64/2 функция 0x41: Сброс в исходное состояние.")

#define V764_2_CMD_0x42     0x42
#define V764_2_CMD_0x42_TEXT   tr("В7-64/2 функция 0x42: Установка скорости обмена.")

#define V764_2_CMD_0x45     0x45
#define V764_2_CMD_0x45_TEXT   tr("В7-64/2 функция 0x45: Инициализация вторичной станции.")

#define V764_2_CMD_0x46     0x46
#define V764_2_CMD_0x46_TEXT   tr("В7-64/2 функция 0x46: Запрос идентификатора.")

#define V764_2_CMD_0x47     0x47
#define V764_2_CMD_0x47_TEXT   tr("В7-64/2 функция 0x47: Запрос состояния.")

#define V764_2_CMD_0x48     0x48
#define V764_2_CMD_0x48_TEXT   tr("В7-64/2 функция 0x48: Переадресация.")

#define V764_2_CMD_0x53     0x53
#define V764_2_CMD_0x53_TEXT   tr("В7-64/2 функция 0x53: Управление прибором.")
//--------------------------------------------------------------------------------
//#pragma pack (1)
//--------------------------------------------------------------------------------
typedef struct
{
  unsigned char  address;
  unsigned char  cmd;
  unsigned char  count_data;
} 
V7642_HEADER;
//--------------------------------------------------------------------------------
union CMD_V7642_ERROR_ANSWER
{
  struct {
    V7642_HEADER header;
    unsigned char error;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x41_QUESTION
{
  struct {
    V7642_HEADER header;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x42_QUESTION
{
  struct {
    V7642_HEADER header;
    struct {
      unsigned char  baud;
      unsigned char  time;
    } 
    data;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x45_QUESTION
{
  struct {
    V7642_HEADER header;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};

union CMD_V7642_0x45_ANSWER
{
  struct {
    V7642_HEADER header;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x46_QUESTION
{
  struct {
    V7642_HEADER header;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};

union CMD_V7642_0x46_ANSWER
{
  struct {
    V7642_HEADER header;
    struct {
      unsigned char  type;
      unsigned char  year;
      unsigned char  month;
      unsigned char  serno_lo;
      unsigned char  serno_hi;
      unsigned char  baud;
      unsigned char  time_waiting;
      unsigned char  address_station;
      unsigned char  byte_test;
    } 
    data;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x47_QUESTION
{
  struct {
    V7642_HEADER header;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};

union CMD_V7642_0x47_ANSWER
{
  struct {
    V7642_HEADER header;
    struct {
      uint8_t  state;
      uint8_t  error;
      int32_t     value;
    } 
    data;
    uint16_t crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x48_QUESTION
{
  struct {
    V7642_HEADER header;
    struct {
      unsigned char  data_0;
    } 
    data;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};

union CMD_V7642_0x48_ANSWER
{
  struct {
    V7642_HEADER header;
    struct {
      unsigned char  address_station;
    } 
    data;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
union CMD_V7642_0x53_QUESTION
{
  struct {
    V7642_HEADER header;
    struct {
      unsigned char  data_0;
    } 
    data;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};

union CMD_V7642_0x53_ANSWER
{
  struct {
    V7642_HEADER header;
    struct {
      unsigned char  data_0;
    } 
    data;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};

union CMD_V7642_0x53_ANSWER_ERROR
{
  struct {
    V7642_HEADER header;
    unsigned char error;
    unsigned short crc16;
  } 
  body;
  unsigned char buf[sizeof(body)];
};
//--------------------------------------------------------------------------------
uint16_t powersupply_crc16(uint8_t *pcBlock, uint16_t len)
{
  uint16_t crc = 0xFFFF;

  for (int pos=0; pos<len; pos++)
  {
    crc ^= (uint16_t)pcBlock[pos];

    for (int i=8; i!=0; i--)
    {
      if ((crc & 0x0001) != 0)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
    }
  }
#ifdef USE_HTONS
  return htons(crc);
#else
  return crc;
#endif
}
//--------------------------------------------------------------------------------
int modbus_receive(void)
{
  uint8_t i;
  uint8_t s;

  input_buf_index = 0;
  while(true) 
  {
    if(!Serial.available()) 
    {
      i = 0;
      while (!Serial.available()) 
      {
        delay(1);
        if (++i == 10) 
        {
          /* Too late, bye */
          return -1;
        }
      }
    }
    s = Serial.read();
    if(s >= 0)
    {
      if(input_buf_index < MAX_LEN)
      {
        input_buf[input_buf_index] = s;
        input_buf_index++;
      }
    }
  }
  return input_buf_index;
}
//--------------------------------------------------------------------------------
void clear_input_buf(void)
{
  for(int n=0; n<MAX_LEN; n++)
  {
    input_buf[n] = 0;
  }
  input_buf_index = 0;
}
//--------------------------------------------------------------------------------
bool cmd_0x41(void)
{
  return true;
}
//--------------------------------------------------------------------------------
bool cmd_0x42(void)
{
  return true;
}
//--------------------------------------------------------------------------------
bool cmd_0x45(void)
{
  CMD_V7642_0x45_ANSWER answer;

  answer.body.header.address = 0;
  answer.body.header.cmd = V764_2_CMD_0x45;
  answer.body.header.count_data = 0;
  answer.body.crc16 = powersupply_crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x45_ANSWER) - 2);

  for(int n=0; n<sizeof(CMD_V7642_0x45_ANSWER); n++)
  {
    Serial.write(answer.buf[n]);
  }
  return true;
}
//--------------------------------------------------------------------------------
bool cmd_0x46(void)
{
  CMD_V7642_0x46_ANSWER answer;

  answer.body.header.address = 0;
  answer.body.header.cmd = V764_2_CMD_0x46;
  answer.body.header.count_data = sizeof(answer.body.data);
  answer.body.data.type = 0;
  answer.body.data.year = 0;
  answer.body.data.month = 1;
  answer.body.data.serno_lo = 0x12;
  answer.body.data.serno_hi = 0x34;
  answer.body.data.baud = 1;
  answer.body.data.time_waiting = 1;
  answer.body.data.address_station = 1;
  answer.body.data.byte_test = 0;
  answer.body.crc16 = powersupply_crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x46_ANSWER) - 2);

  for(int n=0; n<sizeof(CMD_V7642_0x46_ANSWER); n++)
  {
    Serial.write(answer.buf[n]);
  }
  return true;
}
//--------------------------------------------------------------------------------
bool cmd_0x47(void)
{
  CMD_V7642_0x47_ANSWER answer;

  answer.body.header.address = 0;
  answer.body.header.cmd = V764_2_CMD_0x47;
  answer.body.header.count_data = sizeof(answer.body.data);
  answer.body.data.state = mode_measuring;
  answer.body.data.error = 0;
  answer.body.data.value = measuring_value;
  answer.body.crc16 = powersupply_crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x47_ANSWER) - 2);

  for(int n=0; n<sizeof(CMD_V7642_0x47_ANSWER); n++)
  {
    Serial.write(answer.buf[n]);
  }
  return true;
}
//--------------------------------------------------------------------------------
bool cmd_0x48(void)
{
  CMD_V7642_0x48_ANSWER answer;

  answer.body.header.address = 0;
  answer.body.header.cmd = V764_2_CMD_0x48;
  answer.body.header.count_data = sizeof(answer.body.data);
  answer.body.data.address_station = 0;
  answer.body.crc16 = powersupply_crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x48_ANSWER) - 2);

  for(int n=0; n<sizeof(CMD_V7642_0x48_ANSWER); n++)
  {
    Serial.write(answer.buf[n]);
  }
  return true;
}
//--------------------------------------------------------------------------------
bool cmd_0x53(void)
{
  CMD_V7642_0x53_QUESTION *question = (CMD_V7642_0x53_QUESTION *)input_buf;
  code_button = question->body.data.data_0;

  switch (code_button)
  {
  case BUTTON_CODE_UDC: 
    mode_measuring = MODE_UDC;  
    break;
  case BUTTON_CODE_IDC: 
    mode_measuring = MODE_IDC;  
    break;
  case BUTTON_CODE_R:   
    mode_measuring = MODE_R;    
    break;
  case BUTTON_CODE_UAC: 
    mode_measuring = MODE_UAC;  
    break;
  case BUTTON_CODE_IAC: 
    mode_measuring = MODE_IAC;  
    break;
  case BUTTON_CODE_HZ:  
    mode_measuring = MODE_HZ;   
    break;
  case BUTTON_CODE_MHZ: 
    mode_measuring = MODE_MHZ;  
    break;

  default:
    mode_measuring = MODE_UDC;
    break;
  }

  CMD_V7642_0x53_ANSWER answer;

  answer.body.header.address = 0;
  answer.body.header.cmd = V764_2_CMD_0x53;
  answer.body.header.count_data = sizeof(answer.body.data);
  answer.body.data.data_0 = code_button;
  answer.body.crc16 = powersupply_crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x53_ANSWER) - 2);

  for(int n=0; n<sizeof(CMD_V7642_0x53_ANSWER); n++)
  {
    Serial.write(answer.buf[n]);
  }
  return true;
}
//--------------------------------------------------------------------------------
void check_packet(void)
{
  if(input_buf_index < sizeof(V7642_HEADER)) 
  {
    return;
  }

  V7642_HEADER *header = (V7642_HEADER *)input_buf;
  unsigned char cmd = header->cmd;

  switch(cmd)
  {
  case V764_2_CMD_0x41:  
    cmd_0x41();  
    break;    
  case V764_2_CMD_0x42:  
    cmd_0x42();  
    break;    
  case V764_2_CMD_0x45:  
    cmd_0x45();  
    break;    
  case V764_2_CMD_0x46:  
    cmd_0x46();  
    break;    
  case V764_2_CMD_0x47:  
    cmd_0x47();  
    break;
  case V764_2_CMD_0x48:  
    cmd_0x48();  
    break;
  case V764_2_CMD_0x53:  
    cmd_0x53();  
    break;

  default:
    break;
  }
}
//--------------------------------------------------------------------------------
void draw_data(void)
{
  lcd.clear();

  if(input_buf_index == 0)
  {
    lcd.print("no data");
    return;
  }

  for(int n=0; n<input_buf_index; n++)
  {
    lcd.print(input_buf[n], HEX);
  }
  delay(1000);
}
//--------------------------------------------------------------------------------
void measuring(void)
{
  value_U = analogRead(pin_U);
  value_I = analogRead(pin_I);
}
//--------------------------------------------------------------------------------
void draw(void)
{
  if((old_value_U != value_U) || (old_value_I != value_I))
  {
    old_value_U = value_U;
    old_value_I = value_I;
    
    lcd.clear();

    unsigned int U = map(value_U, 0, 0x3FF, 0, 0xFFFF) * 2;
    unsigned int I = map(value_I, 0, 0x3FF, 0, 0xFFFF) * 2;

    lcd.setCursor(0, 0);
    lcd.print("U ");
    lcd.print(U);

    lcd.setCursor(0, 1);
    lcd.print("I ");
    lcd.print(I);
    delay(500);
  }
}
//--------------------------------------------------------------------------------
void modbus(void)
{
  if(Serial.available()) 
  {
    clear_input_buf();
    modbus_receive();
    check_packet();
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup(void)
{
  unsigned int speed = SPEED_57600;

  measuring_value = 666;
  code_button = BUTTON_NUMBER_UDC;
  mode_measuring = MODE_UDC;

  lcd.begin(MAX_X_LCD, MAX_Y_LCD);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("B7-64/2");

  lcd.setCursor(0, 1);
  lcd.print("baudrate ");
  lcd.print(speed);

  Serial.begin(speed);
  
  //pinMode(pin_U, INPUT);
  //pinMode(pin_I, INPUT);
  
  //digitalWrite(pin_U, HIGH);
  //digitalWrite(pin_I, HIGH);

  delay(1000);
}
//--------------------------------------------------------------------------------
void loop(void)
{
  measuring();
  modbus();
  draw();
}
//--------------------------------------------------------------------------------









