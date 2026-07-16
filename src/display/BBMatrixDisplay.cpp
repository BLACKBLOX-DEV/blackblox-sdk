#include "BBMatrixDisplay.h"

namespace blackblox
{

BBMatrixDisplay::BBMatrixDisplay(
    uint16_t width,
    uint16_t height)
    : BBGraphics(width, height),
      _matrixCount(0)
{
    for (uint8_t i = 0; i < MaxMatrices; ++i)
    {
        _matrices[i].matrix = nullptr;
        _matrices[i].x = 0;
        _matrices[i].y = 0;
        _matrices[i].rotation = BBMatrixRotation::R0;
    }
}

bool BBMatrixDisplay::attach(
    BBRGBMatrix8x16& matrix,
    int16_t x,
    int16_t y,
    BBMatrixRotation rotation)
{
    if (_matrixCount >= MaxMatrices)
    {
        return false;
    }

    const uint8_t width = logicalWidth(rotation);
    const uint8_t height = logicalHeight(rotation);

    if (x < 0 || y < 0)
    {
        return false;
    }

    if ((x + width) > getWidth() ||
        (y + height) > getHeight())
    {
        return false;
    }

    MatrixSlot& slot = _matrices[_matrixCount];

    slot.matrix = &matrix;
    slot.x = x;
    slot.y = y;
    slot.rotation = rotation;

    ++_matrixCount;

    return true;
}

uint8_t BBMatrixDisplay::matrixCount() const
{
    return _matrixCount;
}

bool BBMatrixDisplay::show()
{
    bool result = true;

    for (uint8_t i = 0; i < _matrixCount; ++i)
    {
        MatrixSlot& slot = _matrices[i];

        if (slot.matrix == nullptr)
        {
            result = false;
            continue;
        }

        const uint8_t width =
            logicalWidth(slot.rotation);

        const uint8_t height =
            logicalHeight(slot.rotation);

        slot.matrix->clear();

        for (uint8_t logicalY = 0;
             logicalY < height;
             ++logicalY)
        {
            for (uint8_t logicalX = 0;
                 logicalX < width;
                 ++logicalX)
            {
                const BBColor color = getPixel(
                    slot.x + logicalX,
                    slot.y + logicalY);

                uint8_t physicalX = 0;
                uint8_t physicalY = 0;

                mapPixel(
                    logicalX,
                    logicalY,
                    slot.rotation,
                    physicalX,
                    physicalY);

                slot.matrix->drawPixel(
                    physicalX,
                    physicalY,
                    color);
            }
        }

        if (!slot.matrix->show())
        {
            result = false;
        }
    }

    return result;
}

uint8_t BBMatrixDisplay::logicalWidth(
    BBMatrixRotation rotation) const
{
    if (rotation == BBMatrixRotation::R90 ||
        rotation == BBMatrixRotation::R270)
    {
        return BBRGBMatrix8x16::Height;
    }

    return BBRGBMatrix8x16::Width;
}

uint8_t BBMatrixDisplay::logicalHeight(
    BBMatrixRotation rotation) const
{
    if (rotation == BBMatrixRotation::R90 ||
        rotation == BBMatrixRotation::R270)
    {
        return BBRGBMatrix8x16::Width;
    }

    return BBRGBMatrix8x16::Height;
}

void BBMatrixDisplay::mapPixel(
    uint8_t logicalX,
    uint8_t logicalY,
    BBMatrixRotation rotation,
    uint8_t& physicalX,
    uint8_t& physicalY) const
{
    switch (rotation)
    {
        case BBMatrixRotation::R90:
            physicalX =
                BBRGBMatrix8x16::Width - 1 - logicalY;

            physicalY = logicalX;
            break;

        case BBMatrixRotation::R180:
            physicalX =
                BBRGBMatrix8x16::Width - 1 - logicalX;

            physicalY =
                BBRGBMatrix8x16::Height - 1 - logicalY;
            break;

        case BBMatrixRotation::R270:
            physicalX = logicalY;

            physicalY =
                BBRGBMatrix8x16::Height - 1 - logicalX;
            break;

        case BBMatrixRotation::R0:
        default:
            physicalX = logicalX;
            physicalY = logicalY;
            break;
    }
}

}