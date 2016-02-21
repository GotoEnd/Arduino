#ifndef MSGEQ7_H
#define MSGEQ7_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif


#define RMSGEQ7 1 //A2
#define RSTROBE 9
#define RRESET  8

#define LMSGEQ7 0 //A1
#define LSTROBE 7
#define LRESET  6

#define SPECTRUM 7
#define NOISEFILTER 80

struct Spectrum {
  uint8_t RightChannel[SPECTRUM];
  uint8_t LeftChannel[SPECTRUM];
};

class MSGEQ7 {
  public:
    MSGEQ7();
    ~MSGEQ7();
    void Initialize(byte constaint);
    Spectrum ReadSpectrum(byte level);
};
 
#endif
