#include "BBSL030.h"

#include <string.h>

namespace blackblox
{

BBSL030::BBSL030(TwoWire& wire, uint8_t address)
    : _wire(wire),
      _address(address),
      _uid{},
      _uidLength(0),
      _tagType(0),
      _status(NoStatus),
      _error(BBSL030Error::NotInitialized),
      _initialized(false),
      _present(false),
      _waiting(false),
      _noTagCount(0),
      _removalThreshold(3),
      _scanIntervalMs(150),
      _firstReadDelayMs(20),
      _retryIntervalMs(5),
      _timeoutMs(150),
      _lastScanAt(0),
      _sentAt(0),
      _lastReadAt(0)
{
}

bool BBSL030::isConnected()
{
    _wire.beginTransmission(_address);
    return _wire.endTransmission() == 0;
}

bool BBSL030::begin()
{
    _initialized = false;
    _waiting = false;
    _present = false;
    _noTagCount = 0;
    _uidLength = 0;
    _tagType = 0;
    _status = NoStatus;
    memset(_uid, 0, sizeof(_uid));

    if (_address < 0x50 || _address > 0x53)
    {
        _error = BBSL030Error::InvalidAddress;
        return false;
    }

    if (!isConnected())
    {
        _error = BBSL030Error::DeviceNotFound;
        return false;
    }

    _initialized = true;
    _error = BBSL030Error::None;
    _lastScanAt = millis() - _scanIntervalMs; // Scan on the first poll().
    return true;
}

void BBSL030::setScanInterval(uint16_t ms)
{
    _scanIntervalMs = ms == 0 ? 1 : ms;
}

void BBSL030::setRemovalThreshold(uint8_t count)
{
    _removalThreshold = count == 0 ? 1 : count;
}

bool BBSL030::setReplyTiming(uint16_t firstReadDelayMs,
                            uint16_t retryIntervalMs,
                            uint16_t timeoutMs)
{
    if (retryIntervalMs == 0 || timeoutMs <= firstReadDelayMs)
        return false;

    _firstReadDelayMs = firstReadDelayMs;
    _retryIntervalMs = retryIntervalMs;
    _timeoutMs = timeoutMs;
    return true;
}

BBSL030Event BBSL030::poll()
{
    if (!_initialized)
    {
        // Keep a more useful begin() failure such as DeviceNotFound.
        if (_error == BBSL030Error::None)
            _error = BBSL030Error::NotInitialized;
        return BBSL030Event::None;
    }

    const uint32_t now = millis();

    if (_waiting)
    {
        if (static_cast<uint32_t>(now - _sentAt) >= _timeoutMs)
        {
            _waiting = false;
            _noTagCount = 0; // A transport fault is not a card removal.
            _error = BBSL030Error::Timeout;
            return BBSL030Event::None;
        }

        if (static_cast<uint32_t>(now - _sentAt) < _firstReadDelayMs ||
            static_cast<uint32_t>(now - _lastReadAt) < _retryIntervalMs)
            return BBSL030Event::None;

        _lastReadAt = now;
        return readReply();
    }

    if (static_cast<uint32_t>(now - _lastScanAt) < _scanIntervalMs)
        return BBSL030Event::None;

    _lastScanAt = now;
    _wire.beginTransmission(_address);
    const bool written = _wire.write(static_cast<uint8_t>(1)) == 1 &&
                         _wire.write(SelectCommand) == 1;
    const uint8_t result = _wire.endTransmission();
    if (!written || result != 0)
    {
        // An SL030 can NACK while busy; never count this as 'no tag'.
        _error = BBSL030Error::Bus;
        _status = NoStatus;
        _noTagCount = 0;
        return BBSL030Event::None;
    }

    _sentAt = millis();
    _lastReadAt = _sentAt - _retryIntervalMs;
    _status = NoStatus;
    _error = BBSL030Error::None;
    _waiting = true;
    return BBSL030Event::None;
}

BBSL030Event BBSL030::readReply()
{
    uint8_t frame[FrameLength] = {};
    uint8_t received = 0;

    // Wire reads are bounded by the platform I2C timeout. The module may
    // return a short frame (no tag) or pad a response up to FrameLength.
    _wire.requestFrom(_address, FrameLength);
    while (_wire.available())
    {
        const int byte = _wire.read();
        if (byte < 0)
            break;
        if (received < FrameLength)
            frame[received++] = static_cast<uint8_t>(byte);
    }

    if (received == 0)
    {
        _error = BBSL030Error::Bus;
        return BBSL030Event::None; // Busy NACK: retry until timeout.
    }

    if (received < 3 || frame[0] < 2 || frame[0] > FrameLength - 1 ||
        received < static_cast<uint8_t>(frame[0] + 1) ||
        frame[1] != SelectCommand)
    {
        _error = BBSL030Error::InvalidFrame;
        return BBSL030Event::None;
    }

    const uint8_t length = frame[0]; // Command + Status + optional data.
    const uint8_t status = frame[2];
    if (status == 0x00 && length != 7 && length != 10)
    {
        _error = BBSL030Error::InvalidFrame;
        return BBSL030Event::None;
    }
    if (status == 0x01 && length != 2)
    {
        _error = BBSL030Error::InvalidFrame;
        return BBSL030Event::None;
    }

    _waiting = false;
    _status = status;
    _error = BBSL030Error::None;

    if (status == 0x01)
        return sawNoTag();

    if (status != 0x00)
    {
        _noTagCount = 0;
        _error = BBSL030Error::DeviceStatus; // E.g. 0x0A: collision.
        return BBSL030Event::None;
    }

    // Select reply: [Len][0x01][0x00][UID (4/7 bytes)][Type].
    const uint8_t uidLength = static_cast<uint8_t>(length - 3);
    const uint8_t type = frame[3 + uidLength];
    const bool changed = !_present || uidLength != _uidLength ||
                         memcmp(_uid, frame + 3, uidLength) != 0 ||
                         type != _tagType;

    memcpy(_uid, frame + 3, uidLength);
    _uidLength = uidLength;
    _tagType = type;
    _present = true;
    _noTagCount = 0;
    return changed ? BBSL030Event::Card : BBSL030Event::None;
}

BBSL030Event BBSL030::sawNoTag()
{
    if (!_present)
    {
        _noTagCount = 0;
        return BBSL030Event::None;
    }

    if (++_noTagCount < _removalThreshold)
        return BBSL030Event::None;

    _noTagCount = 0;
    _present = false;
    return BBSL030Event::Removed;
}

} // namespace blackblox
