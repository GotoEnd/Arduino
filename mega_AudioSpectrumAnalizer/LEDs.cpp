#include "LEDs.h"

CRGB _strips[LED_STRIPS][LEDS_PER_STRIP];

//Color palettes
CRGBPalette16 _currentPalette;
TBlendType    _currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;



  //Make these functions of LEDCurtain...
  //ChangePalettePeriodically();
  //EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { ChangePalettePeriodically(); } // change palette periodically

LEDCurtain * LEDCurtain::instance = 0;
LEDCurtain * LEDCurtain::GetInstance()
{
  if (instance == 0)
    instance = new LEDCurtain();
  return instance;
}

void LEDCurtain::DestroyInstance()
{
  delete instance;
  instance = 0;
}

void LEDCurtain::Initialize()
{
  Serial.println(F("**LED Cutain Initializing**"));

  _currentPalette = RainbowColors_p;
  _currentBlending = LINEARBLEND;
  
  FastLED.addLeds<NEOPIXEL,LLED1>(_strips[0], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 1 initialized on pin: "));Serial.println(LLED1);
  FastLED.addLeds<NEOPIXEL,LLED2>(_strips[1], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 2 initialized on pin: "));Serial.println(LLED2);
  FastLED.addLeds<NEOPIXEL,LLED3>(_strips[2], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 3 initialized on pin: "));Serial.println(LLED3);
  FastLED.addLeds<NEOPIXEL,LLED4>(_strips[3], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 4 initialized on pin: "));Serial.println(LLED4);
  FastLED.addLeds<NEOPIXEL,LLED5>(_strips[4], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 5 initialized on pin: "));Serial.println(LLED5);
  FastLED.addLeds<NEOPIXEL,LLED6>(_strips[5], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 6 initialized on pin: "));Serial.println(LLED6);
  FastLED.addLeds<NEOPIXEL,LLED7>(_strips[6], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  left strip 7 initialized on pin: "));Serial.println(LLED7);

  FastLED.addLeds<NEOPIXEL,RLED1>(_strips[7], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 1 initialized on pin: "));Serial.println(RLED1);
  FastLED.addLeds<NEOPIXEL,RLED2>(_strips[8], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 2 initialized on pin: "));Serial.println(RLED2);
  FastLED.addLeds<NEOPIXEL,RLED3>(_strips[9], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 3 initialized on pin: "));Serial.println(RLED3);
  FastLED.addLeds<NEOPIXEL,RLED4>(_strips[10], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 4 initialized on pin: "));Serial.println(RLED4);
  FastLED.addLeds<NEOPIXEL,RLED5>(_strips[11], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 5 initialized on pin: "));Serial.println(RLED5);
  FastLED.addLeds<NEOPIXEL,RLED6>(_strips[12], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 6 initialized on pin: "));Serial.println(RLED6);
  FastLED.addLeds<NEOPIXEL,RLED7>(_strips[13], LEDS_PER_STRIP).setCorrection( TypicalLEDStrip ); Serial.print(F("  right strip 7 initialized on pin: "));Serial.println(RLED7);

  FastLED.setBrightness(64);
  delay(10);  
  ClearStrips(10);
  
  Serial.println(F("**LED Cutain Initialized**"));Serial.println();
}

void LEDCurtain::SetPixel(uint8_t strip, uint8_t pixel, CRGB color)
{
  //Serial.print("LEDCurtain::SetPixel strip: ");Serial.print(strip);Serial.print(", pixel: ");Serial.println(pixel);
  _strips[strip][pixel]=color;
}

void LEDCurtain::ClearPixel(uint8_t strip, uint8_t pixel)
{
  //Serial.println("LEDCurtain::ClearPixel");
  SetPixel(strip, pixel, CRGB::Black);
}

void LEDCurtain::ClearStrips(int hold)
{
  Serial.println("LEDCurtain::ClearStrips");
  for(uint8_t strip=0;strip<LED_STRIPS;strip++){
    for(uint8_t i=1;i<LEDS_PER_STRIP;i++)
      ClearPixel(strip, i);
  }
  if(hold>0)
    delay(hold);
}

void LEDCurtain::FlashStrips(int hold, int del, uint8_t brightness)
{
  Serial.println("LEDCurtain::FlashStrips");
  for(uint8_t strip=0;strip<LED_STRIPS;strip++){
    for(uint8_t i=1;i<LEDS_PER_STRIP;i++)
      _strips[strip][i]=CHSV( HUE_PURPLE, 64, brightness);
  }
  delay(hold);
  ClearStrips(del);
}

void LEDCurtain::FadeBy(uint8_t strip, uint8_t by)
{
  fadeToBlackBy(_strips[strip], LEDS_PER_STRIP, by);
}

void LEDCurtain::DisplayRainDrop(uint8_t strip, uint8_t pixel, byte intensity)
{
  //Serial.print("LEDCurtain::DisplayRainDrop strip: ");Serial.print(strip);Serial.print(", pixel: ");Serial.println(pixel);
  int brightness=64*intensity;
  _strips[strip][pixel]=CHSV( HUE_BLUE, 128, brightness);
}

void LEDCurtain::Demo(byte setting, byte level)
{
  RenderDemoFrame(setting, level);
}

void LEDCurtain::RenderDemoFrame(byte setting, byte level)
{
  Serial.print("LEDCurtain::RenderDemoFrame: ");Serial.println(_currentPatternNumber);
  switch(_currentPatternNumber)
  {
    case 0:
      Rainbow();
      break;
    case 1:
      RainbowWithGlitter();
      break;
    case 3:
      Confetti();
      break;
    case 4:
      Sinelon();
      break;
    case 5:
      Juggle();
      break;
    case 6:
      BPM();
      break;
    default:
      Rainbow();
      break;
  }
  FastLED.show();
  
  EVERY_N_MILLISECONDS( 20 ) { _hue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 5 ) { NextPattern(); } // change patterns periodically
}

void LEDCurtain::NextPattern()
{
  Serial.print("LEDCurtain::NextPattern : ");Serial.println(_currentPatternNumber);
  // add one to the current pattern number, and wrap around at the end
  _currentPatternNumber = (_currentPatternNumber + 1) % 7;
  Serial.print("                  after : ");Serial.println(_currentPatternNumber);  
}

void LEDCurtain::Rainbow() 
{
  Serial.println("LEDCurtain::Rainbow");
  for( int i=0; i<LED_STRIPS; i++) {
    fill_rainbow( _strips[i], LEDS_PER_STRIP, _hue, 7);
  }
}

void LEDCurtain::RainbowWithGlitter() 
{
  Rainbow();
  for( int i=0; i<LED_STRIPS; i++) {
    AddGlitter(i,80);
  }
}

void LEDCurtain::AddGlitter(uint8_t strip, fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    _strips[strip][ random16(LEDS_PER_STRIP) ] += CRGB::White;
  }
}

void LEDCurtain::Confetti() 
{
  Serial.println("LEDCurtain::Confetti");
  for( int i=0; i<LED_STRIPS; i++) {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy( _strips[i], LEDS_PER_STRIP, 10);
    int pos = random16(LEDS_PER_STRIP);
    _strips[i][pos] += CHSV( _hue + random8(64), 200, 255);
  }
}

void LEDCurtain::Sinelon()
{
  Serial.println("LEDCurtain::Sinelon");  
  for( int i=0; i<LED_STRIPS; i++)
  {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( _strips[i], LEDS_PER_STRIP, 20);
    int pos = beatsin16(13,0,LEDS_PER_STRIP);
    _strips[i][pos] += CHSV( _hue, 255, 192);
  }
}

void LEDCurtain::BPM()
{
  Serial.println("LEDCurtain::BMP");
  for( int i=0; i<LED_STRIPS; i++)
  {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
    for( int j = 0; j < LEDS_PER_STRIP; j++) {
      _strips[i][j] = ColorFromPalette(palette, _hue+(j*2), beat-_hue+(j*10));
    }
  }
}

void LEDCurtain::Juggle() 
{
  Serial.println("LEDCurtain::Juggle");
  // eight colored dots, weaving in and out of sync with each other
  for(uint8_t strip=0; strip<LED_STRIPS; strip++)
    fadeToBlackBy( _strips[strip], LEDS_PER_STRIP, 20);
    
  for(uint8_t strip=0; strip<LED_STRIPS; strip++)
  {  
    byte dothue = 0;
    for( int j = 0; j < 8; j++) {
      _strips[strip][beatsin16(j+7,0,LEDS_PER_STRIP)] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }
}



//void LEDCurtain::DisplaySpectrum(Spectrum spectrum, byte setting)
//{
//  Serial.println(F("LEDCurtain::DisplaySpectrum"));
//  switch(setting)
//  {
//    case 1:
//      DisplaySpectrumTest(0,spectrum);
//      break;
//    case 2:
//      //DisplaySpectrum(spectrum, true);  //Simple
//      break;
//    case 3:
//      DisplaySpectrum(spectrum, false);   //Color shift
//      break;
//    case 4:
//      //DisplaySpectrumWithPeakBars(spectrum);
//      break;      
//    default:
//      break;
//  }
//}

//void LEDCurtain::DisplaySpectrumTest(int stripIndex, Spectrum spectrum) //single strip, single band, single color
//{
//  Serial.println(F("LEDCurtain::DisplaySpectrumTest"));
//  for(uint8_t led=0;led<LEDS_PER_STRIP;led++)
//  {
//    if(spectrum.LeftChannel[stripIndex]>=led){
//      SetPixel(stripIndex, led, CRGB::Black);
//    }
//    else {
//      SetPixel(stripIndex, led, CRGB::Red);
//    }
//  }
//}

//void LEDCurtain::DisplaySpectrumWithPeakBars(CRGB barColor)  //with peak value bar dropping slowly
//{
//  static uint8_t lpeaks[SPECTRUM]; static uint8_t rpeaks[SPECTRUM];
//  
//  for(uint8_t band=0;band<SPECTRUM;band++)
//  {
//    //left peak detection
//    if(_lspectrumValues[band]>=lpeaks[band]){
//      lpeaks[band]=_lspectrumValues[band];  //new high
//    }
//    //right peak detection
//    if(_rspectrumValues[band]>=rpeaks[band]){
//      rpeaks[band]=_rspectrumValues[band];  //new high
//    }
//
//    //render spectrum band current values
//    RenderSpectrumBand(band);
//
//    //render spectrum band peaks
//    _lstrips[band][lpeaks[band]]=barColor; _rstrips[band][rpeaks[band]]=barColor;
//
//    //lower peaks for next pass
//    lpeaks[band]--; rpeaks[band]--;
//  }  
//}

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

CRGB LEDCurtain::GetColor(uint8_t totalValue, uint8_t currentPixel)
{
  return GetColorPalette(currentPixel,totalValue,0,false);
//  return GetColor(currentPixel,totalValue,0,false);
}

CRGB LEDCurtain::GetColorPalette(uint8_t currentPixel, uint8_t total, uint8_t intensity, bool fixedColor)
{
  uint8_t brightness;
  if(intensity>0)
    brightness=intensity;  //map intensity to brightness
  else
    brightness = map(total,0,LEDS_PER_STRIP,0,255);

  uint8_t colorIndex;
  if(fixedColor)
    colorIndex = map(total,0,LEDS_PER_STRIP,0,240);
  else
    colorIndex = map(currentPixel,0,LEDS_PER_STRIP,0,240);
  return ColorFromPalette( _currentPalette, colorIndex, brightness, _currentBlending);
}

void LEDCurtain::ChangePalettePeriodically()
{
  EVERY_N_MILLISECONDS( 5000 ) 
  { 
    SwitchPallette(random(0,10)); 
  }
//    uint8_t secondHand = (millis() / 1000) % 60;
//    static uint8_t lastSecond = 99;
//    
//    if( lastSecond != secondHand) {
//        lastSecond = secondHand;
//        if( secondHand ==  0)  { _currentPalette = RainbowColors_p;         _currentBlending = LINEARBLEND; }
//        if( secondHand == 10)  { _currentPalette = RainbowStripeColors_p;   _currentBlending = NOBLEND;  }
//        if( secondHand == 15)  { _currentPalette = RainbowStripeColors_p;   _currentBlending = LINEARBLEND; }
//        if( secondHand == 20)  { SetupPurpleAndGreenPalette();              _currentBlending = LINEARBLEND; }
//        if( secondHand == 25)  { SetupTotallyRandomPalette();               _currentBlending = LINEARBLEND; }
//        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();        _currentBlending = NOBLEND; }
//        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();        _currentBlending = LINEARBLEND; }
//        if( secondHand == 40)  { _currentPalette = CloudColors_p;           _currentBlending = LINEARBLEND; }
//        if( secondHand == 45)  { _currentPalette = PartyColors_p;           _currentBlending = LINEARBLEND; }
//        if( secondHand == 50)  { _currentPalette = myRedWhiteBluePalette_p; _currentBlending = NOBLEND;  }
//        if( secondHand == 55)  { _currentPalette = myRedWhiteBluePalette_p; _currentBlending = LINEARBLEND; }
//    }
}

void LEDCurtain::SwitchPallette(uint8_t seed)
{
  switch(seed)
  {
    case 0:  _currentPalette = RainbowColors_p;         _currentBlending = LINEARBLEND; break;
    case 1:  _currentPalette = RainbowStripeColors_p;   _currentBlending = NOBLEND; break;    
    case 2:  _currentPalette = RainbowStripeColors_p;   _currentBlending = LINEARBLEND; break;
    case 3:  SetupPurpleAndGreenPalette();              _currentBlending = LINEARBLEND; break;
    case 4:  SetupTotallyRandomPalette();               _currentBlending = LINEARBLEND; break;
    case 5:  SetupBlackAndWhiteStripedPalette();        _currentBlending = NOBLEND; break;
    case 6:  SetupBlackAndWhiteStripedPalette();        _currentBlending = LINEARBLEND; break;
    case 7:  _currentPalette = CloudColors_p;           _currentBlending = LINEARBLEND; break;
    case 8:  _currentPalette = PartyColors_p;           _currentBlending = LINEARBLEND; break;
    case 9:  _currentPalette = myRedWhiteBluePalette_p; _currentBlending = NOBLEND; break;
    case 10: _currentPalette = myRedWhiteBluePalette_p; _currentBlending = LINEARBLEND; break;
    default: _currentPalette = RainbowColors_p;         _currentBlending = LINEARBLEND;
  }
}

// This function fills the palette with totally random colors.
void LEDCurtain::SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        _currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes, using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used to set them up.
void LEDCurtain::SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( _currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    _currentPalette[0] = CRGB::White;
    _currentPalette[4] = CRGB::White;
    _currentPalette[8] = CRGB::White;
    _currentPalette[12] = CRGB::White;
}

// This function sets up a palette of purple and green stripes.
void LEDCurtain::SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    _currentPalette = CRGBPalette16(green,  green,  black,  black, purple, purple, black,  black,
                                    green,  green,  black,  black, purple, purple, black,  black );
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black,
    CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black,    
    CRGB::Red, CRGB::Red, 
    CRGB::Gray, CRGB::Gray, 
    CRGB::Blue, CRGB::Blue,
    CRGB::Black, CRGB::Black
};
