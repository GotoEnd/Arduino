//#include "Demo.h"
//
//Demo::Demo(){}
//Demo::~Demo(){}
//
//void Demo::Initialize()
//{
//}
//
//void Demo::Visualize(LEDCurtain &led, byte setting, byte level)
//{
//  switch(_currentPatternNumber)
//  {
//    case 0:
//      Rainbow();
//      break;
//    case 1:
//      RainbowWithGlitter();
//      break;
//    case 3:
//      Confetti();
//      break;
//    case 4:
//      Sinelon();
//      break;
//    case 5:
//      Juggle();
//      break;
//    case 6:
//      BPM();
//      break;
//    case default:
//      Rainbow();
//      break;
//  }
//
//  EVERY_N_MILLISECONDS( 20 ) { _hue++; } // slowly cycle the "base color" through the rainbow
//  EVERY_N_SECONDS( 10 ) { NextPattern(); } // change patterns periodically
//}
//
//void Demo::NextPattern()
//{
//  // add one to the current pattern number, and wrap around at the end
//  _currentPatternNumber = (_currentPatternNumber + 1) % 7;
//}
//
//void Demo::Rainbow(LEDCurtain &led) 
//{
//  for( int i=0; i<LED_STRIPS; i++) {
//    //fill_rainbow( _strips[i], LEDS_PER_STRIP, _hue, 7);
//  }
//}
//
//void Demo::RainbowWithGlitter(LEDCurtain &led) 
//{
//  Rainbow();
//  for( int i=0; i<LED_STRIPS; i++) {
//    AddGlitter(i,80);
//  }
//}
//
//void Demo::AddGlitter(LEDCurtain &led, uint8_t strip, fract8 chanceOfGlitter) 
//{
//  if( random8() < chanceOfGlitter) {
//    //_strips[strip][ random16(LEDS_PER_STRIP) ] += CRGB::White;
//  }
//}
//
//void Demo::Confetti(LEDCurtain &led) 
//{
//  for( int i=0; i<LED_STRIPS; i++) {
//    // random colored speckles that blink in and fade smoothly
//    //fadeToBlackBy( _strips[i], LEDS_PER_STRIP, 10);
//    int pos = random16(LEDS_PER_STRIP);
//    //_strips[i][pos] += CHSV( _hue + random8(64), 200, 255);
//  }
//}
//
//void Demo::Sinelon(LEDCurtain &led)
//{
//  for( int i=0; i<LED_STRIPS; i++)
//  {
//    // a colored dot sweeping back and forth, with fading trails
//    //fadeToBlackBy( _strips[i]+i*2, LEDS_PER_STRIP, 20);
//    int pos = beatsin16(13,0,LEDS_PER_STRIP);
//    //_strips[i][pos+i*2] += CHSV( _hue, 255, 192);
//  }
//}
//
//void Demo::BPM(LEDCurtain &led)
//{
//  for( int i=0; i<LED_STRIPS; i++)
//  {
//    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
//    uint8_t BeatsPerMinute = 62;
//    CRGBPalette16 palette = PartyColors_p;
//    
//    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
//    for( int j = 0; j < LEDS_PER_STRIP; j++) {
//      //_strips[i][j] = ColorFromPalette(palette, _hue+(j*2), beat-_hue+(j*10));
//    }
//  }
//}
//
//void Demo::Juggle(LEDCurtain &led) 
//{
//  // eight colored dots, weaving in and out of sync with each other
//  for(uint8_t strip=0; strip<LED_STRIPS; strip++)
//    led.FadeBy(strip,10);  //fadeToBlackBy( _strips[strip], LEDS_PER_STRIP, 20);
//    
//  for(strip=0; strip<LED_STRIPS; strip++)
//  {  
//    byte dothue = 0;
//    for( int j = 0; j < 8; j++) {
//      _led.SetPixel(strip, [beatsin16(j+7,0,LEDS_PER_STRIP)], CHSV(dothue, 200, 255));
//      //_strips[strip][beatsin16(j+7,0,LEDS_PER_STRIP)] |= CHSV(dothue, 200, 255);
//      dothue += 32;
//    }
//  }
//}

