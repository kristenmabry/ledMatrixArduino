#include <SoftwareSerial.h>
#include <RGBmatrixPanel.h>
#include <EEPROM.h>
#include "Bluetooth.h"
#include "Layout.h"

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

#define TLENGTH 21
#define CLENGTH 512

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(11, 12); /* (Rx,Tx) */

State state = State::Start;
int counter = 0;
char btBuffer[CLENGTH] = {};

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  bt.begin(9600); /* Define baud rate for software serial communication */
  matrix.begin();

  btBuffer[0] = EEPROM.read(0);
  if (btBuffer[0] == 'T')
  {
    for (int i = 1; i < TLENGTH; ++i)
    {
      btBuffer[i] = EEPROM.read(i);
    }

    LEDINFO* text = buildTextLayout(btBuffer);
    displayTextLayout(matrix, text);
    delete[] text;
  }
  
}

void loop() {
  state = getIncomingData(bt, state, counter, btBuffer);

  if (state != State::Start)
  {
    Serial.print(state, DEC);
    Serial.println("State");
  }
  if (state == State::FinishText)
  {
    LEDINFO* text = buildTextLayout(btBuffer);
    displayTextLayout(matrix, text);
    delete[] text;

    for (int i = 0; i < TLENGTH; ++i)
    {
      EEPROM.write(i, btBuffer[i]);
    }

    state = State::Start;
  }
  else if (state == State::SendLayout && counter == 0)
  {
    for (int i = 1; i < TLENGTH; ++i)
    {
      btBuffer[i] = EEPROM.read(i);
    }
  }
  else if (state == State::FinishCustom)
  {
    displayCustomLayout(matrix, counter, btBuffer);
    Serial.println("Finish Custom");
    state = State::Start;
  }
}
