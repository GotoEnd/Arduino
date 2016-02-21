#include "Run.h"

MSGEQ7 _eq;
LEDCurtain * _led = LEDCurtain::GetInstance();
SpectrumVisualizer _spec;
ThunderStorm _storm;
Fire _fire;
MP3 _mp3;

Settings * _settings = Settings::GetInstance();

Controller::Controller() {}
Controller::~Controller(){}

void Controller::Initialize()
{
  Serial.println(F("**CONTROLLER Initializing**"));
  
  _led->Initialize();
  _mp3.Initialize();
  _eq.Initialize(_led->LEDsPerStrip);
  _storm.Initialize();
  _fire.Initialize();
  _spec.Initialize();  
  
  Serial.println(F("**CONTROLLER Initialized**"));
  Serial.println();  
}

//void Controller::ModeUpdated()
//{
//}
//
//void Controller::SettingUpdated()
//{
//}
//
//void Controller::LevelUpdated()
//{
//}

void Controller::Update()
{
  ExecuteRun(true);
}

void Controller::Run()
{
  ExecuteRun(false);
}

void Controller::ExecuteRun(bool initial)
{
  Serial.print("Controller::ExecuteRun: ");Serial.println(initial);
  switch(_settings->Mode)
  {
    case MODE_ASA:
      initial ? SoundInit() : Sound();
      break;
    case MODE_FIRE:
      initial ? FireInit() : Fire();
      break;
    case MODE_RAIN:
      initial ? StormInit() : Storm();
      break;
    case MODE_DEMO:
      initial ? DemoInit() : Demo();
      break;    
    default:
      break;
  }    
}

void Controller::StormInit()
{
  _mp3.Play(MP3_storm);
}

void Controller::Storm()
{
  //Serial.println("Controller::Storm()");
  //TODO: use msgeq7 to control intensity and munder (if able to switch sound sources)
  //    : munder  
  _storm.MakeItRain(*_led,_settings->Setting,_settings->Level);
}

void Controller::FireInit()
{
  //Serial.println("Controller::FireInit()");
  _mp3.Play(MP3_fire);
}

void Controller::Fire()
{
  //Serial.println("Controller::Fire()");
  _fire.FireItUp(*_led,_settings->Setting,_settings->Level);
}

void Controller::SoundInit()
{
  Serial.println("Controller::SoundInit()");
  //maybe switch audio sources here??  (not sure how to work into current remote control scheme..or even how to wire it up...?)
  _mp3.Play(MP3_spectrum);
}

void Controller::Sound()
{
  Serial.println("Controller::Sound()");
  Spectrum spectrum = _eq.ReadSpectrum(_settings->Level);
  _spec.Visualize(*_led, spectrum, _settings->Setting,_settings->Level);
}

void Controller::DemoInit()
{
  Serial.println("Controller::DemoInit()");
  _mp3.Play(MP3_storm);//MP3_demo
}
  
void Controller::Demo()
{
  Serial.println("Controller::Demo()");
  _led->Demo(_settings->Setting,_settings->Level);
}
