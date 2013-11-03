#include "communication.h"

void communication::setup(encoders* _myEncoders, endLines* _myEndlines, solenoids* _mysolenoids) {
  myEncoders = _myEncoders;
  myEndlines = _myEndlines;
  mysolenoids = _mysolenoids;
  lastSendTimeStamp = millis();
  dataSize = 201;
  footer = 126;
  dataReplace = false;
  readCnt = 0;
  lf = '@';    // AT in ASCII
  // table - bit encoding
  unsigned int bitRegister16SolenoidTemp[16] = { 32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1 };
  for (int i=0; i<16; i++) {
    bitRegister16Solenoid[i] = bitRegister16SolenoidTemp[i];
  }
  Serial.setTimeout(10);
}


void communication::sendSerialToComputer(){
  if ((myEncoders->lastencoder1Pos != myEncoders->encoder1Pos) || (millis()-lastSendTimeStamp) > 500) {
    lastSendTimeStamp = millis();
    Serial.print(",");
    Serial.print(myEncoders->stitch);
    Serial.print(",");
    Serial.print(myEncoders->headDirection);
    Serial.print(",");
    if(myEndlines->phase) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.println(lf);
    myEncoders->lastencoder1Pos = myEncoders->encoder1Pos;
  }
}

void communication::checkSolenoid(int i) {
  if( bitRegister16Solenoid[i] == (received & bitRegister16Solenoid[i])) {
    if(mysolenoids->solenoidstate[i] !=true){
      mysolenoids->solenoidstate[i] = true;
      mysolenoids->changed = true;
    }
  }
  else{
    if(mysolenoids->solenoidstate[i] !=false){
      mysolenoids->solenoidstate[i] = false;
      mysolenoids->changed = true;
    }
  }
}

void communication::set16Solenoids() {
  if(lastReceived != received){
    lastReceived = received;
    for(int i=0; i<16; i++){
      checkSolenoid(i);
    }

  }
}

void communication::receiveAllLine() {
  while (Serial.available() > 0) {
    if (Serial.readBytesUntil(footer, receivedBin, dataSize)) {
      dataReplace = true;
    }
  }
  if (dataReplace) {
      sendCurrentPixelArray();
      dataReplace = false;
  }
}

// send to processing
void communication::sendCurrentPixelArray() {
  Serial.println(lf);
  for (int i=0; i<200; i++){
    mysolenoids->pixelBin[i] = receivedBin[i];
    Serial.print(String(mysolenoids->pixelBin[i]));
  }
  Serial.println(lf);
}

// get data from processing
void communication::receiveRealtimeFromComputer() {
  boolean isReceived = false;
  char buffer[2];
  while(Serial.available() > 0) {
    Serial.readBytesUntil(',', &buffer[0], 4);
    received = 0;
    received = buffer[0] <<8;
    received = received | buffer[1];
    isReceived = true;
  }
  if(isReceived){
    set16Solenoids();
  }
}
