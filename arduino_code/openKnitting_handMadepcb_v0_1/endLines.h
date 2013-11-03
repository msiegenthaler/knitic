#ifndef ENDLINES_H_
#define ENDLINES_H_

#include "arduino.h"
#include "sound_alerts.h"
#include "encoders.h"

class endLines{
private:
  soundAlerts* mySoundAlerts;
  int endLineLeftAPin;  // analog arduino pin
  int endLineRightAPin; // analog arduino pin
  encoders* myEncoders;
  int filterValueLeftMin;
  int filterValueRightMin;
  int filterValueLeftMax;
  int filterValueRightMax;
  int maxLeft;
  int maxRight;

public:
  int valueEndLineLeft;
  int valueEndLineRight;
  int phase;

public:
  endLines() {}
  ~endLines() {}

  void setup();
  void setPosition(encoders* _myEncoders, soundAlerts* _mySoundAlerts);
  void loop();
};
#endif

