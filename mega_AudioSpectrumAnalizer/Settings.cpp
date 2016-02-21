#include "Settings.h"

Settings * Settings::instance = 0;
Settings * Settings::GetInstance()
{
  if (instance == 0)
    instance = new Settings();

  return instance;
}

void Settings::DestroyInstance()
{
  delete instance;
  instance = 0;
}

void Settings::Initialize(byte mode, byte setting, byte level)
{
  Serial.println(F("**Settings Initializing**"));
  
  Mode = mode;
  Setting = setting;
  Level = level;
  PrintSettings();
  
  Serial.println(F("**Settings Initialized**"));
  Serial.println();  
}

void Settings::PrintSettings()
{
  Serial.print(F("SETTINGS: "));
  Serial.print(F(" mode: "));Serial.print(Mode);Serial.print(F(" - setting: "));Serial.print(Setting);Serial.print(F(" - level"));Serial.println(Level);
}
