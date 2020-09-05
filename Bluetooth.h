#ifndef BLUETOOTH_H
#define BLUETOOTH_H

enum State: int { 
  Start = 0,
  StartText = 1,
  ReceiveText = 2,
  StartCustom = 3,
  ReceiveCustom = 4,
  Finish = 5,
  SendLayout = 6
};

State getIncomingData(SoftwareSerial& bt, State state, int& counter, char* buffer);

#endif
