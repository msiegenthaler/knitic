#ifndef SOLENOIDS_H_
#define SOLENOIDS_H_

#include "arduino.h"
#include "encoders.h"
#include "endLines.h"

class solenoids{
private:
  encoders* myEncoders;
  endLines* myEndlines;
  byte myDataOut;
  int amegaPinsArray[16];
  int ledArray[16];

public:
  int pixelBin[256];
  int currentPixState;
  int currentStitchSetup;
  int currentSolenoidIDSetup;
  boolean changed;
  boolean solenoidstate[16];
  boolean solenoidstateOn[16];
  String _16solenoids;
  boolean sectionPosition;

public:
  solenoids();
  ~solenoids() {}

  void setup(endLines* _myEndlines,encoders* _myEncoders);
  void loop();

private:
  void ifChanged();
  boolean isCurrentSolenoid(int i,int r);
  void setArduinoMegaPins();
};
#endif



















