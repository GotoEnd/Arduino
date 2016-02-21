#include "IR.h"
#include "Settings.h"
#include "Pub.h"
#include "Run.h"

//Settings
#define SLAVE_PORT        8
#define FRAMES_PER_SECOND 60

IR _ir;
Publisher _pub;
Controller _controller;

//TODO:
//  fire, demo
//  finish spectrumVisualizer
//  info and error messages to LCD

void setup()
{
  Serial.begin(9600);
  while (!Serial1);
  delay(3000); // sanity delay

  Serial.println(F("***INITIALIZING***"));Serial.println();
  
  Settings * settings = Settings::GetInstance(); settings->Initialize(MODE_FIRE,1,5);
  _ir.Initialize();
  _pub.Initialize(SLAVE_PORT);
  _controller.Initialize();
  delay(100);
  _controller.Update();
  delay(100);
  
  Serial.println(F("***INITIALIZED***"));Serial.println();
}

void loop()
{
  IsModeUpdated() ? _controller.Update() : _controller.Run();
  
  //FastLED.delay(1000 / FRAMES_PER_SECOND);
}

bool IsModeUpdated()
{
  IR_Results ir = _ir.CheckRemote();
  Settings * _settings = Settings::GetInstance();

  if(ir.SettingsUpdated)
  {
    Serial.println("Setting updated: "); _settings->PrintSettings();
    _pub.SendSetting(_settings->Setting);
  }
  
  if(ir.LevelUpdated)
  {
    Serial.println("Level updated: "); _settings->PrintSettings();
    _pub.SendLevel(_settings->Level);
  }
  
  if(ir.ModeUpdated)
  {
    Serial.println("Mode updated: "); _settings->PrintSettings();
    _pub.SendMode(_settings->Mode);
    return true;
  }
  return false;
}
