#include <BLACKBLOX.h>

BBRGBMatrix8x16 matrix(0x10);

void setup()
{
    BB.begin(0, 1);   // BLACKBLOX ESP32-S3: SDA=GPIO0, SCL=GPIO1
    matrix.begin();

    matrix.fill(BBColor::Blue());
    delay(1000);

    matrix.clear();

    matrix.setPixel(0, 0, BBColor::Red());
    matrix.setPixel(1, 0, BBColor::Green());
    matrix.setPixel(2, 0, BBColor::Blue());
    matrix.setPixel(3, 0, BBColor::White());

    matrix.show();
}

void loop()
{
}