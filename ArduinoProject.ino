#include <SoftwareSerial.h>
#include <RGBmatrixPanel.h>
#include "Bluetooth.h"
#include "Layout.h"

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

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
 
  // draw some text!
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('1');
  matrix.setTextColor(matrix.Color333(7,4,0));
  matrix.print('6');
  matrix.setTextColor(matrix.Color333(7,7,0));
  matrix.print('x');
  matrix.setTextColor(matrix.Color333(4,7,0));
  matrix.print('3');
  matrix.setTextColor(matrix.Color333(0,7,0));
  matrix.print('2');

  matrix.setCursor(1, 9);  // next line
  matrix.setTextColor(matrix.Color333(0,7,7));
  matrix.print('*');
  matrix.setTextColor(matrix.Color333(0,4,7));
  matrix.print('R');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('G');
  matrix.setTextColor(matrix.Color333(4,0,7));
  matrix.print('B');
  matrix.setTextColor(matrix.Color333(7,0,4));
  matrix.print('*');

  buffer = new char[21];
}

void loop() {
  state = getIncomingData(bt, state, counter, buffer);
  
  if (state == State::Finish)
  {
    layout = Layout(matrix, buffer);
    state = State::Start;
  }
}
