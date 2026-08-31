#pragma once

// ============================================================================
//  BBOLED176x176 - BLACKBLOX 176x176 RGB OLED module (SSD1333 controller).
//
//  Follows the same model as BBRGBMatrix8x16: drawing goes into the
//  inherited BBGraphics framebuffer and nothing reaches the panel until
//  show() (or showRegion() / showDirty()) is called.
//
//  ---------------------------------------------------------------------
//  MEMORY
//  ---------------------------------------------------------------------
//  BBGraphics stores one BBColor (3 bytes) per pixel:
//
//      176 * 176 * 3 = 92 928 bytes of heap
//
//  That is a large allocation. On an ESP32-S3 without PSRAM it will
//  usually succeed at startup but may fail once Wi-Fi is running, so
//  construct this object before bringing up the network and always check
//  begin(), which returns false when the framebuffer could not be
//  allocated. isValid() (from BBGraphics) reports the same condition.
//
//  ---------------------------------------------------------------------
//  TRANSFER TIME
//  ---------------------------------------------------------------------
//  A full frame is 176 * 176 * 2 = 61 952 bytes of RGB565. At 400 kHz,
//  9 bits per byte, that is about 1.4 s of bus time before per-transaction
//  overhead - so show() is not something to call in a loop.
//
//  For anything that updates repeatedly, redraw only what changed:
//
//      oled.fillRect(10, 40, 60, 16, BBColor::Black());
//      oled.drawText(10, 40, buffer, BBColor::White());
//      oled.showRegion(10, 40, 60, 16);     // ~30 ms instead of 1.4 s
//
//  or accumulate regions with markDirty() and flush once with showDirty().
//
//  Raising the I2C chunk size helps a lot on ESP32, where BB.begin()
//  enlarges the Wire TX buffer to 512 bytes:
//
//      BB.begin(0, 1);
//      oled.setChunkPixels(240);            // 481 bytes per transaction
//
//  Leave the default (15 pixels, 31 bytes) on cores with a 32-byte
//  Wire buffer.
// ============================================================================

#include <Arduino.h>
#include <Wire.h>

#include <stdint.h>

#include "../graphics/BBGraphics.h"
#include "../drivers/BBSSD1333.h"

namespace blackblox
{

class BBOLED176x176 final : public BBGraphics
{
public:
    static constexpr uint16_t Width  = 176;
    static constexpr uint16_t Height = 176;

    /// The SSD1333 responds to 0x3C (SA0 low) or 0x3D (SA0 high) only.
    /// The choice is made physically by strapping SA0 - see the address
    /// notes in docs/modules/BBOLED176x176.md.
    static constexpr uint8_t AddressSA0Low  = BBSSD1333::AddressSA0Low;
    static constexpr uint8_t AddressSA0High = BBSSD1333::AddressSA0High;
    static constexpr uint8_t DefaultAddress = BBSSD1333::DefaultAddress;

    /// @param wire      Shared I2C bus. This class never calls Wire.begin();
    ///                  the application does that once via BB.begin().
    /// @param address   0x3C or 0x3D.
    /// @param resetPin  GPIO wired to RES#, or -1 when the board handles
    ///                  reset itself.
    explicit BBOLED176x176(
        TwoWire& wire = Wire,
        uint8_t address = DefaultAddress,
        int8_t resetPin = -1);

    // ------------------------------------------------------------------
    // Lifecycle
    // ------------------------------------------------------------------

    /// Initializes the controller, clears the panel and turns it on.
    /// Returns false if the framebuffer could not be allocated, the
    /// module did not respond, or initialization failed.
    ///
    /// Takes roughly 1.5 s at the default 400 kHz because GDDRAM is
    /// cleared before the display is enabled. Call setChunkPixels()
    /// before begin() to shorten that on platforms with a large Wire
    /// buffer.
    bool begin();

    bool isInitialized() const;
    bool isConnected();

    /// Status of the most recent controller operation.
    BBSSD1333Status lastStatus() const;
    static const char* statusString(BBSSD1333Status status);

    // ------------------------------------------------------------------
    // Presenting the framebuffer
    // ------------------------------------------------------------------

    /// Pushes the entire framebuffer. Slow - see the header notes.
    bool show() override;

    /// Pushes one rectangle. The rectangle is clipped to the panel;
    /// a rectangle entirely off-screen or with zero area is a no-op
    /// that returns true.
    bool showRegion(int16_t x, int16_t y, int16_t width, int16_t height);

    /// Adds a rectangle to the pending dirty region (union of all marks).
    void markDirty(int16_t x, int16_t y, int16_t width, int16_t height);

    /// Marks the whole panel dirty.
    void markAllDirty();

    /// True when at least one region is pending.
    bool isDirty() const;

    /// Pushes the accumulated dirty region and clears it. Returns true
    /// when nothing was pending.
    bool showDirty();

    // ------------------------------------------------------------------
    // Panel control (pass-through to the controller)
    // ------------------------------------------------------------------
    bool displayOn();
    bool displayOff();
    bool setInvert(bool invert);
    bool setContrast(uint8_t value);
    bool setContrastRGB(uint8_t a, uint8_t b, uint8_t c);

    /// Master current scaling, 0..15. Useful as a global brightness knob.
    bool setBrightness(uint8_t sixteenths);

    // ------------------------------------------------------------------
    // Transfer tuning
    // ------------------------------------------------------------------
    void setChunkPixels(uint16_t pixels);
    uint16_t chunkPixels() const;

    /// Escape hatch for panel-specific tuning (remap, gamma, raw windows).
    BBSSD1333& controller();

private:
    bool pushRegion(
        uint8_t x0,
        uint8_t y0,
        uint8_t x1,
        uint8_t y1);

    void clearDirty();

    BBSSD1333 _controller;

    // Staging buffer for one I2C chunk of RGB565 bytes. A member rather
    // than a local so a large chunk size cannot spike the stack.
    uint8_t _stage[BBSSD1333::MaxChunkPixels * 2];

    // Pending dirty rectangle, inclusive. Valid only when _dirty is true.
    int16_t _dirtyX0;
    int16_t _dirtyY0;
    int16_t _dirtyX1;
    int16_t _dirtyY1;
    bool    _dirty;
};

} // namespace blackblox
