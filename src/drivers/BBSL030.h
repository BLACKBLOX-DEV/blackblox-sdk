#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

enum class BBSL030Event : uint8_t
{
    None,
    Card,       // First card, or a different card while one is present.
    Removed
};

enum class BBSL030Error : uint8_t
{
    None,
    InvalidAddress,
    NotInitialized,
    DeviceNotFound,
    Bus,
    InvalidFrame,
    Timeout,
    DeviceStatus
};

// StrongLink SL030 I2C reader, select-card command only. The caller owns the
// I2C bus: initialize it once with BB.begin(sda, scl) before begin().
// poll() uses no delay(), but each Wire transaction can still wait briefly.
class BBSL030
{
public:
    static constexpr uint8_t DefaultAddress = 0x50; // JP1/JP2: 0x50..0x53
    static constexpr uint8_t MaxUidLength = 7;
    static constexpr uint8_t NoStatus = 0xFF;

    explicit BBSL030(TwoWire& wire = Wire,
                     uint8_t address = DefaultAddress);

    // An address ACK verifies the reader is reachable. No bus initialization.
    bool begin();
    bool isConnected(); // May return false while the SL030 is busy with a card.

    // Call frequently from loop(). A command is sent on one call and its
    // response is read on later calls. None means no card-state change.
    BBSL030Event poll();

    bool cardPresent() const { return _present; }
    // UID and tag type retain the last card after a Removed event. Check
    // cardPresent() when current presence matters. The UID is not a credential.
    const uint8_t* uidBytes() const { return _uid; }
    uint8_t uidLength() const { return _uidLength; }
    uint8_t tagType() const { return _tagType; } // Raw firmware-specific value.

    BBSL030Error lastError() const { return _error; }
    // Valid response status, or NoStatus while a reply is pending/invalid.
    uint8_t lastStatus() const { return _status; }

    void setScanInterval(uint16_t ms); // Default 150 ms, minimum 1 ms.
    void setRemovalThreshold(uint8_t count); // Default 3 valid no-tag replies.

    // Defaults: first read after 20 ms, retry every 5 ms, timeout at 150 ms.
    // Invalid parameters leave the previous settings unchanged.
    bool setReplyTiming(uint16_t firstReadDelayMs,
                        uint16_t retryIntervalMs,
                        uint16_t timeoutMs);

private:
    static constexpr uint8_t SelectCommand = 0x01;
    static constexpr uint8_t FrameLength = 1 + 1 + 1 + MaxUidLength + 1;

    BBSL030Event readReply();
    BBSL030Event sawNoTag();

    TwoWire& _wire;
    uint8_t _address;
    uint8_t _uid[MaxUidLength];
    uint8_t _uidLength;
    uint8_t _tagType;
    uint8_t _status;
    BBSL030Error _error;
    bool _initialized;
    bool _present;
    bool _waiting;
    uint8_t _noTagCount;
    uint8_t _removalThreshold;
    uint16_t _scanIntervalMs;
    uint16_t _firstReadDelayMs;
    uint16_t _retryIntervalMs;
    uint16_t _timeoutMs;
    uint32_t _lastScanAt;
    uint32_t _sentAt;
    uint32_t _lastReadAt;
};

} // namespace blackblox
