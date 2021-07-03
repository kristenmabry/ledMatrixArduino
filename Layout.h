#ifndef LAYOUT_H
#define LAYOUT_H

#include <RGBmatrixPanel.h>

struct LEDINFO {
  char letter;
  char color[3];
};

   
LEDINFO* buildTextLayout(char* incomingData);
void displayTextLayout(RGBmatrixPanel& matrix, LEDINFO* textChars);
void displayCustomLayout(RGBmatrixPanel& matrix, int counter, char* incomingData);

#endif
