#include "Storm.h"

//TODO:  Fix big drop/ lil drop bug  (seed changes with each itteration)
//        so, save in array or have 2 different arrays


//Constants
#define MAX_DROPS 3 //max drops per strip

int _drops[LED_STRIPS][MAX_DROPS];

ThunderStorm::ThunderStorm(){}
ThunderStorm::~ThunderStorm(){}

byte stormIntensity = 500;

void ThunderStorm::Initialize()
{
  Serial.println(F("**ThunderStorm Initializing**"));
  
  randomSeed(42);

  for(uint8_t strip=0; strip<LED_STRIPS; strip++) {
    for(uint8_t i=0;i<MAX_DROPS;i++)
      _drops[strip][i]=-1;
  }
  
  Serial.println(F("**ThunderStorm Initialized**"));
  Serial.println();
}

void ThunderStorm::Munder(LEDCurtain &curtain)
{
  Serial.println(F("MUNDER BOOM"));
  RideTheLightning(curtain);
}

void ThunderStorm::MakeItRain(LEDCurtain &curtain, byte setting, byte level)
{
  //Serial.println(F("RAIN RAIN"));
    
  //byte stormIntensity = map(level,0,7,1,500);
  
  //random number between 1 and 1000
  int seed = random(0,1000);

  //Serial.print(" -si: ");Serial.print(stormIntensity);  Serial.print(" -seed: ");Serial.print(seed); Serial.print(" -level: ");Serial.println(level); 

  //create new raindrop if within threshold
  if(seed < stormIntensity) {
    uint8_t strip = random(0,LED_STRIPS);  //pick a random strip
    Serial.print(" -random strip: ");Serial.println(strip);
    CreateRaindrop(strip);
  }
 
  //step all drops in array
  for(uint8_t strip=0;strip<LED_STRIPS;strip++) {
    for(uint8_t i=0;i<MAX_DROPS;i++) {
      //Serial.print("  -strip:");Serial.print(strip);Serial.print(" -drop:");Serial.print(i);Serial.print(" -array:");Serial.println(_drops[strip][i]);
      if(_drops[strip][i] != -1) {
        curtain.ClearPixel(strip,_drops[strip][i]); //black out last drop
        if(_drops[strip][i]+1<curtain.LEDsPerStrip) {
          //if(i%4!=0) {              
//          if(seed < stormIntensity/5) {
//            if(strip==1 || strip==2)
//            {
//              Serial.println("   -big drop");
//              Serial.print("    -strip:");Serial.print(strip);Serial.print(" -drop:");Serial.print(i);Serial.print(" -array:");Serial.println(_drops[strip][i]);
//            }
            _drops[strip][i]++;
            curtain.DisplayRainDrop(strip, _drops[strip][i], 2);  //intensity: 1->4
//          }
//          else {
//            Serial.println("   -lil drop");
//            _drops[strip][i]=_drops[strip][i]+2;
//            curtain.DisplayRainDrop(strip, _drops[strip][i], 1);
//          }
        }
        else
          _drops[strip][i]=-1;  //mark available
      }
    }
  }  
}

void ThunderStorm::RideTheLightning(LEDCurtain &curtain)
{
  //set-up
  curtain.ClearStrips(20);
  //strike
  curtain.FlashStrips(20,  40,  196);
  curtain.FlashStrips(10,  100, 196);
  curtain.FlashStrips(90,  90,  48 );
  curtain.FlashStrips(50,  150, 48 );  
  curtain.FlashStrips(150, 400, 48 );
  curtain.FlashStrips(400, 30,  196);
  curtain.FlashStrips(20,  60,  196);
  curtain.FlashStrips(70,  10,  196);
}

void ThunderStorm::CreateRaindrop(uint8_t strip)
{
  Serial.print("  -creating raindrop on ");Serial.println(strip);
  //create new raindrop if space available in drop array
  int next = NextSpotAvailable(strip);
  if(next != -1)
    _drops[strip][next]=0;
}

int ThunderStorm::NextSpotAvailable(uint8_t strip)
{
  Serial.print("  -checking for next available raindrop on ");Serial.println(strip);
  for(uint8_t i=0;i<MAX_DROPS;i++) {
    if(_drops[strip][i]==-1)
      return i;
  }
  return -1;
}


