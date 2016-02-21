#include "Pub.h"

int _port;

Publisher::Publisher(){}
Publisher::~Publisher(){}

void Publisher::Initialize(int port)
{
  Serial.println(F("**Publisher Initializing**"));

  Wire.begin(); // join i2c bus (address optional for master)
  _port = port;
  SendInitializingStart();
  
  Serial.println(F("**Publisher Initialized**"));
  Serial.println();  
}

void Publisher::SendInitializingStart()
{
  Begin();
    Wire.write(M_INIT_START);
  End();
}

void Publisher::SendAllSettings(byte mode, byte setting, byte level)
{
  Begin();
    Wire.write(M_ALL_SETTINGS);
    Wire.write(mode);
    Wire.write(setting);
    Wire.write(level);
  End();
}

void Publisher::SendMode(byte mode)
{
  Begin();
    Wire.write(M_MODE);
    Wire.write(mode);
  End();
}
  
void Publisher::SendSetting(byte setting)
{
  Begin();
    Wire.write(M_SETTING);
    Wire.write(setting);
  End();
}

void Publisher::SendLevel(byte level)
{
  Begin();
    Wire.write(M_LEVEL);
    Wire.write(level);
  End();  
}

void Publisher::SendInfo(String message)
{
  Begin();
    //TODO: Figure out messaging protocol (begin, message, end), stuff...
  End();  
}

void Publisher::Begin()
{
  Serial.print(F(" -writing to port: ")); Serial.println(_port);
  Wire.beginTransmission(_port);
}

void Publisher::End()
{
  Wire.endTransmission();
}

