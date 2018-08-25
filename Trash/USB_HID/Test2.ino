
#include "TrinketHidCombo.h"

void setup()
{
    //pinMode(13,OUTPUT);

    pinMode(4,INPUT);
    pinMode(2,INPUT);
    pinMode(5,OUTPUT);

    digitalWrite(4, HIGH);
    TrinketHidCombo.begin();
}

void loop()
{
    TrinketHidCombo.poll();
    TrinketHidCombo.mouseMove(200,0,0);
    //delay(500);
    //digitalWrite(13, HIGH);
    TrinketHidCombo.mouseMove(0,200,0);
    //delay(500);
    //digitalWrite(13, LOW);
    TrinketHidCombo.mouseMove(-200,0,0);
    //delay(500);
    //digitalWrite(13, HIGH);
    TrinketHidCombo.mouseMove(0,-200,0);
    //delay(500);
    //digitalWrite(13, LOW);
}
