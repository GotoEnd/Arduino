#include "MSGEQ7.h"

byte _finalConstraint;

MSGEQ7::MSGEQ7(){}
MSGEQ7::~MSGEQ7(){}

//TODO
//  use middle band as noise limiter for all (some bands are naturally more noisy)


void MSGEQ7::Initialize(byte constraint)
{
  Serial.println(F("**MSGEQ7 Initializing**"));
  
  _finalConstraint=constraint;

  pinMode(LMSGEQ7, INPUT);        pinMode(RMSGEQ7, INPUT);
  pinMode(LSTROBE, OUTPUT);       pinMode(RSTROBE, OUTPUT);
  pinMode(LRESET, OUTPUT);        pinMode(RRESET, OUTPUT);
    
  analogReference(DEFAULT);

  digitalWrite(LRESET, LOW);      digitalWrite(RRESET, LOW);
  digitalWrite(LSTROBE, HIGH);    digitalWrite(RSTROBE, HIGH);

  Serial.print(F(" -Left Channel:  IN=")); Serial.print(LMSGEQ7); Serial.print(F("  STROBE=")); Serial.print(LSTROBE); Serial.print(F("  RESET=")); Serial.println(LRESET);
  Serial.print(F(" -Right Channel: IN=")); Serial.print(RMSGEQ7); Serial.print(F("  STROBE=")); Serial.print(RSTROBE); Serial.print(F("  RESET=")); Serial.println(RRESET);    
  Serial.println(F("**MSGEQ7 Initialized**")); Serial.println();  
}

Spectrum MSGEQ7::ReadSpectrum(byte level)
{
  //TODO: use level for NOISEFILTER
  Serial.println("  *reading spectrum");
  Spectrum spectrum;
  digitalWrite(LRESET, HIGH);     digitalWrite(RRESET, HIGH);
  digitalWrite(LRESET, LOW);      digitalWrite(RRESET, LOW); 

  for (uint8_t i=0;i<SPECTRUM;i++)
  {
    digitalWrite(LSTROBE, LOW);   digitalWrite(RSTROBE, LOW);
    delay(30);

    int lval=analogRead(LMSGEQ7); int rval=analogRead(RMSGEQ7);

    spectrum.LeftChannel[i]=map(constrain(lval,NOISEFILTER,1023),NOISEFILTER,1023,0,_finalConstraint); 
    spectrum.RightChannel[i]=map(constrain(rval,NOISEFILTER,1023),NOISEFILTER,1023,0,_finalConstraint);

    Serial.print(F("   band "));Serial.print(i); Serial.print(" = "); Serial.print(lval); Serial.print(", "); Serial.print(rval);Serial.println();
    
    digitalWrite(LSTROBE, HIGH);  digitalWrite(RSTROBE, HIGH);
  }
  return spectrum;
}

