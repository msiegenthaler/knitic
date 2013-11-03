#ifndef ENCODERS_H_
#define ENCODERS_H_

// table created to get combinations
/*
table encoder position an values id
 OFF_ON  = 0+3 = 3
 ON_OFF  = 1+5 = 6
 ON_ON   = 1+3 = 4
 OFF_OFF = 0+5 = 5 
 */
#define OFF_ON 3
#define ON_OFF 6
#define ON_ON 4
#define OFF_OFF 5

#include "arduino.h"

class encoders{
private:
  short directionEncoders;
  short lastDirectionEncoders;
  int encoder4Pos;
  int lastencoder4Pos;
  boolean last_8segmentEncoder;

public:
  int encoder1Pos;
  int lastencoder1Pos;
  int stitch;
  int lastStitch;
  int headDirection;
  boolean _8segmentEncoder;

private:
  void calculateDirection();

public:
  encoders() {}
  ~encoders() {}

  void setup();
  void loopNormal();
  // interup handler on changes to encoder0PinA
  void loopAttachInterrupt();
};
#endif

