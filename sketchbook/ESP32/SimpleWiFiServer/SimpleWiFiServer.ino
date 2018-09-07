/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will print the IP address of your WiFi Shield (once connected)
  to the Serial monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 5.

  If the IP address of your shield is yourAddress:
  http://yourAddress/H turns the LED on
  http://yourAddress/L turns it off

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the Wifi.begin() call accordingly.

  Circuit:
   WiFi shield attached
   LED attached to pin 5

  created for arduino 25 Nov 2012
  by Tom Igoe

  ported for sparkfun esp32
  31.01.2017 by Jan Hendrik Berlin

*/

#include <WiFi.h>
#include "lcd.h"
#include "esp32-hal-ledc.h"

int pwm_channel = 0;
int pwm_freq = 50;
int pwm_resolution = 8; // 0 - 0xFF
int pwm_pin = 16;

int pwm_value = 0;

#if 1
const char* ssid     = "RT-WiFi_DBA0";
const char* password = "CUDRM67c";
#endif

#if 0
const char* ssid = "Wifi";
const char* password = "88888888";
#endif

int port = 15000;

WiFiServer server(port);
WiFiClient client;

void draw_progress_bar(int value) {
  int x = 0;
  int y = 45;
  int w = 127;
  int h = 15;

  display.setColor(WHITE);
  
  display.drawLine(x, y, x+w, y);
  display.drawLine(x, y+h, x+w, y+h);
  display.drawLine(x, y, x, y+h);
  display.drawLine(x+w, y, x+w, y+h);

  display.setColor(BLACK);
  display.fillRect(x+1, y+1, w-1, h-1);

  display.setColor(WHITE);
  display.fillRect(x+1, y+1, value / 8 - 1, h-1);
  
  display.display();
}

void clear_pwm_text(int x, int y, int w, int h) {
  display.setColor(BLACK);
  for (int pos_y = y; pos_y < (y + h); pos_y++) {
    display.drawLine(x, pos_y, x + w, pos_y);
  }
  display.display();
  display.setColor(WHITE);
}

void Question(String text)
{
  String temp = text;
  Serial.println("Question: " + temp);
  //char *str0 = strtok(temp, " ");
  int pos_0 = temp.indexOf(" ");
  if (pos_0 < 0)
  {
    return;
  }

  String temp2 = temp.substring(pos_0 + 1);
  Serial.println("pos_0: " + String(pos_0));
  Serial.println("temp2: " + temp2);

  int pos_1 = temp2.indexOf(" ");
  if (pos_0 < 0)
  {
    return;
  }

  Serial.println("pos_1: " + String(pos_1));
  String temp3 = temp2.substring(0, pos_1);
  Serial.println("temp3: " + temp3);

  String temp4 = temp3.substring(5);
  Serial.println("temp4: " + temp4);

  int value_pwm = temp4.toInt();
  Serial.println("value_pwm = " + String(value_pwm));
}

int get_pwm_value(String text)
{
  String temp = text;
  int pos_0 = temp.indexOf(" ");
  if (pos_0 < 0)
  {
    return -1;
  }

  String temp2 = temp.substring(pos_0 + 1);
  int pos_1 = temp2.indexOf(" ");
  if (pos_0 < 0)
  {
    return -1;
  }

  String temp3 = temp2.substring(0, pos_1);
  String temp4 = temp3.substring(5);

  int value_pwm = temp4.toInt();
  return value_pwm;
}

void setup()
{
  ledcSetup(pwm_channel, pwm_freq, pwm_resolution);
  ledcAttachPin(pwm_pin, pwm_channel);
  pinMode(pwm_pin, OUTPUT);

  Serial.begin(115200);

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  lcd_init();
  lcd_clear();
  lcd_print_str(0, "Init");

  WiFi.begin(ssid, password);

  lcd_print_str(1, "Wait...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  lcd_clear();
  lcd_print_str(0, ssid);
  lcd_print_str(1, WiFi.localIP().toString() + ":" + port);

  draw_progress_bar(0);

  server.begin();
}

void loop()
{
  // Check if a client has connected
  client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  int err_cnt = 0;
  while (!client.available())
  {
    err_cnt++;
    if (err_cnt > 1000)
    {
      Serial.println("... failed");
      return;
    }
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Question(req);

  Serial.println(req);
  client.flush();

  // GET /gpio/0 HTTP/1.1

  // Match the request
  int val = 0;
  if (req.indexOf("/gpio/0") != -1)
  {
    val = 0;
    ledcWrite(pwm_channel, 0);

    draw_progress_bar(0);
  }
  else if (req.indexOf("/gpio/1") != -1)
  {
    val = 1;
    ledcWrite(pwm_channel, 0xFF);

    draw_progress_bar(1023);
  }
  else if (req.indexOf("/pwm/") != -1)
  {
    pwm_value = get_pwm_value(req);
    ledcWrite(pwm_channel, pwm_value);

    clear_pwm_text(0, 45, 64, 15);
    draw_progress_bar(pwm_value);
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val) ? "high" : "low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

