#include "solenoids.h"

solenoids::solenoids() {
  pixelBin[0] = 1;
  pixelBin[1] = 1;
  pixelBin[8] = 1;
  int ledArrayTemp[16] = { 38,40,42,44,46,48,50,52,5,6,43,45,47,49,51,7 };
  int amegaPinsArrayTemp[16] = { 22,24,26,28,30,32,34,36,37,35,33,31,29,27,25,23 };
  for(int i=0; i<16; i++) {
    amegaPinsArray[i] = amegaPinsArrayTemp[i];
    ledArray[i] = ledArrayTemp[i];
    pinMode(amegaPinsArrayTemp[i], OUTPUT);
    pinMode(ledArrayTemp[i], OUTPUT);
  }
}

void solenoids::setup(endLines* _myEndlines,encoders* _myEncoders){
  sectionPosition = false;
  myEndlines = _myEndlines;
  myEncoders = _myEncoders;
  changed = false;
  for (int i=0; i<16; i++) {
    solenoidstate[i] = 0;
    solenoidstateOn[i] = 0;
  }
}

void solenoids::loop() {
  if (myEncoders->lastStitch!=myEncoders->stitch) {
    myEncoders->lastStitch = myEncoders->stitch;
    // RIGHT direction
    if (myEncoders->headDirection == -1) {
      int pos = myEncoders->encoder1Pos;
      if(pos > 15){
        int i = abs(pos-8) % 16;
        if (myEndlines->phase == 0) {
          i = abs(pos-8)%16; // maybe +8
        } else {
          // validated
          i = abs(pos)%16;
        }

        int currentStitchSetup = pos-16;
        if (currentStitchSetup >= 0 && currentStitchSetup < 254) {
          int currentPixState = pixelBin[currentStitchSetup];
          if (solenoidstateOn[i] != (currentPixState == 1) ){
            digitalWrite(amegaPinsArray[i], currentPixState);
            digitalWrite(ledArray[i], currentPixState);
            solenoidstateOn[i] = (currentPixState == 1);
          }
        }
      }
    } else if (myEncoders->headDirection == 1) {
      // LEFT direction
      int pos = myEncoders->encoder1Pos;
      if(pos < 256-8 ){
        int i;
        if (myEndlines->phase == 0) {
          // validated
          i = abs(pos+8) % 16; //was 0, means no +8
        } else {
          i = abs(pos) % 16; // -8
        }

        int currentStitchSetup = pos-40;
        if (currentStitchSetup >= 0 && currentStitchSetup < 254) {
          int currentPixState = pixelBin[currentStitchSetup];
          if( solenoidstateOn[i] != (currentPixState == 1)) {
            digitalWrite(amegaPinsArray[i], currentPixState);
            digitalWrite(ledArray[i], currentPixState);
            solenoidstateOn[i] = (currentPixState == 1);
          }
        }
      }
    }
    // Set all solenoids OFF when end of line
    if (myEncoders->encoder1Pos==0 || myEncoders->encoder1Pos == 255 ) {
      for (int i=0; i<16; i++) {
        digitalWrite(amegaPinsArray[i], LOW);
        digitalWrite(ledArray[i], LOW);
        solenoidstateOn[i] = false;
      }
    }
  }
}

void solenoids::ifChanged() {
  if(changed){
    changed = false;
    setArduinoMegaPins();
  }
}

boolean solenoids::isCurrentSolenoid(int i,int r) {
  int stitch = myEncoders->stitch;
  int headDirection = -myEncoders->headDirection;
  return ((stitch<=176 && stitch>=-24 && headDirection==-1)
      && ((stitch-2+(i*headDirection))%16)==r );
}

void solenoids::setArduinoMegaPins(){
  for (int i=0; i<16; i++) {
    if (solenoidstate[i]) {
      if (!solenoidstateOn[i]) {
        digitalWrite(amegaPinsArray[i], HIGH);
        digitalWrite(ledArray[i], HIGH);
        solenoidstateOn[i] = true;
      }
    } else if(solenoidstateOn[i]) {
      digitalWrite(amegaPinsArray[i], LOW);
      digitalWrite(ledArray[i], LOW);
      solenoidstateOn[i] = false;
    }
  }
}
