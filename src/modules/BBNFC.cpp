#include "BBNFC.h"

#include <string.h>

namespace blackblox
{

BBNFC::BBNFC(TwoWire& wire, uint8_t address)
    : _reader(wire, address),
      _lastCard{},
      _hasLastCard(false),
      _uidText{}
{
}

bool BBNFC::begin()
{
    _lastCard = BBNFCCard{};
    _hasLastCard = false;
    _uidText[0] = '\0';
    return _reader.begin();
}

BBSL030Event BBNFC::poll()
{
    const BBSL030Event event = _reader.poll();
    if (event == BBSL030Event::Card)
        cacheCard();
    return event;
}

bool BBNFC::card(BBNFCCard& out) const
{
    if (!_reader.cardPresent() || !_hasLastCard)
        return false;

    out = _lastCard;
    return true;
}

bool BBNFC::lastCard(BBNFCCard& out) const
{
    if (!_hasLastCard)
        return false;

    out = _lastCard;
    return true;
}

void BBNFC::cacheCard()
{
    _lastCard.uidLength = _reader.uidLength();
    _lastCard.tagType = _reader.tagType();
    _lastCard.firstSeenAtMs = millis();
    memcpy(_lastCard.uid, _reader.uidBytes(), _lastCard.uidLength);
    _hasLastCard = true;

    static const char digits[] = "0123456789ABCDEF";
    uint8_t pos = 0;
    for (uint8_t i = 0; i < _lastCard.uidLength; ++i)
    {
        if (i != 0)
            _uidText[pos++] = ':';
        _uidText[pos++] = digits[_lastCard.uid[i] >> 4];
        _uidText[pos++] = digits[_lastCard.uid[i] & 0x0F];
    }
    _uidText[pos] = '\0';
}

} // namespace blackblox
