#ifndef LAYOUT_H
#define LAYOUT_H

#include <RGBmatrixPanel.h>

struct LEDINFO {
  char letter;
  char color[3];
};

class Layout
{
  public:
    // Layout(RGBmatrixPanel& matrix, char* incomingData);
    // Layout(RGBmatrixPanel& matrix, char* incomingData, int counter);
    void buildTextLayout(char* incomingData);
    void displayTextLayout(RGBmatrixPanel& matrix);
    void displayCustomLayout(RGBmatrixPanel& matrix, int counter, char* incomingData);

  private:
    LEDINFO textChars[10];
};

#endif
