#include <BLACKBLOX.h>

#include <BLACKBLOX.h>
#include <drivers/BBPCA9633.h>


BBProcessorESP32 processor;
blackblox::BBPCA9633 led;

void setup()
{
    Serial.begin(115200);

    processor.begin();

    if (!led.begin())
    {
        Serial.println("PCA9633 not found.");
        while (true)
            delay(1000);
    }

    Serial.println("PCA9633 found.");
}

void loop()
{
    for (uint8_t channel = 0; channel < 4; channel++)
    {
        Serial.print("Channel ");
        Serial.println(channel);

        led.off();
        led.setChannel(channel, 255);

        delay(1500);
    }

    led.off();
    delay(1500);
}