#ifndef PAINT_SURFACE_H
#define PAINT_SURFACE_H

#include "image.h"

#include <cstdint>
#include <vector>

constexpr uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return b | (g << 8) | (r << 16);
}

class PaintSurface
{
public:
    PaintSurface(Image& img);
    PaintSurface(uint32_t* framebuffer, uint32_t width, uint32_t height);

    void drawPixel(uint32_t x, uint32_t y, uint32_t pixel);
    void drawImage(Image& sourceImg, int32_t x, int32_t y, bool makePurpleTransparent = false);
    void drawImage(Image& sourceImg,
                   int32_t sourceX, int32_t sourceY, int32_t sourceWidth, int32_t sourceHeight,
                   int32_t targetX, int32_t targetY,
                   bool makePurpleTransparent = false);

    uint32_t* getData() { return m_framebuffer; }

    uint32_t getWidth() { return m_width; }
    uint32_t getHeight() { return m_height; }

private:
    uint32_t* m_framebuffer;
    uint32_t m_width;
    uint32_t m_height;
};

#endif // PAINT_SURFACE_H
