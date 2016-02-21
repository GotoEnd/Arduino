#ifndef THUNDERSTORM_H
#define THUNDERSTORM_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include "LEDs.h"

class ThunderStorm {
  public:
    ThunderStorm();
    ~ThunderStorm();
    void Initialize();
    void MakeItRain(LEDCurtain &curtain, byte setting, byte intensity);
    void Munder(LEDCurtain &curtain);
  private:
    void RideTheLightning(LEDCurtain &curtain);
    void CreateRaindrop(uint8_t strip);
    int NextSpotAvailable(uint8_t strip);
};
 
#endif
