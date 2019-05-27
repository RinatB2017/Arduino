//---------------------------------------------------------------
// тест по-быстрому
//---------------------------------------------------------------
#define CMD_SET_DELAY_MS    1
#define CMD_SET_BRIGHTNESS  2

#define CMD_01 10
#define CMD_02 20
#define CMD_03 30
#define CMD_04 40
#define CMD_05 50

String answer;
//--------------------------------------------------------------------------------
String convert_data_to_ascii(uint8_t data)
{
  uint8_t hi = (data >> 4) & 0x0F;
  uint8_t lo = (data & 0x0F);

  String hi_str;
  String lo_str;
  String temp;

  switch (hi)
  {
    case 0x00: hi_str = "0"; break;
    case 0x01: hi_str = "1"; break;
    case 0x02: hi_str = "2"; break;
    case 0x03: hi_str = "3"; break;
    case 0x04: hi_str = "4"; break;
    case 0x05: hi_str = "5"; break;
    case 0x06: hi_str = "6"; break;
    case 0x07: hi_str = "7"; break;
    case 0x08: hi_str = "8"; break;
    case 0x09: hi_str = "9"; break;
    case 0x0A: hi_str = "A"; break;
    case 0x0B: hi_str = "B"; break;
    case 0x0C: hi_str = "C"; break;
    case 0x0D: hi_str = "D"; break;
    case 0x0E: hi_str = "E"; break;
    case 0x0F: hi_str = "F"; break;
    default:
      break;
  }

  switch (lo)
  {
    case 0x00: lo_str = "0"; break;
    case 0x01: lo_str = "1"; break;
    case 0x02: lo_str = "2"; break;
    case 0x03: lo_str = "3"; break;
    case 0x04: lo_str = "4"; break;
    case 0x05: lo_str = "5"; break;
    case 0x06: lo_str = "6"; break;
    case 0x07: lo_str = "7"; break;
    case 0x08: lo_str = "8"; break;
    case 0x09: lo_str = "9"; break;
    case 0x0A: lo_str = "A"; break;
    case 0x0B: lo_str = "B"; break;
    case 0x0C: lo_str = "C"; break;
    case 0x0D: lo_str = "D"; break;
    case 0x0E: lo_str = "E"; break;
    case 0x0F: lo_str = "F"; break;
    default:
      break;
  }

  temp += hi_str;
  temp += lo_str;

  return temp;
}
//---------------------------------------------------------------
void send_answer(uint8_t cmd)
{
  String x = convert_data_to_ascii(cmd);

  answer = "";
  answer += ":";
  answer += x;
  answer += "FF";
  answer += "FF";
}
//---------------------------------------------------------------
char buf[1597];
void setup()
{
  Serial.begin(57600);

  send_answer(CMD_SET_DELAY_MS);
  Serial.println(answer);

  send_answer(CMD_SET_BRIGHTNESS);
  Serial.println(answer);

  send_answer(CMD_01);
  Serial.println(answer);  
  send_answer(CMD_02);
  Serial.println(answer);
  send_answer(CMD_03);
  Serial.println(answer);
  send_answer(CMD_04);
  Serial.println(answer);
  send_answer(CMD_05);
  Serial.println(answer);

  for(int n=0; n<1500; n++)
  {
    buf[n] = 0;
  }
}
//---------------------------------------------------------------
void loop(void)
{
}
//---------------------------------------------------------------

