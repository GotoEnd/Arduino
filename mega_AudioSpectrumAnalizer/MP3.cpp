#include "MP3.h"
#include <SoftwareSerial.h>
#include <DFRobot_utility.h>
#include <DFPlayer_Mini_Mp3.h>

#define CHECK_SUCCESS_RETRY 3
#define SEND_COMMAND_RETRY  3

SoftwareSerial _serial(RX,TX);

MP3::MP3(){}
MP3::~MP3(){}

void MP3::Initialize()
{
  Serial.println(F("**MP3 Initializing**"));
  Serial.print(F(" RX: "));Serial.print(RX);Serial.print(F(", TX: "));Serial.println(TX);

  _serial.begin(9600);  while(!_serial){}
  mp3_set_serial(_serial);
  
  delay(1000); CheckLastCommand(0,0); //for shits..
  SetVolume(30);
  
  //TODO: check for init?

  Serial.println(F("**MP3 Initialized**"));
}

void MP3::SetVolume(uint16_t volume)
{
  SendCommandArgs(CMD_VOLUME, volume,0);
}

void MP3::Play(MP3Tracks track)
{
  Serial.print("MP3::Play: ");Serial.println(track);
  SendCommand(CMD_STOP,0);
  SendCommandArgs(CMD_PLAYMP3, track,0);
}

void MP3::Pause()
{
  SendCommand(CMD_PAUSE,0);
}

void MP3::Resume()
{
  SendCommand(CMD_PAUSE,0);
}

void MP3::Stop()
{
  SendCommand(CMD_STOP,0);
}


void MP3::SendCommand(byte command, byte pass)
{
  Serial.print("  -send command: ");Serial.println(command,HEX);
  mp3_send_cmd(command);
  delay(100);
  if(!CheckLastCommand(command,0) && pass < SEND_COMMAND_RETRY)
  {
    Serial.print("   ** send command failed; pass: ");Serial.println(pass);
    delay(100);
    SendCommand(command, ++pass);
  }
}

void MP3::SendCommandArgs(byte command, uint16_t args, byte pass)
{
  Serial.print(" send command with args: ");Serial.print(command,HEX);Serial.print(" -args: ");Serial.println(args);
  mp3_send_cmd(command, args);
  delay(100);
  if(!CheckLastCommand(command,0) && pass < SEND_COMMAND_RETRY)
  {
    Serial.print("   ** send command failed; pass: ");Serial.println(pass);
    delay(100);
    SendCommandArgs(command, args, ++pass);
  }
}

bool MP3::CheckLastCommand(byte expected, byte pass)
{
  //replies start with 7E FF, end with EF
  Serial.print("  -get reply for: ");Serial.print(expected,HEX);Serial.print(", pass: ");Serial.println(pass);
  uint8_t __recv_buf[CMD_SIZE];
  byte counter=0;
  bool done = false;
  bool success = true;

  delay(10);
  while (_serial.available() && !done) 
  {
    byte value = _serial.read();
    __recv_buf[counter]= value;

    //TODO: validation against message header, version, size and checksum if needed
    //check for error
    if(counter == CMD_OFFSET) {
      if(value==GET_ERROR)
          success=false;
      else {
        //TODO: check against expected reply if needed
      }
    }
    //check for end-of-message
    if(value==CMD_END)
      done=true;
  
    delay(1);
    counter++;
  }
  
  Serial.print("  -received: "); printHex (__recv_buf, counter);
  Serial.println();

  if(!success && pass<CHECK_SUCCESS_RETRY){
    Serial.print("   ** check last command failed; pass: ");Serial.println(pass);
    return CheckLastCommand(expected, ++pass);
  }
  return success;
}
