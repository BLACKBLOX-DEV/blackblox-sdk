#include "BB.h"
#include "../transport/BBI2C.h"

namespace blackblox
{

bool BBClass::begin()
{
    return BBI2C::begin(0, 1);
}

bool BBClass::begin(int sda, int scl)
{
    return BBI2C::begin(sda, scl);
}

BBClass BB;

}