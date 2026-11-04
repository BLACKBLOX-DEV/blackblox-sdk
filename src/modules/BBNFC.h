#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "../drivers/BBSL030.h"

namespace blackblox
{

struct BBNFCCard
{
    uint8_t uid[BBSL030::MaxUidLength] = {};
    uint8_t uidLength = 0;
    uint8_t tagType = 0;      // Raw SL030 type; mapping depends on firmware.
    uint32_t firstSeenAtMs = 0;
};

// Application-facing NFC module. It provides a card snapshot and printable UID
// on top of the SL030's event-driven I2C driver. No access-control policy is
// implemented: UID values can be cloned and must not authenticate a user.
class BBNFC
{
public:
    explicit BBNFC(TwoWire& wire = Wire,
                        uint8_t address = BBSL030::DefaultAddress);

    // The application calls BB.begin(sda, scl) once before begin().
    bool begin();
    bool isConnected() { return _reader.isConnected(); }

    // Call from loop(). Card is emitted on presentation/change; Removed
    // follows the configured number of valid no-tag replies.
    BBSL030Event poll();
    bool cardPresent() const { return _reader.cardPresent(); }

    // Returns false when no card is currently confirmed in the field.
    bool card(BBNFCCard& out) const;
    // Remembers the most recently seen card, including after removal.
    bool lastCard(BBNFCCard& out) const;
    const char* lastUidString() const { return _uidText; } // "AA:BB:CC:DD"

    BBSL030Error lastError() const { return _reader.lastError(); }
    uint8_t lastStatus() const { return _reader.lastStatus(); }

    void setScanInterval(uint16_t ms) { _reader.setScanInterval(ms); }
    void setRemovalThreshold(uint8_t count)
    {
        _reader.setRemovalThreshold(count);
    }
    bool setReplyTiming(uint16_t delayMs, uint16_t retryMs, uint16_t timeoutMs)
    {
        return _reader.setReplyTiming(delayMs, retryMs, timeoutMs);
    }

    BBSL030& driver() { return _reader; }
    const BBSL030& driver() const { return _reader; }

private:
    void cacheCard();

    BBSL030 _reader;
    BBNFCCard _lastCard;
    bool _hasLastCard;
    char _uidText[BBSL030::MaxUidLength * 3];
};

} // namespace blackblox
