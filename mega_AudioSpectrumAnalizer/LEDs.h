#ifndef LEDCURTAIN_H
#define LEDCURTAIN_H

#define LED_STRIPS          14
#define LEDS_PER_STRIP      60

#define LLED1 40
#define LLED2 42
#define LLED3 44
#define LLED4 46
#define LLED5 48
#define LLED6 50
#define LLED7 52

#define RLED1 22
#define RLED2 24
#define RLED3 26
#define RLED4 28
#define RLED5 30
#define RLED6 32
#define RLED7 34

#include <FastLED.h>
#include "MSGEQ7.h"

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

class LEDCurtain {
  public:
    const uint8_t Strips = LED_STRIPS;
    const uint8_t LEDsPerStrip = LEDS_PER_STRIP;
  
    static LEDCurtain * GetInstance();
    static void DestroyInstance();
    ~LEDCurtain();

    void Initialize();
    void Demo(byte setting, byte level);
    void DisplaySpectrum(Spectrum spectrum, byte setting);
    void ClearStrips(int hold);
    void FlashStrips(int hold, int del, uint8_t brightness);
    void ClearPixel(uint8_t strip, uint8_t pixel);
    void SetPixel(uint8_t strip, uint8_t pixel, CRGB color);
    void FadeBy(uint8_t strip, uint8_t by);
    void DisplayRainDrop(uint8_t strip, uint8_t pixel, byte intensity);
    
  private:
    uint8_t _currentPatternNumber = 0;
    uint8_t _hue = 0;
    
    //void DisplaySpectrum(Spectrum spectrum, bool simple);
    //void DisplaySpectrumTest(int stripIndex, Spectrum spectrum);    
    //void RenderSpectrumBand(uint8_t band, uint8_t leftValue, uint8_t rightValue, bool simple);
    
    CRGB GetColor(uint8_t totalValue, uint8_t currentPixel);
    CRGB GetColorPalette(uint8_t currentPixel, uint8_t total, uint8_t intensity, bool fixedColor);
    void SetupPurpleAndGreenPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupTotallyRandomPalette();
    void SwitchPallette(uint8_t seed);
    void ChangePalettePeriodically();
    
    void RenderDemoFrame(byte setting, byte level);
    void NextPattern();
    void Rainbow();
    void RainbowWithGlitter();
    void AddGlitter(uint8_t strip, fract8 chanceOfGlitter);
    void Confetti();
    void Sinelon();
    void Juggle();
    void BPM();
    
    
    static LEDCurtain * instance;
    LEDCurtain(){};
    LEDCurtain(const LEDCurtain& orig);
    LEDCurtain& operator=(const LEDCurtain& orig);       
};

#endif
