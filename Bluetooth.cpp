#include <SoftwareSerial.h>
#include "Bluetooth.h"

State getIncomingData(SoftwareSerial& bt, State state, int& counter, char* buffer)
{
    if (state == State::SendLayout)
    {
      bt.write(buffer[counter++]);
      if (counter == 21)
      {
        counter = 0;
        return State::Finish;
      }
    }
    else if (!bt.available())
    {
        return state;
    }
    else if (state == State::Start)
    {
        char first = bt.read();
        if (first == 'T')
        {
            buffer[0] = first;
            counter = 1;
            return State::ReceiveText;
        }
        else if (first == 'S')
        {
          counter = 0;
          return State::SendLayout;
        }
    }
    else if (state == State::ReceiveText)
    {
        char letter = bt.read();
        buffer[counter++] = letter;
        if (counter == 21)
        {
            return State::Finish;
        }
    }
    return state;
}
