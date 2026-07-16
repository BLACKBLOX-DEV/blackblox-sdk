struct BBColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    constexpr BBColor()
        : r(0), g(0), b(0)
    {
    }

    constexpr BBColor(
        uint8_t red,
        uint8_t green,
        uint8_t blue)
        : r(red), g(green), b(blue)
    {
    }

    // Off(), Red(), Green() ...
};