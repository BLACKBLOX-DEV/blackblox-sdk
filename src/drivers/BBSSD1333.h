#pragma once

// ============================================================================
//  BBSSD1333 - Low-level driver for the Solomon Systech SSD1333 OLED
//              controller (176 RGB x 176, 65k color) over I2C.
//
//  This class knows the silicon and nothing else. It has no framebuffer,
//  no drawing primitives, no fonts and no knowledge of BLACKBLOX modules.
//  Use BBOLED176x176 for the application-facing API.
//
//  Verified against: SSD1333 Rev 1.2 (May 2018) + SSD1333 Command Table
//                    Rev 1.0 (Feb 2018), Solomon Systech.
//
//  Bus ownership: this driver never calls Wire.begin(). The application
//  initializes the bus once via BB.begin(sda, scl).
// ============================================================================

#include <Arduino.h>
#include <Wire.h>

#include <stdint.h>

namespace blackblox
{

enum class BBSSD1333Status : uint8_t
{
    Ok = 0,
    NotInitialized,     ///< begin() has not completed successfully
    ArgumentError,      ///< null pointer, zero size, or inverted window
    BufferOverflow,     ///< chunk larger than the TwoWire TX buffer
    NackAddress,        ///< no ACK on the address phase (wiring / address)
    NackData,           ///< no ACK mid-transfer (connection lost)
    Timeout,            ///< bus timeout
    BusError            ///< any other Wire error
};

class BBSSD1333
{
public:
    // ------------------------------------------------------------------
    // Panel geometry. Fixed by the controller.
    // ------------------------------------------------------------------
    static constexpr uint8_t Width  = 176;
    static constexpr uint8_t Height = 176;

    // ------------------------------------------------------------------
    // I2C addresses. Datasheet 6.1.5: the slave address is 0111100b or
    // 0111101b, selected by the SA0 pin (which is the D/C# pin in I2C
    // mode). There are only these two options and the choice is physical.
    // ------------------------------------------------------------------
    static constexpr uint8_t AddressSA0Low  = 0x3C;
    static constexpr uint8_t AddressSA0High = 0x3D;
    static constexpr uint8_t DefaultAddress = AddressSA0Low;

    // ------------------------------------------------------------------
    // Pixels per I2C transaction.
    //
    // Each transaction is 1 control byte + 2 bytes per pixel, so the
    // transaction length is (1 + 2 * chunkPixels) and must fit inside the
    // TwoWire TX buffer.
    //
    // The default of 15 gives 31 bytes, which fits the 32-byte AVR buffer
    // and is therefore safe on every core. On ESP32 the buffer is larger
    // (BB.begin() raises it to 512), so raise this with setChunkPixels()
    // for a large speed gain - see the header notes in BBOLED176x176.h.
    // ------------------------------------------------------------------
    // MaxChunkPixels bounds any staging buffer a caller needs to size at
    // compile time; setChunkPixels() clamps to this range.
    static constexpr uint16_t DefaultChunkPixels = 15;
    static constexpr uint16_t MinChunkPixels     = 1;
    static constexpr uint16_t MaxChunkPixels     = 256;

    explicit BBSSD1333(
        TwoWire& wire = Wire,
        uint8_t address = DefaultAddress,
        int8_t resetPin = -1);

    // ------------------------------------------------------------------
    // Lifecycle
    // ------------------------------------------------------------------

    /// Resets the controller, runs the initialization sequence and leaves
    /// the panel in sleep mode with the display OFF. The caller is
    /// expected to clear GDDRAM before calling displayOn(), otherwise the
    /// power-on RAM contents (undefined) become visible.
    /// Does NOT call Wire.begin().
    bool begin();

    /// True when begin() completed successfully.
    bool isInitialized() const;

    /// Address-only probe. Safe to call before begin().
    bool isConnected();

    /// Status of the most recent operation.
    BBSSD1333Status lastStatus() const;

    /// Human-readable form of a status code. Returns a static string.
    static const char* statusString(BBSSD1333Status status);

    /// Hardware reset pulse. No-op when no reset pin was configured.
    /// Follows the datasheet power-on sequence (section 6.9).
    void reset();

    // ------------------------------------------------------------------
    // Display control
    // ------------------------------------------------------------------
    bool displayOn();
    bool displayOff();

    /// Normal (false) or inverted (true) display. Command A6h / A7h.
    bool setInvert(bool invert);

    /// Forces every pixel to GS0 (blank) without touching GDDRAM.
    /// Command A4h. Pass false to return to normal display (A6h).
    bool setBlank(bool blank);

    /// Equal contrast on all three color channels. Command C1h.
    bool setContrast(uint8_t value);

    /// Per-channel contrast for white balance. Command C1h.
    /// Note the arguments map to the controller's colors A, B and C,
    /// which are only "red, green, blue" if the panel is wired that way
    /// and the color-order bit in the remap value matches.
    bool setContrastRGB(uint8_t a, uint8_t b, uint8_t c);

    /// Master current scaling, 0..15 -> 1/16..16/16. Command C7h.
    /// Values above 15 are rejected.
    bool setMasterContrast(uint8_t sixteenths);

    /// Overrides the remap / color-depth byte (command A0h).
    /// See DefaultRemap for the meaning of each bit. Panel-specific.
    /// Must be called after begin(); takes effect immediately.
    bool setRemap(uint8_t value);

    // ------------------------------------------------------------------
    // GDDRAM access
    // ------------------------------------------------------------------

    /// Sets the active rectangle and arms GDDRAM for writing (5Ch).
    /// Coordinates are inclusive. Returns false on an inverted or
    /// out-of-range window - it does not silently clamp, because a
    /// clamped window silently desynchronises the caller's pixel stream.
    bool setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

    /// Streams raw RGB565 bytes (big-endian, high byte first) into the
    /// armed window. byteCount must be even.
    bool writePixels(const uint8_t* data, uint32_t byteCount);

    /// Writes the same RGB565 value pixelCount times into the armed window.
    bool fillWindow(uint16_t color565, uint32_t pixelCount);

    /// Convenience: arms the full screen and fills it. Slow - see the
    /// timing note in BBOLED176x176.h.
    bool fillScreen(uint16_t color565);

    // ------------------------------------------------------------------
    // Transfer tuning
    // ------------------------------------------------------------------
    void setChunkPixels(uint16_t pixels);
    uint16_t chunkPixels() const;

    // ------------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------------

    /// 8:8:8 -> RGB565. Truncates; no dithering.
    static constexpr uint16_t toRgb565(uint8_t r, uint8_t g, uint8_t b)
    {
        return static_cast<uint16_t>(
            (static_cast<uint16_t>(r & 0xF8) << 8) |
            (static_cast<uint16_t>(g & 0xFC) << 3) |
            static_cast<uint16_t>(b >> 3));
    }

    // ------------------------------------------------------------------
    // Default remap value for command A0h (see datasheet 1.5).
    //
    //   0x74 = 0b0111_0100
    //     A[0] = 0  horizontal address increment  <- required by the
    //               row-major streaming in BBOLED176x176; do not change
    //     A[1] = 0  column 0 -> SEG0
    //     A[2] = 1  color sequence swapped, C -> B -> A
    //     A[3] = 0  reserved
    //     A[4] = 1  COM scan from COM[N-1] to COM0
    //     A[5] = 1  COM split odd/even enabled (reset default)
    //     A[7:6] = 01  65k color                 <- required
    //
    // A[2] = 1 is what makes a normally-wired panel interpret standard
    // RGB565 correctly: in 8-bit 65k mode the first byte's high bits land
    // in color C and the second byte's low bits in color A (datasheet
    // Table 6-7), so without the swap red and blue come out exchanged.
    //
    // A[1], A[4] and A[5] are panel-orientation bits. If the image is
    // mirrored or upside down, change them here or via setRemap() rather
    // than transposing the framebuffer.
    // ------------------------------------------------------------------
    static constexpr uint8_t DefaultRemap = 0x74;

private:
    // Wire.endTransmission() code -> BBSSD1333Status
    BBSSD1333Status mapWireError(uint8_t code) const;

    bool pushByte(uint8_t value);

    bool writeCommand(uint8_t command);
    bool writeCommand(uint8_t command, const uint8_t* params, uint8_t count);
    bool writeParams(const uint8_t* params, uint8_t count);

    bool runInitSequence();

    TwoWire&        _wire;
    uint8_t         _address;
    int8_t          _resetPin;
    bool            _initialized;
    uint16_t        _chunkPixels;
    BBSSD1333Status _lastStatus;
};

} // namespace blackblox
