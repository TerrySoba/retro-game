#include "game_base.h"

#include "png_image.h"

#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>

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

    uint32_t purple = rgb(255,0,255);

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

    auto copyFunctor =
            makePurpleTransparent ?
            [](uint32_t* start, uint32_t* end, uint32_t* dest){ copyIgnorePurple(start, end, dest); } :
            [](uint32_t* start, uint32_t* end, uint32_t* dest){ memcpy(dest, start, (end - start) * sizeof(uint32_t)); };

    for (int line = 0; line < img.getHeight(); ++line)
    {
        copyFunctor(
                &img.getData()[line * img.getWidth()],
                &img.getData()[line * img.getWidth()] + img.getWidth(),
                &m_framebuffer[(y + line) * m_frameWidth + x]);
    }
}




const void* GameBase::draw()
{

//    for (uint64_t i = 0; i < m_frameWidth * m_frameHeight; ++i)
//    {
//        m_framebuffer[i] = i + m_frameCounter;
//    }

    // drawPixel(m_frameCounter % m_frameWidth, 100, rgb(255, 255, 255));

    for (size_t i = 0; i < 100; ++i)
    {
        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(rand() % 256, rand() % 256, rand() % 256));
        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(255, 255, 255))
    }

    drawImage(*m_bgImage, 0, 0, false);


    auto sinValue = sin(m_frameCounter / 10.0) * 10;
    auto cosValue = cos(m_frameCounter / 11.0) * 10;

    drawImage(*m_image, 100 + sinValue, 100 + cosValue, true);

    ++m_frameCounter;
    return m_framebuffer.data();
}