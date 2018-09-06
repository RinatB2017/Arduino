#include "esp32-hal-ledc.h"

int pwm_channel = 0;
int pwm_freq = 50;
int pwm_resolution = 8; // 0 - 0xFF
int pwm_pin = 16;

int pwm_value = 0;

void setup() {
  ledcSetup(pwm_channel, pwm_freq, pwm_resolution);
  ledcAttachPin(pwm_pin, pwm_channel);
  pinMode(pwm_pin, OUTPUT);
}

void loop() {
  if(pwm_value > 255) {
    pwm_value = 0;
  }
  ledcWrite(pwm_channel, pwm_value);
  pwm_value++;
  delay(50);
}
