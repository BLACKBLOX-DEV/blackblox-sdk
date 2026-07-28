#include "BBProcessorESP32.h"

#include <Wire.h>

namespace blackblox
{

bool BBProcessorESP32::begin()
{
    Wire.begin(0, 1);
    Wire.setClock(400000);

    return true;
}

}