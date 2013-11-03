#include "sound_alerts.h"
#include "arduino.h"

void soundAlerts::setup() {
  piezoPin = 3;
}

void soundAlerts::startMachine() {
  int delayms = 50;
  for(int i=0; i<3; i++) {
    analogWrite(piezoPin, 20);      // Almost any value can be used except 0 and 255
    // experiment to get the best tone
    delay(delayms);             // wait for a delayms ms
    analogWrite(piezoPin, 0);   // 0 turns it off
    delay(delayms);             // wait for a delayms ms
  }
}

void soundAlerts::endPattern(){
  int delayms = 50;
  for(int i=0;i<5;i++){
    analogWrite(piezoPin, 20);      // Almost any value can be used except 0 and 255
    // experiment to get the best tone
    delay(delayms);             // wait for a delayms ms
    analogWrite(piezoPin, 0);   // 0 turns it off
    delay(delayms);             // wait for a delayms ms
  }
}