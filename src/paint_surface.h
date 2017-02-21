#ifndef PAINT_SURFACE_H
#define PAINT_SURFACE_H

#include "image.h"

#include <cstdint>
#include <vector>

class PaintSurface
{
public:
    PaintSurface(uint32_t width, uint32_t height);

    void drawPixel(uint32_t x, uint32_t y, uint32_t pixel);
    void drawImage(Image& img, int32_t x, int32_t y, bool makePurpleTransparent = false);

    uint32_t* getData() { return m_framebuffer.data(); }

    uint32_t getWidth() { return m_width; }
    uint32_t getHeight() { return m_height; }

private:
    uint32_t m_width;
    uint32_t m_height;
    std::vector<uint32_t> m_framebuffer;
};

#endif // PAINT_SURFACE_H
