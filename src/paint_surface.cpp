#include "paint_surface.h"

#include "rectangle.h"

#include <cstring>
#include <assert.h>

PaintSurface::PaintSurface(uint32_t width, uint32_t height) :
    m_width(width),
    m_height(height),
    m_framebuffer(width * height)
{
}

void PaintSurface::drawPixel(uint32_t x, uint32_t y, uint32_t pixel)
{
    assert(x < m_width);
    assert(y < m_height);
    m_framebuffer[x + y*m_width] = pixel;
}

constexpr uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return b | (g << 8) | (r << 16);
}


void copyIgnorePurple(uint32_t* start, uint32_t* end, uint32_t* dest)
{

    static const uint32_t purple = rgb(255,0,255);

    while (start != end)
    {
        if (*start != purple)
        {
            *dest++ = *start++;
        }
        else
        {
            dest++;
            start++;
        }
    }

}


void PaintSurface::drawImage(Image& img, int32_t x, int32_t y, bool makePurpleTransparent)
{
    Rectangle screenRect(0, 0, m_width, m_height);

    // check if image is visible at all
    Rectangle imgRect(x, y, img.getWidth(), img.getHeight());
    auto inter = screenRect.intersection(imgRect);

    // only draw img if it is visible
    bool visible = (inter.getWidth() > 0 &&
                    inter.getHeight() > 0);

    if (visible)
    {
        auto copyFunctor =
                makePurpleTransparent ?
                [](uint32_t* start, uint32_t* end, uint32_t* dest){ copyIgnorePurple(start, end, dest); } :
                [](uint32_t* start, uint32_t* end, uint32_t* dest){ memcpy(dest, start, (end - start) * sizeof(uint32_t)); };

        auto tl = inter.getTopLeft();

        auto xOffScreen = tl[0];
        auto yOffScreen = tl[1];

        auto xOffImg = tl[0] - x;
        auto yOffImg = tl[1] - y;

        auto imgData = img.getData();

        auto drawWidth = inter.getWidth();

        auto imgWidth = img.getWidth();

        for (int line = 0; line < inter.getHeight(); ++line)
        {
            copyFunctor(
                    &imgData[(line + yOffImg) * imgWidth + xOffImg],
                    &imgData[(line + yOffImg) * imgWidth + xOffImg + drawWidth],
                    &m_framebuffer[(yOffScreen + line) * m_width + xOffScreen]);
        }
    }
}
