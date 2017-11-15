//---------------------------------------------------------------
#ifndef robocraft_h
#define robocraft_h
//---------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
//---------------------------------------------------------------
class RoboCraft
{
  public:
    RoboCraft();
    void hello();
};
//---------------------------------------------------------------
#endif
