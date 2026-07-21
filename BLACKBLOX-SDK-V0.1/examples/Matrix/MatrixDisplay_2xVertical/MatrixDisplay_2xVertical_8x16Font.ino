#include <BLACKBLOX.h>

#include <display/BBMatrixDisplay.h>
#include <graphics/fonts/BBFont8x16.h>
#include <modules/BBRGBMatrix8x16.h>

using namespace blackblox;

BBRGBMatrix8x16 top(0x11);
BBRGBMatrix8x16 bottom(0x12);

BBMatrixDisplay display(16, 16);

void setup()
{
    BB.begin(0, 1);

    top.begin();
    bottom.begin();

    display.attach(top,    0, 0, BBMatrixRotation::R0);
    display.attach(bottom, 0, 8, BBMatrixRotation::R0);

    display.clear();

    const BBFont& font = BBFont8x16::font();

    display.drawChar(
        4,
        0,
        '2',
        font,
        BBColor(255, 255, 255));

    display.show();
}

void loop()
{
}