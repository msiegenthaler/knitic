#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "arduino.h"

#include "encoders.h"
#include "solenoids.h"
#include "endLines.h"

class communication{
private:
  encoders* myEncoders;
  endLines* myEndlines;
  solenoids* mysolenoids;
  unsigned long lastSendTimeStamp;
  int readCnt;
  unsigned int received;
  unsigned int lastReceived;
  unsigned int bitRegister16Solenoid[16];
  char receivedBin[201];
  int dataSize;
  boolean dataReplace;
  boolean startSend200pix;
  byte footer;
  char lf;

public:
  String _status;

public:
  communication() {}
  ~communication() {}

  void setup(encoders* _myEncoders, endLines* _myEndlines, solenoids* _mysolenoids);

  // send data to processing
  void sendSerialToComputer();
  void receiveAllLine();

private:
  void checkSolenoid(int i);
  void set16Solenoids();
  void sendCurrentPixelArray();
  void receiveRealtimeFromComputer();
};

#endif





