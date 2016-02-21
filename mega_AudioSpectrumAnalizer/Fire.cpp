#include "Fire.h"

Fire::Fire(){}
Fire::~Fire(){}

void Fire::Initialize()
{  
}

void Fire::FireItUp(LEDCurtain &led, byte setting, byte level)
{
  for(int i=0;i<led.Strips;i++)
    PalateFire(led, i); // run simulation frame, using palette colors
}

void Fire::PalateFire(LEDCurtain &led, int strip)
{
//  // Array of temperature readings at each simulation cell
//  static byte heat[NUM_LEDS];
//  
//    // Step 1.  Cool down every cell a little
//    for( int i = 0; i < NUM_LEDS; i++) 
//    {
//      //uint8_t temp = tempFromColor(_strips[index][i]);      
//      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
//    }
//  
//    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
//    for( int k= NUM_LEDS - 1; k >= 2; k--) {
//      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
//    }
//    
//    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
//    if( random8() < SPARKING ) {
//      int y = random8(7);
//      heat[y] = qadd8( heat[y], random8(160,255) );
//    }
//
//    // Step 4.  Map from heat cells to LED colors
//    for( int j = 0; j < NUM_LEDS; j++) {
//      // Scale the heat value from 0-255 down to 0-240
//      // for best results with color palettes.
//      byte colorindex = scale8( heat[j], 240);
//      CRGB color = ColorFromPalette( gPal, colorindex);
//      _strips[index][j] = color;
//      //_strips[index].setPixelColor(j,color.r,color.g,color.b);
//    }
//    //_strips[index].show();
}

//uint8_t tempFromColor(CRGB color)
//{
//  return 10;
//}
