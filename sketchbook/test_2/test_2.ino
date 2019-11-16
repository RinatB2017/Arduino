
//---------------------------------------------------------------
#define BAUDRATE    115200
#define work_serial Serial
//---------------------------------------------------------------
uint8_t modbus_buf[255] = { 0 };
//---------------------------------------------------------------
#pragma pack (push, 1)

struct HEADER {
  uint8_t address;
  uint8_t command;
  uint8_t cnt_data;
  uint8_t data[];
};

struct CMD_1 {
  uint8_t brightness;
  uint8_t color_R;
  uint8_t color_G;
  uint8_t color_B;
};

union U_UINT32 {
  uint32_t value;
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
};

#pragma pack(pop)
//---------------------------------------------------------------
void debug(String text)
{
  work_serial.println(text);
}
//---------------------------------------------------------------
uint32_t crc32(const char *buf, size_t len)
{
  static uint32_t table[256];
  static int have_table = 0;
  uint32_t rem;
  uint8_t octet;
  int i, j;
  uint32_t crc = 0;
  const char *p, *q;

  /* This check is not thread safe; there is no mutex. */
  if (have_table == 0) {
    /* Calculate CRC table. */
    for (i = 0; i < 256; i++) {
      rem = (uint32_t)i;  /* remainder from polynomial division */
      for (j = 0; j < 8; j++) {
        if (rem & 1) {
          rem >>= 1;
          rem ^= 0xedb88320;
        } else
          rem >>= 1;
      }
      table[i] = rem;
    }
    have_table = 1;
  }

  crc = ~crc;
  q = buf + len;
  for (p = buf; p < q; p++) {
    octet = (uint8_t) * p; /* Cast to unsigned octet. */
    crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
  }
  return ~crc;
}
//---------------------------------------------------------------
void setup()
{
  work_serial.begin(BAUDRATE);

#if 0
  //00 00 04 14FF942E C0F4CF4A
  modbus_buf[0]  = 0x00;
  modbus_buf[1]  = 0x00;
  modbus_buf[2]  = 0x04;

  modbus_buf[3]  = 0x14;
  modbus_buf[4]  = 0xFF;
  modbus_buf[5]  = 0x94;
  modbus_buf[6]  = 0x2E;

  modbus_buf[7]  = 0xC0;
  modbus_buf[8]  = 0xF4;
  modbus_buf[9]  = 0xCF;
  modbus_buf[10] = 0x4A;

  uint32_t calc_crc32 = crc32((char *)&modbus_buf[sizeof(HEADER) + sizeof(CMD_1)], sizeof(uint32_t));
#endif

#if 1
  //000000FF41D912
  modbus_buf[0]  = 0x00;
  modbus_buf[1]  = 0x00;
  modbus_buf[2]  = 0x00;
  modbus_buf[3]  = 0xFF;
  modbus_buf[4]  = 0x41;
  modbus_buf[5]  = 0xD9;
  modbus_buf[6]  = 0x12;
  
  uint32_t calc_crc32 = crc32((char *)&modbus_buf, sizeof(HEADER));
#endif

  work_serial.println(sizeof(HEADER));
  work_serial.println(sizeof(CMD_1));
  work_serial.println(sizeof(uint32_t));
  work_serial.println(calc_crc32,   HEX);
}
//---------------------------------------------------------------
void loop()
{

}
//---------------------------------------------------------------

