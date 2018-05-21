#include <Charliplexing.h> //Imports the library, which needs to be Initialized in setup.

void setup()
{
  LedSign::Init();

  while(1)
  {
    for(int n=0; n<DISPLAY_ROWS; n++)
    {
      LedSign::Clear();
      LedSign::Horizontal(n, 1);
      delay(50);
    }
    for(int n=0; n<DISPLAY_COLS; n++)
    {
      LedSign::Clear();
      LedSign::Vertical(n, 1);
      delay(50);
    }
  }
#if 0  
  for(int n=0; n<DISPLAY_ROWS; n++)
  {
    LedSign::Set(n, n, 0);
  }
#endif  
}

void loop()
{

}


