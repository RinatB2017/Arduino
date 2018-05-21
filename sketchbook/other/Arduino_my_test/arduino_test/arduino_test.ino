//---------------------------------------------------------------
#define USE_LCD
//---------------------------------------------------------------
#ifdef USE_LCD
  #include <LiquidCrystal.h>
#endif
#include <EEPROM.h>
//---------------------------------------------------------------
#define MAX_X_LCD  16
#define MAX_Y_LCD  2

#define MAX_LEN  1024

char temp_buf[MAX_LEN];
char buf[MAX_LEN];
uint16_t  buf_index = 0;
//---------------------------------------------------------------
#define MAX_EEPROM_BYTES    512
#define BEGIN_BYTE          0x55
#define END_BYTE            0xAA

enum {
  COMMAND_CMD_1           = 1,
  COMMAND_CMD_2           = 2,
  COMMAND_CMD_3           = 3,
  COMMAND_READ_ONE_BYTE   = 4,
  COMMAND_WRITE_ONE_BYTE  = 5,
  COMMAND_READ_ALL_BYTES  = 6,
  COMMAND_WRITE_ALL_BYTES = 7,
  COMMAND_RGB             = 8,
  COMMAND_MOTOR           = 9
};
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
//---------------------------------------------------------------
struct RGB {
  uint8_t  color_R;
  uint8_t  color_G;
  uint8_t  color_B;
};

struct PROTOCOL_HEADER {
  uint8_t  begin_byte;
  uint8_t  command;
  uint16_t len_data;
};

struct PROTOCOL_RGB {
  struct PROTOCOL_HEADER;
  struct RGB;
  uint8_t  end_byte;
};

struct PROTOCOL_MOTOR {
  struct PROTOCOL_HEADER;
  uint8_t  motor_angle_1;
  uint8_t  motor_angle_2;
  uint8_t  end_byte;
};
//---------------------------------------------------------------
#ifdef USE_LCD
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#endif  
//---------------------------------------------------------------
void serial_setup(long value)
{
  Serial.begin(value);    
#ifdef USE_LCD
  lcd.print("baudrate ");
  lcd.print(value);
#endif  
}
//---------------------------------------------------------------
void setup(void)
{
#ifdef USE_LCD
  lcd.begin(MAX_X_LCD, MAX_Y_LCD);
#endif  
  serial_setup(SPEED_9600);
}
//---------------------------------------------------------------
void read_all(void)
{
  byte value = 0;
  int address = 0;
  
  for(address=0; address<MAX_EEPROM_BYTES; address++)
  {
    value = EEPROM.read(address);
    Serial.write((byte)value);
  }
}
//---------------------------------------------------------------
void clear_all(void)
{
  int address = 0;
  
#ifdef USE_LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("clear");
#endif  
  
  for(address=0; address<MAX_EEPROM_BYTES; address++)
  {
    EEPROM.write(address, 0);
  }
}
//---------------------------------------------------------------
void print_error(char *error)
{
#ifdef USE_LCD
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(error);
#endif  
}
//---------------------------------------------------------------
bool check(void)
{
  PROTOCOL_HEADER *header;
  header = (PROTOCOL_HEADER *)buf;
  
  if(header->begin_byte != BEGIN_BYTE) 
  {
    print_error("Error begin byte");
    return false;
  }
  switch(header->command)
  {
    case COMMAND_CMD_1:
    case COMMAND_CMD_2:
    case COMMAND_CMD_3:
    case COMMAND_READ_ONE_BYTE:
    case COMMAND_WRITE_ONE_BYTE:
    case COMMAND_READ_ALL_BYTES:
    case COMMAND_WRITE_ALL_BYTES:
      break;
      
    default:
      print_error("Error command");
      return false;
  }
  if((byte)buf[buf_index-1] != END_BYTE) 
  {
    print_error("Error end byte");
#ifdef USE_LCD
    lcd.setCursor(0, 1);
    lcd.print(buf_index);
#endif    
    return false;
  }
  
  return true;
}
//---------------------------------------------------------------
void cmd_1(void)
{
  
}
//---------------------------------------------------------------
void cmd_2(void)
{
  
}
//---------------------------------------------------------------
void cmd_3(void)
{
  
}
//---------------------------------------------------------------
void cmd_read_one_byte(void)
{
  
}
//---------------------------------------------------------------
void cmd_write_one_byte(void)
{
  
}
//---------------------------------------------------------------
void cmd_read_all_bytes(void)
{
   read_all(); 
}
//---------------------------------------------------------------
void cmd_write_all_bytes(void)
{
  for(int addr=0; addr<MAX_EEPROM_BYTES; addr++)
  {
    EEPROM.write(addr, (byte)buf[sizeof(PROTOCOL_HEADER)+addr]);
  }
}
//---------------------------------------------------------------
void run_command(void)
{
  PROTOCOL_HEADER *header;
  header = (PROTOCOL_HEADER *)buf;
  switch(header->command)
  {
    case COMMAND_CMD_1: 
#ifdef USE_LCD
      lcd.print("CMD_1"); 
#endif      
      cmd_1();
      break;
    case COMMAND_CMD_2: 
#ifdef USE_LCD
      lcd.print("CMD_2"); 
#endif      
      cmd_2();
      break;
    case COMMAND_CMD_3: 
#ifdef USE_LCD
      lcd.print("CMD_3"); 
#endif      
      cmd_3();
      break;
    case COMMAND_READ_ONE_BYTE: 
#ifdef USE_LCD
      lcd.print("READ_ONE_BYTE"); 
#endif      
      cmd_read_one_byte();
      break;
    case COMMAND_WRITE_ONE_BYTE: 
#ifdef USE_LCD
      lcd.print("WRITE_ONE_BYTE"); 
#endif      
      cmd_write_one_byte();
      break;
    case COMMAND_READ_ALL_BYTES: 
#ifdef USE_LCD
      lcd.print("READ_ALL_BYTES"); 
#endif      
      cmd_read_all_bytes();
      break;
    case COMMAND_WRITE_ALL_BYTES: 
#ifdef USE_LCD
      lcd.print("WRITE_ALL_BYTES"); 
#endif      
      cmd_write_all_bytes();
      break;
      
    default:
#ifdef USE_LCD
      lcd.print("Error command");
#endif      
      break;
  }
}
//---------------------------------------------------------------
void append_data(char data)
{
  if(buf_index<MAX_LEN) 
  {
    buf[buf_index] = data;
    buf_index++;
  }
  else
  {
#ifdef USE_LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error !!!");
#endif    
  }
}
//---------------------------------------------------------------
void read_all_data(int interval)
{
  int old_time = millis();
  int current_time = millis();

  while(1)
  {  
    if(Serial.available())
    {
      append_data(Serial.read());
    }
    current_time = millis();
    if((current_time - old_time) > interval)
      break;
  }
}
//---------------------------------------------------------------
void loop(void)
{
  if(Serial.available())
  {
    read_all_data(1000);
    if(check())
    {
#ifdef USE_LCD
      lcd.clear();
      lcd.setCursor(0, 0);
#endif      
      run_command();
      //lcd.setCursor(0, 1);
      //lcd.print("Yes!");
    }
    buf_index = 0;
  }
}
//---------------------------------------------------------------

