
# RGB Matrix Module

This module provides a high-level API for controlling BLACKBLOX RGB Matrix modules.

The SDK maintains an internal framebuffer and transfers it to the module using `show()`.

## Rendering model

Drawing functions modify only the local framebuffer.

The display is updated only after calling:

```cpp
matrix.show();

| Function           | Status |
| ------------------ | :----: |
| `begin()`          |    ✅   |
| `clear()`          |    ✅   |
| `fill()`           |    ✅   |
| `setPixel()`       |    ✅   |
| `drawMonoBitmap()` |    ✅   |
| `show()`           |    ✅   |
| `drawLine()`       |    ⏳   |
| `drawRectangle()`  |    ⏳   |
| `drawCircle()`     |    ⏳   |
| `drawText()`       |    ⏳   |
| `drawRGBBitmap()`  |    ⏳   |
 Function           | Status |
| ------------------ | :----: |
| `begin()`          |    ✅   |
| `clear()`          |    ✅   |
| `fill()`           |    ✅   |
| `setPixel()`       |    ✅   |
| `drawMonoBitmap()` |    ✅   |
| `show()`           |    ✅   |
| `drawLine()`       |    ⏳   |
| `drawRectangle()`  |    ⏳   |
| `drawCircle()`     |    ⏳   |
| `drawText()`       |    ⏳   |
| `drawRGBBitmap()`  |    ⏳   |

# Usage Examples

## drawMonoBitmap()

Draws a 1-bit bitmap into the framebuffer.

### Parameters

| Parameter | Description |
|-----------|-------------|
| x | X position |
| y | Y position |
| bitmap | Pointer to bitmap data |
| width | Bitmap width in pixels |
| height | Bitmap height in pixels |
| color | Color used for all set pixels |

### Example

```cpp
const uint8_t smiley[] =
{
    0b00111100,
    0b01111110,
    0b11111111,
    0b11011011,
    0b11111111,
    0b10111101,
    0b01100110,
    0b00111100
};

matrix.drawMonoBitmap(
    0,
    0,
    smiley,
    8,
    8,
    BBColor::Yellow());

matrix.show();
```