#ifndef BLUETOOTH_H
#define BLUETOOTH_H

enum State: char { 
  Start = 0,
  ReceiveText = 1,
  FinishText = 2,
  ReceiveCustom = 3,
  FinishCustom = 4,
  SendLayout = 5
};

State getIncomingData(SoftwareSerial& bt, State state, int& counter, char* buffer);

#endif
