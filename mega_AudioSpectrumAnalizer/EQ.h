#ifndef EQVISUALIZER_H
#define EQVISUALIZER_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include "LEDs.h"
#include "MSGEQ7.h"

class SpectrumVisualizer {
  public:
    SpectrumVisualizer();
    ~SpectrumVisualizer();
    void Initialize();    
    void Visualize(LEDCurtain &led, Spectrum spectrum, byte setting, byte level);
  private:
    void DisplaySpectrumTest(LEDCurtain &led, Spectrum spectrum, int band);
};
 
#endif
