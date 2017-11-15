
#include "TrinketHidCombo.h"

void test()
{
    digitalWrite(4, HIGH);
    delay(500);
    digitalWrite(4, LOW);
    delay(500);

    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5, LOW);
    delay(500);
}

void test2()
{
    pinMode(13,OUTPUT);
    pinMode(4,OUTPUT);
}

void setup()
{
    pinMode(4,INPUT);
    pinMode(2,INPUT);
    pinMode(5,OUTPUT);

    TrinketHidCombo.begin();
}

void loop()
{
    TrinketHidCombo.poll();
    TrinketHidCombo.mouseMove(200,0,0);
    delay(500);
    TrinketHidCombo.mouseMove(0,200,0);
    delay(500);
    TrinketHidCombo.mouseMove(-200,0,0);
    delay(500);
    TrinketHidCombo.mouseMove(0,-200,0);
    delay(500);
}
