#pragma once

#include <stdint.h>

#include "../graphics/BBGraphics.h"
#include "../modules/BBRGBMatrix8x16.h"

namespace blackblox
{

enum class BBMatrixRotation : uint8_t
{
    R0,
    R90,
    R180,
    R270
};

class BBMatrixDisplay : public BBGraphics
{
public:
    static constexpr uint8_t MaxMatrices = 16;

    BBMatrixDisplay(
        uint16_t width,
        uint16_t height);

    bool attach(
        BBRGBMatrix8x16& matrix,
        int16_t x,
        int16_t y,
        BBMatrixRotation rotation = BBMatrixRotation::R0);

    uint8_t matrixCount() const;

    bool show() override;

private:
    struct MatrixSlot
    {
        BBRGBMatrix8x16* matrix;
        int16_t x;
        int16_t y;
        BBMatrixRotation rotation;
    };

    MatrixSlot _matrices[MaxMatrices];
    uint8_t _matrixCount;

    uint8_t logicalWidth(
        BBMatrixRotation rotation) const;

    uint8_t logicalHeight(
        BBMatrixRotation rotation) const;

    void mapPixel(
        uint8_t logicalX,
        uint8_t logicalY,
        BBMatrixRotation rotation,
        uint8_t& physicalX,
        uint8_t& physicalY) const;
};

}