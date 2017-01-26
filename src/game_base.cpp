#include "game_base.h"

#include "png_image.h"
#include "rectangle.h"

#include "fmt/format.h"
#include "exception.h"

#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

#include <unistd.h>



GameBase::GameBase(uint32_t frameWidth, uint32_t frameHeight) :
    m_frameWidth(frameWidth),
    m_frameHeight(frameHeight),
    m_framebuffer(frameWidth * frameHeight)
{
}


void GameBase::init()
{
    m_image = std::make_shared<PngImage>("../retro-game/images/rgb_test.png");
    m_bgImage = std::make_shared<PngImage>("../retro-game/images/wood_bg.png");
    m_anim = std::make_shared<Animation>("../retro-game/gfx/space_ship/animation_64x32/", 0, 250);
    std::memset(m_framebuffer.data(), 0, m_frameWidth * m_frameHeight * 4);
}

void GameBase::drawPixel(uint32_t x, uint32_t y, uint32_t pixel)
{
    assert(x < m_frameWidth);
    assert(y < m_frameHeight);
    m_framebuffer[x + y*m_frameWidth] = pixel;
}

constexpr uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return b | (g << 8) | (r << 16);
}


void copyIgnorePurple(uint32_t* start, uint32_t* end, uint32_t* dest)
{

    const uint32_t purple = rgb(255,0,255);

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


void GameBase::drawImage(Image& img, int32_t x, int32_t y, bool makePurpleTransparent)
{
    Rectangle screenRect(0, 0, m_frameWidth, m_frameHeight);

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

        auto xOffScreen = tl.x;
        auto yOffScreen = tl.y;

        auto xOffImg = tl.x - x;
        auto yOffImg = tl.y - y;

        auto imgData = img.getData();

        auto drawWidth = inter.getWidth();

        auto imgWidth = img.getWidth();

        for (int line = 0; line < inter.getHeight(); ++line)
        {
            copyFunctor(
                    &imgData[(line + yOffImg) * imgWidth + xOffImg],
                    &imgData[(line + yOffImg) * imgWidth + xOffImg + drawWidth],
                    &m_framebuffer[(yOffScreen + line) * m_frameWidth + xOffScreen]);
        }
    }
}




const void* GameBase::run(GameInput input)
{

//    for (uint64_t i = 0; i < m_frameWidth * m_frameHeight; ++i)
//    {
//        m_framebuffer[i] = i + m_frameCounter;
//    }

    // drawPixel(m_frameCounter % m_frameWidth, 100, rgb(255, 255, 255));

//    for (size_t i = 0; i < 100; ++i)
//    {
//        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(rand() % 256, rand() % 256, rand() % 256));
//        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(255, 255, 255))
//    }

    drawImage(*m_bgImage, 0, 0, false);

    for (size_t i = 0; i < 10; ++i)
    {
        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(rand() % 256, rand() % 256, rand() % 256));
        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(0,0,0));
    }


    // auto sinValue = sin(m_frameCounter / 10.0) * 40;
    // auto cosValue = cos(m_frameCounter / 11.12133524) * 30;

    // drawImage(*m_image, 100 + sinValue, 100 + cosValue , true);

    if (input.left) m_posX--;
    if (input.right) m_posX++;
    if (input.down) m_posY++;
    if (input.up) m_posY--;
    m_anim->setFrame(m_frameCounter);

    drawImage(*m_anim, m_posX, m_posY, true);

    ++m_frameCounter;
    return m_framebuffer.data();
}
