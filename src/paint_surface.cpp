#include "paint_surface.h"

#include "rectangle.h"
#include "exception.h"

#include "fmt/format.h"
#include <cstring>
#include <assert.h>

PaintSurface::PaintSurface(Image& img) :
    m_framebuffer(img.getData()),
    m_width(img.getWidth()),
    m_height(img.getHeight())
{
}

PaintSurface::PaintSurface(uint32_t* framebuffer, uint32_t width, uint32_t height) :
    m_framebuffer(framebuffer),
    m_width(width),
    m_height(height)
{
}

void PaintSurface::drawPixel(uint32_t x, uint32_t y, uint32_t pixel)
{
    assert(x < m_width);
    assert(y < m_height);
    m_framebuffer[x + y*m_width] = pixel;
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
    MyRectangle screenRect(0, 0, m_width, m_height);

    // check if image is visible at all
    MyRectangle imgRect(x, y, img.getWidth(), img.getHeight());
    auto inter = screenRect.intersection(imgRect);

    // only draw img if it is visible
    bool visible = (inter.getWidth() > 0 &&
                    inter.getHeight() > 0);

    if (visible)
    {
		std::function<void(uint32_t*, uint32_t*, uint32_t*)> copyFunctor;
		if (makePurpleTransparent) {
			copyFunctor = [](uint32_t* start, uint32_t* end, uint32_t* dest) { copyIgnorePurple(start, end, dest); };
		} else {
			copyFunctor = [](uint32_t* start, uint32_t* end, uint32_t* dest) { memcpy(dest, start, (end - start) * sizeof(uint32_t)); };
		}


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


void PaintSurface::drawImage(Image& sourceImg,
               int32_t sourceX, int32_t sourceY, int32_t sourceWidth, int32_t sourceHeight,
               int32_t targetX, int32_t targetY,
               bool makePurpleTransparent)
{
    // calculations done in framebuffer coordinates
    MyRectangle screenRect(0, 0, m_width, m_height);
    MyRectangle sourceImageRect(targetX - sourceX, targetY - sourceY, sourceImg.getWidth(), sourceImg.getHeight());
    MyRectangle targetImageRect(targetX, targetY, sourceWidth, sourceHeight);
    MyRectangle drawRect = screenRect.intersection(sourceImageRect.intersection(targetImageRect));

//    LOG(fmt::format("screen x:{} y:{} w:{} h:{}", screenRect.getTopLeft()[0], screenRect.getTopLeft()[1], screenRect.getWidth(), screenRect.getHeight()));
//    LOG(fmt::format("src x:{} y:{} w:{} h:{}", sourceImageRect.getTopLeft()[0], sourceImageRect.getTopLeft()[1], sourceImageRect.getWidth(), sourceImageRect.getHeight()));
//    LOG(fmt::format("targetImageRect x:{} y:{} w:{} h:{}", targetImageRect.getTopLeft()[0], targetImageRect.getTopLeft()[1], targetImageRect.getWidth(), targetImageRect.getHeight()));
//    LOG(fmt::format("drawRect x:{} y:{} w:{} h:{}", drawRect.getTopLeft()[0], drawRect.getTopLeft()[1], drawRect.getWidth(), drawRect.getHeight()));

    if (!drawRect.empty())
    {

        std::function<void(uint32_t*, uint32_t*, uint32_t*)> copyFunctor;
        if (makePurpleTransparent) {
            copyFunctor = [](uint32_t* start, uint32_t* end, uint32_t* dest) { copyIgnorePurple(start, end, dest); };
        } else {
            copyFunctor = [](uint32_t* start, uint32_t* end, uint32_t* dest) { memcpy(dest, start, (end - start) * sizeof(uint32_t)); };
        }

        auto xOffScreen = drawRect.getTopLeft()[0];
        auto yOffScreen = drawRect.getTopLeft()[1];

        auto xOffImg = sourceX + sourceWidth - drawRect.getWidth();
        auto yOffImg = sourceY + sourceHeight - drawRect.getHeight();

        auto imgData = sourceImg.getData();

        for (int32_t line = 0; line < drawRect.getHeight(); ++line)
        {
            uint32_t* target = &m_framebuffer[(yOffScreen + line) * m_width + xOffScreen];
            uint32_t* source = &imgData[sourceImg.getWidth() * (line + yOffImg) + xOffImg];

            copyFunctor(source, source + drawRect.getWidth(), target);
        }
    }
}
