//---------------------------------------------------------------
#include <AccelStepper.h>
//---------------------------------------------------------------
AccelStepper stepper;
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);

  stepper.setSpeed(90);	
  //stepper.setMaxSpeed(200.0);
  //stepper.setAcceleration(100.0);
}
//---------------------------------------------------------------
void loop(void)
{
  stepper.runSpeed();

  //Serial.println("test");
  //stepper.runToNewPosition(0);
  //stepper.runToNewPosition(500);
  //stepper.runToNewPosition(100);
  //stepper.runToNewPosition(180);
  //delay(1000);
}
//---------------------------------------------------------------



