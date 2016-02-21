#ifndef FIRE_H
#define FIRE_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include "LEDs.h"

class Fire {
  public:
    Fire();
    ~Fire();
    void Initialize();
    void FireItUp(LEDCurtain &led, byte setting, byte level);
  private:
    void PalateFire(LEDCurtain &led, int strip);
};
 
#endif
