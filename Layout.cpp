#include <RGBmatrixPanel.h>
#include "Layout.h"

/*
struct LEDINFO {
    char letter;
    char color[3];
};
*/

/*
Layout::Layout(RGBmatrixPanel& matrix, char* incomingData)
{
    buildTextLayout(matrix, incomingData);
    displayTextLayout(matrix);
}

Layout::Layout(RGBmatrixPanel& matrix, char* incomingData, int counter)
{
    pixels = counter;
    displayCustomLayout(matrix, incomingData);
}
*/

void Layout::buildTextLayout(char* incomingData)
{
  int letter = 0;
  for (int i = 1; i < 21; i += 2) 
  {
    textChars[letter].color[0] = (incomingData[i] >> 5) & 0b111;
    textChars[letter].color[1] = (incomingData[i] >> 2) & 0b111;
    textChars[letter].color[2] = ((incomingData[i] & 0b11) << 1) + (incomingData[i+1] & (1 << 7));
    textChars[letter].letter = incomingData[i + 1] & ~(1 << 7);
    ++letter;
  }
}

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

void Layout::displayCustomLayout(RGBmatrixPanel& matrix, int counter, char* incomingData)
{
    matrix.fillScreen(matrix.Color333(0, 0, 0));

    int x = 0;
    int y = 0;
    for (int section = 1; section < counter; section += 2)
    {
        unsigned char count = incomingData[section] >> 1;
        char r = ((incomingData[section] & 1) << 2) + ((incomingData[section+1] >> 6) & 0b11);
        char g = (incomingData[section+1] >> 3) & 0b111;
        char b = incomingData[section+1] & 0b111;
        for (int i = 0; i < count + 1; ++i)
        {
            matrix.drawPixel(x++, y, matrix.Color333(r, g, b));
            if (x == 32)
            {
                x = 0;
                ++y;
            }
        }
    }
}
