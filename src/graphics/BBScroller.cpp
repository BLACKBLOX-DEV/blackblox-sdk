#include "BBScroller.h"

#include <Arduino.h>
#include <string.h>

namespace blackblox
{

BBScroller::BBScroller(
    BBMatrixDisplay& display)
    : _display(display),
      _font(nullptr),
      _color(),
      _x(0),
      _y(0),
      _textWidth(0),
      _stepDurationMs(70),
      _lastStepTime(0),
      _running(false),
      _finished(false)
{
    _text[0] = '\0';
}

bool BBScroller::start(
    const char* text,
    int16_t y,
    const BBFont& font,
    BBColor color,
    uint32_t stepDurationMs)
{
    if (text == nullptr ||
        text[0] == '\0')
    {
        return false;
    }

    if (stepDurationMs == 0)
    {
        return false;
    }

    const size_t textLength =
        strlen(text);

    if (textLength > MaxTextLength)
    {
        return false;
    }

    memcpy(
        _text,
        text,
        textLength + 1);

    _font = &font;
    _color = color;
    _y = y;

    _textWidth =
        _display.getTextWidth(
            _text,
            font);

    if (_textWidth <= 0)
    {
        return false;
    }

    _x =
        static_cast<int16_t>(
            _display.getWidth());

    _stepDurationMs =
        stepDurationMs;

    // Prvi klic update() lahko okvir nariše takoj.
    _lastStepTime =
        millis() - _stepDurationMs;

    _running = true;
    _finished = false;

    return true;
}

bool BBScroller::update()
{
    if (!_running ||
        _font == nullptr)
    {
        return false;
    }

    const uint32_t currentTime =
        millis();

    if (currentTime - _lastStepTime <
        _stepDurationMs)
    {
        return false;
    }

    _lastStepTime =
        currentTime;

    renderFrame();

    // Pri x == -textWidth je napis že popolnoma
    // zapustil zaslon. Izrisani okvir zaslon počisti.
    if (_x <= -_textWidth)
    {
        _running = false;
        _finished = true;

        return true;
    }

    --_x;

    return false;
}

void BBScroller::stop(
    bool clearDisplay)
{
    _running = false;
    _finished = true;

    if (clearDisplay)
    {
        _display.clear();
        _display.show();
    }
}

bool BBScroller::isRunning() const
{
    return _running;
}

bool BBScroller::isFinished() const
{
    return _finished;
}

int16_t BBScroller::getX() const
{
    return _x;
}

int16_t BBScroller::getTextWidth() const
{
    return _textWidth;
}

void BBScroller::renderFrame()
{
    _display.clear();

    _display.drawText(
        _x,
        _y,
        _text,
        *_font,
        _color);

    _display.show();
}

}