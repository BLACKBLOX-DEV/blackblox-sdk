#include "BBSSD1333.h"

namespace blackblox
{

namespace
{

// ============================================================================
//  SSD1333 command set.
//
//  Every entry below appears in the SSD1333 command table (Rev 1.0,
//  Feb 2018). Commands from the related SSD1351 that the SSD1333 does NOT
//  implement - notably ABh (Function Selection) and B4h (Set VSL) - are
//  deliberately absent. Sending them puts the following parameter bytes
//  into GDDRAM instead of a command register.
// ============================================================================

constexpr uint8_t CmdSetColumn        = 0x15; // 2 params: start, end
constexpr uint8_t CmdSetRow           = 0x75; // 2 params: start, end
constexpr uint8_t CmdWriteRam         = 0x5C; // 0 params
constexpr uint8_t CmdSetRemap         = 0xA0; // 1 param
constexpr uint8_t CmdSetStartLine     = 0xA1; // 1 param
constexpr uint8_t CmdSetOffset        = 0xA2; // 1 param
constexpr uint8_t CmdDisplayAllOff    = 0xA4; // 0 params (force GS0)
constexpr uint8_t CmdDisplayNormal    = 0xA6; // 0 params
constexpr uint8_t CmdDisplayInverse   = 0xA7; // 0 params
constexpr uint8_t CmdSleepOn          = 0xAE; // 0 params (display off)
constexpr uint8_t CmdSleepOff         = 0xAF; // 0 params (display on)
constexpr uint8_t CmdSetPhaseLength   = 0xB1; // 1 param
constexpr uint8_t CmdSetClockDiv      = 0xB3; // 1 param
constexpr uint8_t CmdSetPrecharge2    = 0xB6; // 1 param
constexpr uint8_t CmdLinearLut        = 0xB9; // 0 params
constexpr uint8_t CmdSetPrechargeV    = 0xBB; // 1 param
constexpr uint8_t CmdSetVcomh         = 0xBE; // 1 param
constexpr uint8_t CmdSetContrast      = 0xC1; // 3 params: A, B, C
constexpr uint8_t CmdMasterContrast   = 0xC7; // 1 param
constexpr uint8_t CmdSetMuxRatio      = 0xCA; // 1 param
constexpr uint8_t CmdCommandLock      = 0xFD; // 1 param

// I2C control bytes. Datasheet 6.1.5.2: Co = 0, D/C# selects command or
// data. With Co = 0 every byte after the control byte in the same
// transaction is of that type, so commands and their parameters travel in
// separate transactions.
constexpr uint8_t ControlCommand = 0x00;
constexpr uint8_t ControlData    = 0x40;

// ----------------------------------------------------------------------------
// Initialization script: { command, parameter count, parameters... }
//
// Values marked PANEL are electrical characteristics of the glass, not the
// controller. Confirm them against the OLED module datasheet; the values
// here are the controller reset defaults wherever a safe default exists.
// ----------------------------------------------------------------------------
const uint8_t InitScript[] =
{
    CmdCommandLock,     1, 0x12,        // unlock the MCU interface
    CmdSleepOn,         0,              // display off while configuring

    CmdSetMuxRatio,     1, 0xAF,        // 175 -> 176 MUX (reset default)
    CmdSetRemap,        1, BBSSD1333::DefaultRemap,
    CmdSetStartLine,    1, 0x00,
    CmdSetOffset,       1, 0x00,

    // B3h: A[7:4] oscillator frequency, A[3:0] divide ratio.
    // 0xF0 = max frequency, divide by 1. (0xF1 would be divide by 2.)
    // With phase lengths below this gives roughly 100 Hz frame rate:
    //   Fosc 3.12 MHz / (1 * (4 + 28 + 145) * 176).
    CmdSetClockDiv,     1, 0xF0,

    // B1h: A[3:0] phase 1 = 2 -> 4 DCLKs, A[7:4] phase 2 = 14 -> 28 DCLKs.
    CmdSetPhaseLength,  1, 0xE2,        // PANEL

    CmdSetPrechargeV,   1, 0x17,        // 0.40 * VCC (reset default) PANEL
    CmdSetPrecharge2,   1, 0x08,        // 8 DCLKs (reset default)     PANEL
    CmdSetVcomh,        1, 0x05,        // 0.82 * VCC (reset default)  PANEL

    CmdSetContrast,     3, 0x8A, 0x51, 0x8A, // white balance          PANEL
    CmdMasterContrast,  1, 0x0F,        // 16/16, no reduction

    CmdLinearLut,       0,              // built-in linear gray scale
    CmdDisplayNormal,   0
};

constexpr uint16_t InitScriptLength =
    static_cast<uint16_t>(sizeof(InitScript) / sizeof(InitScript[0]));

// Datasheet 6.9: after VDD is stable wait at least 20 ms before asserting
// RES#, hold RES# low for at least 3 us, and allow 100 ms (tAF) after AFh
// before SEG/COM are driven.
constexpr uint16_t ResetSettleMs   = 20;
constexpr uint16_t ResetPulseMs    = 1;
constexpr uint16_t ResetRecoveryMs = 10;
constexpr uint16_t DisplayOnMs     = 100;

} // namespace

// ============================================================================
//  Construction
// ============================================================================

BBSSD1333::BBSSD1333(
    TwoWire& wire,
    uint8_t address,
    int8_t resetPin)
    : _wire(wire),
      _address(address),
      _resetPin(resetPin),
      _initialized(false),
      _chunkPixels(DefaultChunkPixels),
      _lastStatus(BBSSD1333Status::NotInitialized)
{
}

// ============================================================================
//  Status
// ============================================================================

BBSSD1333Status BBSSD1333::lastStatus() const
{
    return _lastStatus;
}

bool BBSSD1333::isInitialized() const
{
    return _initialized;
}

const char* BBSSD1333::statusString(BBSSD1333Status status)
{
    switch (status)
    {
        case BBSSD1333Status::Ok:             return "OK";
        case BBSSD1333Status::NotInitialized: return "begin() not completed";
        case BBSSD1333Status::ArgumentError:  return "Invalid argument";
        case BBSSD1333Status::BufferOverflow: return "Chunk exceeds Wire TX buffer";
        case BBSSD1333Status::NackAddress:    return "NACK on address (wiring, address, pull-ups)";
        case BBSSD1333Status::NackData:       return "NACK on data (connection lost)";
        case BBSSD1333Status::Timeout:        return "I2C timeout";
        case BBSSD1333Status::BusError:       return "I2C bus error";
    }

    return "Unknown status";
}

// Arduino TwoWire::endTransmission() codes:
//   0 success, 1 data too long for buffer, 2 NACK on address,
//   3 NACK on data, 4 other error, 5 timeout.
BBSSD1333Status BBSSD1333::mapWireError(uint8_t code) const
{
    switch (code)
    {
        case 0:  return BBSSD1333Status::Ok;
        case 1:  return BBSSD1333Status::BufferOverflow;
        case 2:  return BBSSD1333Status::NackAddress;
        case 3:  return BBSSD1333Status::NackData;
        case 5:  return BBSSD1333Status::Timeout;
        default: return BBSSD1333Status::BusError;
    }
}

// ============================================================================
//  Transport
// ============================================================================

// TwoWire::write() returns 0 when the TX buffer is full. Several Arduino
// cores (the AVR Wire among them) then let endTransmission() report
// success anyway, so an oversized transaction is silently truncated and
// the image is corrupted with no error. Checking every write() return is
// the only portable way to catch that.
bool BBSSD1333::pushByte(uint8_t value)
{
    return _wire.write(value) == 1;
}

bool BBSSD1333::writeCommand(uint8_t command)
{
    _wire.beginTransmission(_address);

    if (!pushByte(ControlCommand) || !pushByte(command))
    {
        _wire.endTransmission();
        _lastStatus = BBSSD1333Status::BufferOverflow;
        return false;
    }

    _lastStatus = mapWireError(_wire.endTransmission());

    return _lastStatus == BBSSD1333Status::Ok;
}

bool BBSSD1333::writeParams(const uint8_t* params, uint8_t count)
{
    if (count == 0)
    {
        _lastStatus = BBSSD1333Status::Ok;
        return true;
    }

    if (params == nullptr)
    {
        _lastStatus = BBSSD1333Status::ArgumentError;
        return false;
    }

    _wire.beginTransmission(_address);

    if (!pushByte(ControlData))
    {
        _wire.endTransmission();
        _lastStatus = BBSSD1333Status::BufferOverflow;
        return false;
    }

    for (uint8_t i = 0; i < count; ++i)
    {
        if (!pushByte(params[i]))
        {
            _wire.endTransmission();
            _lastStatus = BBSSD1333Status::BufferOverflow;
            return false;
        }
    }

    _lastStatus = mapWireError(_wire.endTransmission());

    return _lastStatus == BBSSD1333Status::Ok;
}

bool BBSSD1333::writeCommand(
    uint8_t command,
    const uint8_t* params,
    uint8_t count)
{
    if (!writeCommand(command))
    {
        return false;
    }

    return writeParams(params, count);
}

// ============================================================================
//  Reset and initialization
// ============================================================================

void BBSSD1333::reset()
{
    if (_resetPin < 0)
    {
        return;
    }

    // Drive the pin high before switching it to an output, so the panel
    // never sees a spurious low glitch from the default output register.
    digitalWrite(_resetPin, HIGH);
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, HIGH);

    delay(ResetSettleMs);               // t0: >= 20 ms after VDD is stable

    digitalWrite(_resetPin, LOW);
    delay(ResetPulseMs);                // t1: >= 3 us, 1 ms is generous

    digitalWrite(_resetPin, HIGH);
    delay(ResetRecoveryMs);
}

bool BBSSD1333::runInitSequence()
{
    uint16_t index = 0;

    while (index < InitScriptLength)
    {
        const uint8_t command = InitScript[index++];
        const uint8_t count   = InitScript[index++];

        if (!writeCommand(command))
        {
            return false;
        }

        if (count > 0)
        {
            if (!writeParams(&InitScript[index], count))
            {
                return false;
            }

            index = static_cast<uint16_t>(index + count);
        }
    }

    return true;
}

bool BBSSD1333::begin()
{
    _initialized = false;

    reset();

    if (!isConnected())
    {
        // isConnected() has already set _lastStatus.
        return false;
    }

    if (!runInitSequence())
    {
        return false;
    }

    // The controller is configured but still in sleep mode. The caller
    // clears GDDRAM and then calls displayOn(), which avoids showing the
    // undefined power-on RAM contents.
    _initialized = true;
    _lastStatus  = BBSSD1333Status::Ok;

    return true;
}

bool BBSSD1333::isConnected()
{
    _wire.beginTransmission(_address);
    _lastStatus = mapWireError(_wire.endTransmission());

    return _lastStatus == BBSSD1333Status::Ok;
}

// ============================================================================
//  Display control
// ============================================================================

bool BBSSD1333::displayOn()
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    if (!writeCommand(CmdSleepOff))
    {
        return false;
    }

    delay(DisplayOnMs);                 // tAF

    return true;
}

bool BBSSD1333::displayOff()
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    return writeCommand(CmdSleepOn);
}

bool BBSSD1333::setInvert(bool invert)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    return writeCommand(
        invert ? CmdDisplayInverse : CmdDisplayNormal);
}

bool BBSSD1333::setBlank(bool blank)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    return writeCommand(
        blank ? CmdDisplayAllOff : CmdDisplayNormal);
}

bool BBSSD1333::setContrast(uint8_t value)
{
    return setContrastRGB(value, value, value);
}

bool BBSSD1333::setContrastRGB(uint8_t a, uint8_t b, uint8_t c)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    const uint8_t params[3] = { a, b, c };

    return writeCommand(CmdSetContrast, params, 3);
}

bool BBSSD1333::setMasterContrast(uint8_t sixteenths)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    if (sixteenths > 0x0F)
    {
        _lastStatus = BBSSD1333Status::ArgumentError;
        return false;
    }

    return writeCommand(CmdMasterContrast, &sixteenths, 1);
}

bool BBSSD1333::setRemap(uint8_t value)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    return writeCommand(CmdSetRemap, &value, 1);
}

// ============================================================================
//  GDDRAM
// ============================================================================

bool BBSSD1333::setWindow(
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    // Reject rather than clamp. A clamped window silently desynchronises
    // the caller's pixel stream from the controller's address pointer,
    // which produces a diagonally smeared image that is hard to diagnose.
    if (x0 > x1 || y0 > y1 || x1 >= Width || y1 >= Height)
    {
        _lastStatus = BBSSD1333Status::ArgumentError;
        return false;
    }

    const uint8_t columns[2] = { x0, x1 };
    const uint8_t rows[2]    = { y0, y1 };

    if (!writeCommand(CmdSetColumn, columns, 2))
    {
        return false;
    }

    if (!writeCommand(CmdSetRow, rows, 2))
    {
        return false;
    }

    return writeCommand(CmdWriteRam);
}

bool BBSSD1333::writePixels(const uint8_t* data, uint32_t byteCount)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    if (byteCount == 0)
    {
        _lastStatus = BBSSD1333Status::Ok;
        return true;
    }

    if (data == nullptr || (byteCount & 0x01) != 0)
    {
        _lastStatus = BBSSD1333Status::ArgumentError;
        return false;
    }

    const uint32_t chunkBytes =
        static_cast<uint32_t>(_chunkPixels) * 2u;

    uint32_t sent = 0;

    while (sent < byteCount)
    {
        uint32_t batch = byteCount - sent;

        if (batch > chunkBytes)
        {
            batch = chunkBytes;
        }

        _wire.beginTransmission(_address);

        bool fits = pushByte(ControlData);

        for (uint32_t i = 0; fits && i < batch; ++i)
        {
            fits = pushByte(data[sent + i]);
        }

        if (!fits)
        {
            _wire.endTransmission();
            _lastStatus = BBSSD1333Status::BufferOverflow;
            return false;
        }

        _lastStatus = mapWireError(_wire.endTransmission());

        if (_lastStatus != BBSSD1333Status::Ok)
        {
            return false;
        }

        sent += batch;
    }

    return true;
}

bool BBSSD1333::fillWindow(uint16_t color565, uint32_t pixelCount)
{
    if (!_initialized)
    {
        _lastStatus = BBSSD1333Status::NotInitialized;
        return false;
    }

    if (pixelCount == 0)
    {
        _lastStatus = BBSSD1333Status::Ok;
        return true;
    }

    const uint8_t high = static_cast<uint8_t>(color565 >> 8);
    const uint8_t low  = static_cast<uint8_t>(color565 & 0xFF);

    uint32_t remaining = pixelCount;

    while (remaining > 0)
    {
        uint32_t batch = remaining;

        if (batch > _chunkPixels)
        {
            batch = _chunkPixels;
        }

        _wire.beginTransmission(_address);

        bool fits = pushByte(ControlData);

        for (uint32_t i = 0; fits && i < batch; ++i)
        {
            fits = pushByte(high) && pushByte(low);
        }

        if (!fits)
        {
            _wire.endTransmission();
            _lastStatus = BBSSD1333Status::BufferOverflow;
            return false;
        }

        _lastStatus = mapWireError(_wire.endTransmission());

        if (_lastStatus != BBSSD1333Status::Ok)
        {
            return false;
        }

        remaining -= batch;
    }

    return true;
}

bool BBSSD1333::fillScreen(uint16_t color565)
{
    if (!setWindow(0, 0, Width - 1, Height - 1))
    {
        return false;
    }

    return fillWindow(
        color565,
        static_cast<uint32_t>(Width) * Height);
}

// ============================================================================
//  Transfer tuning
// ============================================================================

void BBSSD1333::setChunkPixels(uint16_t pixels)
{
    if (pixels < MinChunkPixels)
    {
        pixels = MinChunkPixels;
    }
    else if (pixels > MaxChunkPixels)
    {
        pixels = MaxChunkPixels;
    }

    _chunkPixels = pixels;
}

uint16_t BBSSD1333::chunkPixels() const
{
    return _chunkPixels;
}

} // namespace blackblox
