#ifndef SETTINGS_H
#define SETTINGS_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

//Configuration
#define MODES             4
#define SETTINGS          3
#define INTENSITY_LEVELS  7

//Modes
#define MODE_ASA  1
#define MODE_FIRE 2
#define MODE_RAIN 3
#define MODE_DEMO 4

class Settings
{
  public:
    static Settings * GetInstance();
    static void DestroyInstance();
    ~Settings();

    const int NumberModes = MODES;
    const int NumberSettings = SETTINGS;
  
    byte Mode;
    byte Setting;
    byte Level;
    
    void Initialize(byte mode, byte setting, byte level);
    void PrintSettings();
    
  private:
    static Settings * instance;
    Settings(){};
    Settings(const Settings& orig);
    Settings& operator=(const Settings& orig);
};

#endif
