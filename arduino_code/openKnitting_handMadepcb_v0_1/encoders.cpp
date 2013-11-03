#include "encoders.h"

#define encoder0PinA 2
#define encoder0PinB 3
#define encoder0PinC 4

void encoders::setup() {
  pinMode(encoder0PinA,INPUT);
  pinMode(encoder0PinB,INPUT);
  pinMode(encoder0PinC,INPUT);
  headDirection = 0;
  encoder1Pos = -2000;
  lastencoder1Pos = -1;
  encoder4Pos = 0;
  lastencoder4Pos = -1;
  lastDirectionEncoders = 0;
  lastStitch =0;
  stitch = -1;
  _8segmentEncoder = 0;
  last_8segmentEncoder = 0;
}


void encoders::calculateDirection() {
  lastDirectionEncoders = directionEncoders;
  directionEncoders = 0;
  if (digitalRead(encoder0PinA)== HIGH) {
    // directionEncoders is ON for encoder A
    directionEncoders += 1;
  }
  else {
    // directionEncoders is OFF for encoder A
    directionEncoders += 0;
  }
  if (digitalRead(encoder0PinB)== HIGH) {
    // directionEncoders is ON for encoder B
    directionEncoders +=3;
  }
  else {
    directionEncoders +=5;
  }
  last_8segmentEncoder = _8segmentEncoder;
  _8segmentEncoder = (digitalRead(encoder0PinC)==HIGH);
}

void encoders::loopNormal() {
  calculateDirection();
  if (lastDirectionEncoders!=directionEncoders) {
    if (
      (lastDirectionEncoders==OFF_OFF && directionEncoders==OFF_OFF)  ||
      (lastDirectionEncoders==OFF_OFF && directionEncoders==ON_OFF) ||
      (lastDirectionEncoders==ON_OFF && directionEncoders==ON_ON)   ||
      (lastDirectionEncoders==ON_ON && directionEncoders==OFF_ON)   ||
      (lastDirectionEncoders==OFF_ON && directionEncoders==OFF_OFF)

    ) {
      headDirection =-1;
      if (encoder1Pos==-2000) {
        encoder4Pos = 1020; //255 * 4
        encoder1Pos = 255;
      }
      encoder4Pos-=1;
      if (encoder4Pos<0) {
        encoder4Pos=0;
      }
    }
    else if (
      (lastDirectionEncoders==OFF_ON && directionEncoders==ON_ON)  ||
      (lastDirectionEncoders==ON_ON && directionEncoders==ON_ON)   ||
      (lastDirectionEncoders==ON_ON && directionEncoders==ON_OFF)  ||
      (lastDirectionEncoders==ON_OFF && directionEncoders==OFF_OFF)||
      (lastDirectionEncoders==OFF_OFF && directionEncoders==OFF_ON)

    ) {
      headDirection =+1;
      if (encoder1Pos==-2000) {
        encoder4Pos = 0;
        encoder1Pos = 0;
      }
      encoder4Pos+=1;
      if (encoder4Pos>1020) { //255 * 4
        encoder4Pos=1020;
      }
    }
  }

  if (encoder4Pos !=0) {
    encoder1Pos = encoder4Pos/4;
    stitch = encoder1Pos-28;
  } else {
    encoder1Pos = 0;
    stitch = -28;
  }
}


void encoders::loopAttachInterrupt() {
  calculateDirection();

  if (lastDirectionEncoders!=directionEncoders) {
    if (lastDirectionEncoders==OFF_ON || directionEncoders==ON_OFF) {
      headDirection =-1;
      if ( encoder1Pos==-2000) {
        encoder1Pos = 255;
      }
      encoder1Pos-=1;
      if (encoder1Pos<0) {
        encoder1Pos=0;
      }
    } else if (lastDirectionEncoders==ON_ON || directionEncoders==OFF_OFF) {
      headDirection =1;
      if ( encoder1Pos==-2000) {
        encoder1Pos = 0;
      }
      encoder1Pos+=1;
      if (encoder1Pos>255) {
        encoder1Pos = 255;
      }
    }
  }
  lastDirectionEncoders = directionEncoders;

  // encoder position had changed
  if (encoder1Pos != lastencoder1Pos) {
    if (encoder1Pos != 0) {
      stitch = encoder1Pos-28;
    } else {
      stitch = -28;
    }
  }
}
