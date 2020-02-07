/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "ESP8266WiFi.h"

int index_array_ssid = 0;
String array_ssid[100];

void setup()
{
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");

  scan();
}

bool connect(char *ssid, char *password)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    return false;
  }
  return true;
}

void scan()
{
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      array_ssid[index_array_ssid] = WiFi.SSID(i);
      index_array_ssid++;
      delay(10);
    }
  }
}

void loop()
{
  Serial.println("scan start");

  for (int n = 0; n < index_array_ssid; n++)
  {
    Serial.println(array_ssid[index_array_ssid]);
  }

  // Wait a bit before scanning again
  delay(5000);
}

