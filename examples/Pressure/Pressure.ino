#include <BLACKBLOX.h>

BBProcessorESP32 processor;
BBWSENPADS pressure;

void setup()
{
    Serial.begin(115200);

    processor.begin();

    if (!pressure.begin())
    {
        Serial.println("Pressure sensor not found.");
        while (true)
        {
            delay(1000);
        }
    }
}

void loop()
{
    float p;
    float t;

    if (pressure.read(p, t))
    {
        Serial.print("Pressure: ");
        Serial.print(p);
        Serial.print(" kPa");

        Serial.print("  Temperature: ");
        Serial.print(t);
        Serial.println(" °C");
    }

    delay(1000);
}