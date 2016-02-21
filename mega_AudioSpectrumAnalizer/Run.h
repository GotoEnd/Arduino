#ifndef CONTROLLER_H
#define CONTROLLER_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include "LEDs.h"
#include "MP3.h"
#include "MSGEQ7.h"
#include "Settings.h"
#include "Storm.h"
#include "Fire.h"
#include "EQ.h"


class Controller {
  public:
    Controller();
    ~Controller();
    void Initialize();

    void Update();
    void Run();
    
  private:  
//    void ModeUpdated();
//    void SettingUpdated();
//    void LevelUpdated();

    void ExecuteRun(bool initial);
    
    void Storm();
    void StormInit();
    void Fire();
    void FireInit();
    void Sound();
    void SoundInit();
    void Demo();
    void DemoInit();
};

#endif
