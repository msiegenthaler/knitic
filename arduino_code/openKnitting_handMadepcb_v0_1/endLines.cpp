#include "endLines.h"

void endLines::setup() {
  maxLeft = 0;
  maxRight= 0;
  endLineLeftAPin = 1;
  endLineRightAPin = 0;
  filterValueLeftMin = 10;
  filterValueRightMin = 10;
  filterValueLeftMax = 460;
  filterValueRightMax = 460;
}

void endLines::setPosition(encoders* _myEncoders, soundAlerts* _mySoundAlerts) {
  myEncoders = _myEncoders;
  mySoundAlerts = _mySoundAlerts;
}

void endLines::loop() {
  // Left end of line - looking change phase
  if (myEncoders->headDirection ==- 1) {
    valueEndLineLeft  = analogRead(endLineLeftAPin);
    if (valueEndLineLeft < filterValueLeftMin || analogRead(endLineLeftAPin) > filterValueLeftMax) {
      if(myEncoders->_8segmentEncoder) phase = 1;
      else phase = 0;
    }
  }
  // Right end of line - looking change phase
  if (myEncoders->headDirection == 1) {
    valueEndLineRight = analogRead(endLineRightAPin);
    if (valueEndLineRight < filterValueRightMin || analogRead(endLineRightAPin) > filterValueRightMax) {
      if(myEncoders->_8segmentEncoder) phase = 1;
      else phase = 0;
    }
  }
}
