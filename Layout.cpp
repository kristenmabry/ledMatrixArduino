#include <RGBmatrixPanel.h>
#include "Layout.h"

struct LEDINFO {
    char letter;
    int color[3];
};

Layout::Layout(RGBmatrixPanel& matrix, char* incomingData)
{
    for (int i = 0; i < 41; ++i)
    {
      data[i] = incomingData[i];
    }
    if (data[0] == 'T')
    {
        textChars = new LEDINFO[10];
        buildTextLayout(matrix);
        displayTextLayout(matrix);
    }
}

Layout::Layout()
{
  return;
}

Layout::~Layout()
{
    if (data[0] == 'T')
    {
        delete[] textChars;
    }
}

void Layout::buildTextLayout(RGBmatrixPanel& matrix)
{
    int letter = 0;
    for (int i = 1; i < 41; i += 4) 
    {
        textChars[letter].letter = data[i];
        textChars[letter].color[0] = data[i + 1] - 48;
        textChars[letter].color[1] = data[i + 2] - 48;
        textChars[letter].color[2] = data[i + 3] - 48;
        ++letter;
    }
};

void Layout::displayTextLayout(RGBmatrixPanel& matrix)
{
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
    matrix.setTextSize(1);   // size 1 == 8 pixels high

    for (int i = 0; i < 5; ++i)
    {
        matrix.setTextColor(matrix.Color333(textChars[i].color[0], textChars[i].color[1], textChars[i].color[2]));
        matrix.print(textChars[i].letter);
    }

    matrix.setCursor(1, 9);  // next line

    for (int i = 5; i < 10; ++i)
    {
        matrix.setTextColor(matrix.Color333(textChars[i].color[0], textChars[i].color[1], textChars[i].color[2]));
        matrix.print(textChars[i].letter);
    }
}
