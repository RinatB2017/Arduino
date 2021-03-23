//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

//#include <lcd_display.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const char* ble_name = "ESP32test";

void setup() {
  Serial.begin(115200);
  SerialBT.begin(ble_name); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  // экран включить не получится - модуль циклично перезагружается
  //lcd_clear();
  //lcd_print_str(0, "BLE");
  //lcd_print_str(1, ble_name);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  //delay(20);
}
