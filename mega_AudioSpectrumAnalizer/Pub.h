#ifndef PUB_H
#define PUB_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif


#define M_ALL_SETTINGS  1
#define M_MODE          2
#define M_SETTING       3
#define M_LEVEL         4
#define M_INIT_START    5
#define M_INIT_END      6 //not sure if needed...
#define M_INFO          8
#define M_ERROR         9

#include <Wire.h>
#include "Settings.h"

class Publisher
{
  public:
    Publisher();
    ~Publisher();
    void Initialize(int port);
    void SendInitializingStart();
    void SentInitializingEnd(){};
    void SendAllSettings(byte mode, byte setting, byte level);
    void SendMode(byte mode);
    void SendSetting(byte setting);
    void SendLevel(byte level);
    void SendInfo(String message);

  private:
    void Begin();
    void End();
};

#endif
