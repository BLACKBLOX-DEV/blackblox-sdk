#pragma once

#include <stdint.h>

#include "../display/BBMatrixDisplay.h"
#include "fonts/BBFont.h"

namespace blackblox
{

class BBScroller
{
public:
    static constexpr uint16_t MaxTextLength = 96;

    explicit BBScroller(
        BBMatrixDisplay& display);

    bool start(
        const char* text,
        int16_t y,
        const BBFont& font,
        BBColor color,
        uint32_t stepDurationMs = 70);

    bool update();

    void stop(
        bool clearDisplay = false);

    bool isRunning() const;

    bool isFinished() const;

    int16_t getX() const;

    int16_t getTextWidth() const;

private:
    BBMatrixDisplay& _display;

    char _text[MaxTextLength + 1];

    const BBFont* _font;

    BBColor _color;

    int16_t _x;
    int16_t _y;
    int16_t _textWidth;

    uint32_t _stepDurationMs;
    uint32_t _lastStepTime;

    bool _running;
    bool _finished;


    void renderFrame();
};

}