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

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(11, 12); /* (Rx,Tx) */

State state = State::Start;
int counter = 0;
char* buffer;
Layout layout;

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  bt.begin(9600); /* Define baud rate for software serial communication */
  matrix.begin();

  buffer = new char[TLENGTH];

  for (int i = 0; i < TLENGTH; ++i)
  {
    buffer[i] = EEPROM.read(i);
  }
  if (buffer[0] == 'T')
  {
    layout = Layout(matrix, buffer);
  }
}

void loop() {
  state = getIncomingData(bt, state, counter, buffer);
  
  if (state == State::Finish)
  {
    layout = Layout(matrix, buffer);

    for (int i = 0; i < TLENGTH; ++i)
    {
      EEPROM.write(i, buffer[i]);
    }
    
    state = State::Start;
  }
  else if (state == State::SendLayout)
  {
    buffer = layout.getTextLayout();
  }
}
