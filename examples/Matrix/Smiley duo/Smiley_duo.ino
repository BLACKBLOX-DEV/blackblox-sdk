#include <BLACKBLOX.h>

BBRGBMatrix8x16 leftMatrix(0x11);
BBRGBMatrix8x16 rightMatrix(0x12);

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
    BB.begin(0, 1);

    leftMatrix.begin();
    rightMatrix.begin();

    leftMatrix.clear();
    rightMatrix.clear();
}

void loop()
{
    // Red / Blue
    leftMatrix.clear();
    rightMatrix.clear();

    leftMatrix.drawMonoBitmap(0, 0, face, 8, 8, BBColor::Red());
    rightMatrix.drawMonoBitmap(0, 0, face, 8, 8, BBColor::Blue());

    leftMatrix.show();
    rightMatrix.show();

    delay(1000);

    // Green / Yellow
    leftMatrix.clear();
    rightMatrix.clear();

    leftMatrix.drawMonoBitmap(0, 0, face, 8, 8, BBColor::Green());
    rightMatrix.drawMonoBitmap(0, 0, face, 8, 8, BBColor::Yellow());

    leftMatrix.show();
    rightMatrix.show();

    delay(1000);

    // Magenta / Cyan
    leftMatrix.clear();
    rightMatrix.clear();

    leftMatrix.drawMonoBitmap(0, 0, face, 8, 8, BBColor::Magenta());
    rightMatrix.drawMonoBitmap(0, 0, face, 8, 8, BBColor::Cyan());

    leftMatrix.show();
    rightMatrix.show();

    delay(1000);
}