#include <SoftwareSerial.h>
#include "Bluetooth.h"

State getIncomingData(SoftwareSerial& bt, State state, int& counter, char* buffer)
{
    if (state == State::SendLayout)
    {
      bt.write(buffer[counter++]);
      if (buffer[0] == 'T' && counter == 21)
      {
        counter = 0;
        return State::Start;
      }
      else if (buffer[0] == 'C' && buffer[counter - 1] == 0 && buffer[counter-2] == 0)
      {
        counter = 0;
        return State::Start;
      }
    }
    else if (!bt.available())
    {
      if (state == State::ReceiveCustom)
      {
        return State::FinishCustom;
      }
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
        else if (first == 'C')
        {
          buffer[0] = first;
          counter = 1;
          return State::ReceiveCustom;
        }
    }
    else if (state == State::ReceiveText)
    {
        char letter = bt.read();
        buffer[counter++] = letter;
        if (counter == 21)
        {
            return State::FinishText;
        }
    }
    else if (state == State::ReceiveCustom)
    {
      char letter = bt.read();
      buffer[counter++] = letter;
    }

    return state;
}
