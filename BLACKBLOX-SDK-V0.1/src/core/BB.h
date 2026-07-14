#pragma once

namespace blackblox
{
    class BBClass
    {
    public:
        bool begin();
        bool begin(int sda, int scl);
    };

    extern BBClass BB;
}