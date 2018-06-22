#include    "led-blink.h"

#define LED_STAND_PIN A0

bool on = false;
//------------------------------------------------------------------------------
void setup()
{
    pinMode(LED_STAND_PIN, OUTPUT);
}

//------------------------------------------------------------------------------
void loop()
{
    on = !on;
    uint8_t state = on ? HIGH : LOW;

    digitalWrite(LED_STAND_PIN, state);

    delay(500);
}
//------------------------------------------------------------------------------
