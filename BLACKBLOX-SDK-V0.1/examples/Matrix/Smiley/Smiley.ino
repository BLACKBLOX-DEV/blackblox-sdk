#include <BLACKBLOX.h>

BBRGBMatrix8x16 matrix(0x10);

const uint8_t face[] =
{
    0b00111100,
    0b01111110,
    0b11111111,
    0b11011011,
    0b11111111,
    0b10111101,
    0b01100110,
    0b00111100
};

void setup()
{
    BB.begin(0,1);

    matrix.begin();
    matrix.clear();

    matrix.drawMonoBitmap(
        0,
        0,
        face,
        8,
        8,
        BBColor::Yellow());

    matrix.show();
}

void loop()
{
}