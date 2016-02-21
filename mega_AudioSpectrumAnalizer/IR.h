#ifndef IR_H
#define IR_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#define UP    16736925
#define DOWN  16754775
#define LEFT  16720605
#define RIGHT 16761405
#define OK    16712445
#define ZERO  16730805
#define ONE   16738455
#define TWO   16750695
#define THREE 16756815
#define FOUR  16724175
#define FIVE  16718055
#define SIX   16743045
#define SEVEN 16716015
#define EIGHT 16726215
#define NINE  16734885
#define STAR  16728765
#define HASH  16732845

#include "Settings.h"

struct IR_Results {
  public:
    bool ModeUpdated;
    bool SettingsUpdated;
    bool LevelUpdated;
};

class IR {
  public:
    IR();
    ~IR();
    void Initialize();
    IR_Results CheckRemote();
    
  private:
    bool onMode(Settings *settings, int mode);
    byte onUp(byte level);
    byte onDown(byte level);
    byte onRight(byte setting);
    byte onLeft(byte setting);
    void onUnknown();
};
 
#endif
