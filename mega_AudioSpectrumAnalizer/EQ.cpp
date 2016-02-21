#include "EQ.h"

//TODO:  make it play nicer with various number of led strips

SpectrumVisualizer::SpectrumVisualizer(){}
SpectrumVisualizer::~SpectrumVisualizer(){}

void SpectrumVisualizer::Initialize()
{
  Serial.println(F("**SpectrumVisualizer Initializing**"));
  Serial.println(F("**SpectrumVisualizer Initialized**"));
  Serial.println();
}

//void SpectrumVisualizer::RenderSpectrum(byte setting, byte intensity)
//{
//  //TODO: map intensity to sensitivity threshold, and pass that to ReadSpectrum()
//  Spectrum spectrum = _eq.ReadSpectrum();
//  DisplaySpectrum(spectrum, setting);
//}


void SpectrumVisualizer::Visualize(LEDCurtain &led, Spectrum spectrum, byte setting, byte level)
{
  Serial.println(F("SpectrumVisualizer::DisplaySpectrum"));
  switch(setting)
  {
    case 1:
      DisplaySpectrumTest(led, spectrum, 0);
      break;
    case 2:
      //DisplaySpectrum(spectrum, true);  //Simple
      break;
    case 3:
      //DisplaySpectrum(spectrum, false);   //Color shift
      break;
    case 4:
      //DisplaySpectrumWithPeakBars(spectrum);
      break;      
    default:
      break;
  }
}

void SpectrumVisualizer::DisplaySpectrumTest(LEDCurtain &leds, Spectrum spectrum, int band) //single strip, single band, single color
{
  Serial.println(F("SpectrumVisualizer::DisplaySpectrumTest"));
  for(uint8_t led=0;led<leds.LEDsPerStrip;led++)
  {
    if(spectrum.LeftChannel[band]>=led)
      leds.ClearPixel(band, led);
    else
      leds.SetPixel(band, led, CRGB::Red);
  }
}

//void LEDCurtain::DisplaySpectrum(Spectrum spectrum, bool simple)
//{
//  Serial.println(F("LEDCurtain::DisplaySpectrum internal"));
//  uint8_t bands = (sizeof(spectrum.LeftChannel)/sizeof(*spectrum.LeftChannel));
//  for(uint8_t band=0;band<bands;band++){
//    RenderSpectrumBand(band, spectrum.LeftChannel[band],spectrum.RightChannel[band], simple);
//  }
//}
//
//void LEDCurtain::RenderSpectrumBand(uint8_t band, uint8_t leftValue, uint8_t rightValue, bool simple)
//{
//  Serial.println(F("LEDCurtain::RenderSpectrumBand"));
//  for(uint8_t led=0;led<LEDS_PER_STRIP;led++)
//  {
//    //left
//    if(leftValue>=led){
//      SetPixel(band, led, CRGB::Black);
//    }
//    else {
//      if(simple)
//        SetPixel(band, led, CRGB::Red);
//      else
//        SetPixel(band, led, GetColor(leftValue,led));
//    }
//    //right
//    if(rightValue>=led){
//      SetPixel(band+LED_STRIPS/2, led, CRGB::Black);
//    }
//    else {
//      if(simple)
//        SetPixel(band+LED_STRIPS/2, led, CRGB::Red);
//      else
//        SetPixel(band+LED_STRIPS/2, led, GetColor(rightValue,led));
//    }
//  }
//}
