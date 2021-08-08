# LED Matrix - Arduino

This is the Arduino code for the LED Bluetooth Sign Project

[Link to related Android app repository](https://github.com/kristenmabry/ledMatrixApp)

Components:
- Arduino UNO Board
- HC-05 Bluetooth Module
- Adafruit 16x32 LED Matrix

## Bluetooth Messages
There are 3 different messages that can be sent to the Arduino based on the starting character:
1. 'T': Send a new text layout to the Arduino.
    - Each character is made up of 2 bytes to send the color (RGB) and the ascii character code (C). The format is RRRG GGBB BCCC CCCC.
    - 10 characters total are sent which make up two lines of 5 characters.
2. 'C': Send a custom layout to the Arduino.
    - TODO: The second character is the number of total sections that will be sent.
    - The third character is either 'H' for horizontal or 'V' for vertical. This determines the direction to build the layout in.
    - Each section contains the count (C) of how many pixels to set and the color (RGB). The format is CCCC CCCR RRGG GBBB.
      - TODO: Swap count and color to match the text layout
      - TODO: Change matrix.drawPixel to matrix.fillRect to reduce iterations
3. 'S': Request the current layout.
    - The current layout, either text or custom, is sent back over bluetooth in the same format it was sent in.

After each new layout, the data is stored in EEPROM. When turning the sign off and back on, the layout is restored.

## Concepts Used
1. States
    - Since only one character can be read from the bluetooth module in each loop of the main function, a state is used to keep track of what is happening.
    - There is a state for waiting, receiving a text layout, setting the text layout, receiving a custom layout, setting the custom layout, and sending the current layout.
2. Bit manipulation
    - Bit manipulation is needed to extract the color and character from the bytes received.
3. UART
    - The bluetooth module uses the UART communication protocol.
