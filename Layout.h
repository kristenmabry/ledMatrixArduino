#ifndef LAYOUT_H
#define LAYOUT_H

#include <RGBmatrixPanel.h>

struct LEDINFO;

class Layout
{
public:
    Layout(RGBmatrixPanel& matrix, char* incomingData);
    Layout();
    ~Layout();
    void buildTextLayout(RGBmatrixPanel& matrix);
    void displayTextLayout(RGBmatrixPanel& matrix);

private:
    char data[21];
    LEDINFO* textChars;
    uint16_t* pixels;
};

#endif
