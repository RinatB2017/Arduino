/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 64

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);

// the previous reading from the analog input
int previous = 0;

void setup()
{
  Serial.begin(9600);
  // set the speed of the motor to 30 RPMs
  //stepper.setSpeed(90);
  stepper.setSpeed(100);
}

void loop()
{
  unsigned long begin_time = 0;
  unsigned long end_time = 0;
  unsigned long time = 0;

  begin_time = millis();
  stepper.step(360 * 2 * 5.625);
  end_time = millis();
  time = (end_time - begin_time) / 1000.0f;
  Serial.print(" Time :");
  Serial.print(time);
  Serial.println(" sec");
  while(1);
}


