/*****************************************************
  ESP32 Servo Control
  PWM SERVO pin   ==> GPIO 05

  MJRoBot.org 6Sept17
*****************************************************/
// PMW SERVO
#define SERVO_PIN 5
int freq = 50;
int channel = 0;
int resolution = 8;
int dutyCycle = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Servo Control");

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(SERVO_PIN, channel);
  ledcWrite(channel, dutyCycle);
}

void loop()
{
  ledcWrite(channel, 0);
  delay(500);
  ledcWrite(channel, 180);
  delay(500);
}

