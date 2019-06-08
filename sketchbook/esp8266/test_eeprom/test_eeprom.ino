//---------------------------------------------------------------
//
//---------------------------------------------------------------
#include <EEPROM.h>
//---------------------------------------------------------------
int addr  = 0;
int value = 0;
//---------------------------------------------------------------
#pragma pack (push, 1)

struct {
  char ssid[50];
  char password[50];
  char device_name[50];
} data;

#pragma pack(pop)
//---------------------------------------------------------------
void test_write()
{
  EEPROM.begin(sizeof(value));
  EEPROM.put(addr, 666);
  EEPROM.end();
}
//---------------------------------------------------------------
void test_read()
{
  EEPROM.begin(sizeof(value));
  EEPROM.get(addr, value);
  EEPROM.end();
}
//---------------------------------------------------------------
void test_read_data()
{
  EEPROM.begin(sizeof(data));
  EEPROM.get(addr, data);
  EEPROM.end();
}
//---------------------------------------------------------------
void test_write_data()
{
  strncpy(data.ssid, "Network", sizeof(data.ssid));
  strncpy(data.password, "Password", sizeof(data.password));
  strncpy(data.device_name, "Device name", sizeof(data.device_name));

  EEPROM.begin(sizeof(data));
  EEPROM.put(addr, data);
  EEPROM.end();
}
//---------------------------------------------------------------
void setup()
{
  Serial.begin(9600);

  //test_read();
  test_read_data();

  Serial.println();
  Serial.print("ssid :");
  Serial.println(data.ssid);
  Serial.print("password :");
  Serial.println(data.password);
  Serial.print("device_name :");
  Serial.println(data.device_name);

  //Serial.print("sizeof(data): ");
  //Serial.println(sizeof(data));

  //test_write();
  //test_write_data();
}
//---------------------------------------------------------------
void loop()
{

}
//---------------------------------------------------------------
