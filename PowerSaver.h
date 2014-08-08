#ifndef PowerSaver_h
#define PowerSaver_h

#include "Arduino.h"

class PowerSaver
{
  public:
    PowerSaver();
    void sleepInterruptSetup();
    void turnOffSPI();
    void turnOnSPI();
    void turnOffADC();
    void turnOffBOD();
    
  private:
  
};

#endif