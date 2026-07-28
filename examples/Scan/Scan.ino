#include <Wire.h>

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(0, 1);
    Wire.setClock(100000);

    Serial.println("I2C scan:");

    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("Najden naslov: 0x");

            if (address < 16)
                Serial.print('0');

            Serial.println(address, HEX);
        }
    }

    Serial.println("Scan končan.");
}

void loop()
{
}