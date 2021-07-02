# LED Matrix - Arduino

[Link to related Android app repository](https://github.com/kristenmabry/ledMatrixApp)

This is the Arduino code for the LED Bluetooh Sign Project
 - The HC-05 Bluetooth module reads incoming data and turns it into a text layout for the LED matrix to display.
 - The text layout is stored in EEPROM. When the Arduino is turned off and back on, the last layout will be restored.
 - The current text layout is sent when requested.
 
 To Do:
  - Handle custom layouts
