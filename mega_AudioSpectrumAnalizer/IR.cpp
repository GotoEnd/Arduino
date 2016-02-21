#include "IR.h"
#include <IRremote.h>

#define IR_PIN 3 //interrupt enabled pin

IRrecv _irReceiver(IR_PIN);
decode_results _irResult;

IR::IR(){}
IR::~IR(){}

void IR::Initialize()
{
  Serial.println(F("**IR Initializing**"));
  Serial.print(F(" -IR PIN: "));  Serial.println(IR_PIN);

  _irReceiver.enableIRIn(); // Start the IR receiver
  
  Serial.println(F("**IR Initialized**"));
  Serial.println();
}

IR_Results IR::CheckRemote()
{
  Serial.println("IR::CheckRemote");
  Settings * settings = Settings::GetInstance();
  
  IR_Results results;
  results.ModeUpdated=false;
  results.SettingsUpdated=false;
  results.LevelUpdated=false;

  if (_irReceiver.decode(&_irResult))
  {
    Serial.println(" -new ir command");
    _irReceiver.resume();

    switch(_irResult.value)  //or use bit flags
    {
      case UP:  //cycle up through intensity levels
        settings->Level=onUp(settings->Level);
        results.LevelUpdated=true;
        break;
      case DOWN:  //cycle down through intensity levels
        settings->Level=onDown(settings->Level);
        results.LevelUpdated=true;
        break;        
      case LEFT:  //cycle left through mode settings
        settings->Setting=onLeft(settings->Setting);
        results.SettingsUpdated=true;
        break;
      case RIGHT:  //cycle right through mode settings
        settings->Setting=onRight(settings->Setting);
        results.SettingsUpdated=true;
        break;
      case ONE:
        results.ModeUpdated = onMode(settings, 1);
        break;      
      case TWO:
        results.ModeUpdated = onMode(settings, 2);
        break;
      case THREE:
        results.ModeUpdated = onMode(settings, 3);
        break;
      case FOUR:
        results.ModeUpdated = onMode(settings, 4);
        break;
                
      default:
        onUnknown();
        break;
    }
  }
  return results;
}

bool IR::onMode(Settings *settings, int mode)
{
  Serial.print(F(" IR MODE: "));Serial.println(mode);
  bool updated = settings->Mode == mode;
  settings->Mode=mode;
  return updated;
}

byte IR::onUp(byte currentLevel)
{
  Serial.println(F(" IR UP"));
  if(currentLevel == INTENSITY_LEVELS)
    return 1;
  else
    return currentLevel++;
}

byte IR::onDown(byte currentLevel)
{
  Serial.println(F(" IR DOWN"));
  if(currentLevel == 0)
    return INTENSITY_LEVELS;
  else
    return currentLevel--;  
}

byte IR::onRight(byte currentSetting)
{
  Serial.println(F(" IR RIGHT"));
  if(currentSetting == SETTINGS)
    return 1;
  else
    return currentSetting++;
}

byte IR::onLeft(byte currentSetting)
{
  Serial.println(F(" IR LEFT"));
  if(currentSetting == 1)
    return SETTINGS;
  else
    return currentSetting--;     
}

void IR::onUnknown()
{
  if(_irResult.value!=4294967295){
    Serial.print(F(" *IR UNKNOWN: ")); Serial.print(_irResult.value, HEX); Serial.print("  "); Serial.println(_irResult.value, DEC);
  }
}

