#ifndef SOUNDALERTS_H_
#define SOUNDALERTS_H_

class soundAlerts {
private:
  int piezoPin; // analog pin

public:
  soundAlerts() {}
  ~soundAlerts() {}

  void setup();
  void startMachine();
  void endPattern();
};

#endif