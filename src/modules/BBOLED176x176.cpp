#include "BBOLED176x176.h"

namespace blackblox
{

BBOLED176x176::BBOLED176x176(
    TwoWire& wire,
    uint8_t address,
    int8_t resetPin)
    : BBGraphics(Width, Height),
      _controller(wire, address, resetPin),
      _dirtyX0(0),
      _dirtyY0(0),
      _dirtyX1(0),
      _dirtyY1(0),
      _dirty(false)
{
}

// ============================================================================
//  Lifecycle
// ============================================================================

bool BBOLED176x176::begin()
{
    // BBGraphics allocates 92 928 bytes in its constructor. If that failed
    // there is nothing to display, so fail early with a clear signal rather
    // than dereferencing a null framebuffer later.
    if (!isValid())
    {
        return false;
    }

    if (!_controller.begin())
    {
        return false;
    }

    // The controller comes out of begin() configured but asleep. Clear
    // GDDRAM first so the undefined power-on contents are never shown,
    // then enable the panel.
    if (!_controller.fillScreen(0x0000))
    {
        return false;
    }

    if (!_controller.displayOn())
    {
        return false;
    }

    clear();
    clearDirty();

    return true;
}

bool BBOLED176x176::isInitialized() const
{
    return _controller.isInitialized() && isValid();
}

bool BBOLED176x176::isConnected()
{
    return _controller.isConnected();
}

BBSSD1333Status BBOLED176x176::lastStatus() const
{
    return _controller.lastStatus();
}

const char* BBOLED176x176::statusString(BBSSD1333Status status)
{
    return BBSSD1333::statusString(status);
}

// ============================================================================
//  Presenting the framebuffer
// ============================================================================

bool BBOLED176x176::pushRegion(
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1)
{
    if (!_controller.setWindow(x0, y0, x1, y1))
    {
        return false;
    }

    const BBColor* pixels = framebuffer();

    if (pixels == nullptr)
    {
        return false;
    }

    // The window is armed once; the controller advances its own address
    // pointer horizontally and wraps to the next row at the window edge
    // (remap bit A[0] = 0), so the region streams as one contiguous run.
    //
    // Staging exactly one I2C chunk keeps setChunkPixels() meaningful:
    // each flush becomes a single transaction.
    const uint16_t stageBytes =
        static_cast<uint16_t>(_controller.chunkPixels() * 2u);

    uint16_t staged = 0;

    for (uint16_t y = y0; y <= y1; ++y)
    {
        for (uint16_t x = x0; x <= x1; ++x)
        {
            const BBColor& color = pixels[pixelIndex(x, y)];

            const uint16_t value = BBSSD1333::toRgb565(
                color.r,
                color.g,
                color.b);

            _stage[staged++] = static_cast<uint8_t>(value >> 8);
            _stage[staged++] = static_cast<uint8_t>(value & 0xFF);

            if (staged >= stageBytes)
            {
                if (!_controller.writePixels(_stage, staged))
                {
                    return false;
                }

                staged = 0;
            }
        }
    }

    if (staged > 0)
    {
        if (!_controller.writePixels(_stage, staged))
        {
            return false;
        }
    }

    return true;
}

bool BBOLED176x176::show()
{
    if (!isInitialized())
    {
        return false;
    }

    const bool ok = pushRegion(
        0,
        0,
        static_cast<uint8_t>(Width - 1),
        static_cast<uint8_t>(Height - 1));

    if (ok)
    {
        clearDirty();
    }

    return ok;
}

bool BBOLED176x176::showRegion(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height)
{
    if (!isInitialized())
    {
        return false;
    }

    if (width <= 0 || height <= 0)
    {
        return true;
    }

    // Clip in signed arithmetic before narrowing, so negative origins and
    // oversized rectangles cannot wrap around.
    int32_t x0 = x;
    int32_t y0 = y;
    int32_t x1 = static_cast<int32_t>(x) + width  - 1;
    int32_t y1 = static_cast<int32_t>(y) + height - 1;

    if (x0 < 0) { x0 = 0; }
    if (y0 < 0) { y0 = 0; }

    if (x1 > static_cast<int32_t>(Width)  - 1) { x1 = Width  - 1; }
    if (y1 > static_cast<int32_t>(Height) - 1) { y1 = Height - 1; }

    if (x0 > x1 || y0 > y1)
    {
        return true;                    // fully off-screen
    }

    return pushRegion(
        static_cast<uint8_t>(x0),
        static_cast<uint8_t>(y0),
        static_cast<uint8_t>(x1),
        static_cast<uint8_t>(y1));
}

void BBOLED176x176::markDirty(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    int32_t x0 = x;
    int32_t y0 = y;
    int32_t x1 = static_cast<int32_t>(x) + width  - 1;
    int32_t y1 = static_cast<int32_t>(y) + height - 1;

    if (x0 < 0) { x0 = 0; }
    if (y0 < 0) { y0 = 0; }

    if (x1 > static_cast<int32_t>(Width)  - 1) { x1 = Width  - 1; }
    if (y1 > static_cast<int32_t>(Height) - 1) { y1 = Height - 1; }

    if (x0 > x1 || y0 > y1)
    {
        return;
    }

    if (!_dirty)
    {
        _dirtyX0 = static_cast<int16_t>(x0);
        _dirtyY0 = static_cast<int16_t>(y0);
        _dirtyX1 = static_cast<int16_t>(x1);
        _dirtyY1 = static_cast<int16_t>(y1);
        _dirty   = true;

        return;
    }

    if (x0 < _dirtyX0) { _dirtyX0 = static_cast<int16_t>(x0); }
    if (y0 < _dirtyY0) { _dirtyY0 = static_cast<int16_t>(y0); }
    if (x1 > _dirtyX1) { _dirtyX1 = static_cast<int16_t>(x1); }
    if (y1 > _dirtyY1) { _dirtyY1 = static_cast<int16_t>(y1); }
}

void BBOLED176x176::markAllDirty()
{
    _dirtyX0 = 0;
    _dirtyY0 = 0;
    _dirtyX1 = static_cast<int16_t>(Width - 1);
    _dirtyY1 = static_cast<int16_t>(Height - 1);
    _dirty   = true;
}

bool BBOLED176x176::isDirty() const
{
    return _dirty;
}

bool BBOLED176x176::showDirty()
{
    if (!_dirty)
    {
        return true;
    }

    if (!isInitialized())
    {
        return false;
    }

    const bool ok = pushRegion(
        static_cast<uint8_t>(_dirtyX0),
        static_cast<uint8_t>(_dirtyY0),
        static_cast<uint8_t>(_dirtyX1),
        static_cast<uint8_t>(_dirtyY1));

    if (ok)
    {
        clearDirty();
    }

    return ok;
}

void BBOLED176x176::clearDirty()
{
    _dirtyX0 = 0;
    _dirtyY0 = 0;
    _dirtyX1 = 0;
    _dirtyY1 = 0;
    _dirty   = false;
}

// ============================================================================
//  Panel control
// ============================================================================

bool BBOLED176x176::displayOn()
{
    return _controller.displayOn();
}

bool BBOLED176x176::displayOff()
{
    return _controller.displayOff();
}

bool BBOLED176x176::setInvert(bool invert)
{
    return _controller.setInvert(invert);
}

bool BBOLED176x176::setContrast(uint8_t value)
{
    return _controller.setContrast(value);
}

bool BBOLED176x176::setContrastRGB(uint8_t a, uint8_t b, uint8_t c)
{
    return _controller.setContrastRGB(a, b, c);
}

bool BBOLED176x176::setBrightness(uint8_t sixteenths)
{
    return _controller.setMasterContrast(sixteenths);
}

// ============================================================================
//  Transfer tuning
// ============================================================================

void BBOLED176x176::setChunkPixels(uint16_t pixels)
{
    _controller.setChunkPixels(pixels);
}

uint16_t BBOLED176x176::chunkPixels() const
{
    return _controller.chunkPixels();
}

BBSSD1333& BBOLED176x176::controller()
{
    return _controller;
}

} // namespace blackblox
