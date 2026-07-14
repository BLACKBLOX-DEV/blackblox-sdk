#include "BB.h"
#include "../transport/BBI2C.h"

namespace blackblox
{
    BBClass BB;

    bool BBClass::begin()
    {
        return true;
    }

    bool BBClass::begin(int sda, int scl)
    {
        return BBI2C::begin(sda, scl);
    }
}