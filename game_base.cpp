#include "game_base.h"

#include "png_image.h"

#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>

#include <mikmod.h>
#include <unistd.h>

GameBase::GameBase(uint32_t frameWidth, uint32_t frameHeight) :
    m_frameWidth(frameWidth),
    m_frameHeight(frameHeight),
    m_framebuffer(frameWidth * frameHeight)
{
}

MODULE *module;

void GameBase::init()
{
    PngImage img("../RetroGame/images/rgb_test.png");
    std::memset(m_framebuffer.data(), 0, m_frameWidth * m_frameHeight * 4);
}

void GameBase::drawPixel(uint32_t x, uint32_t y, uint32_t pixel)
{
    assert(x < m_frameWidth);
    assert(y < m_frameHeight);
    m_framebuffer[x + y*m_frameWidth] = pixel;
}


uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return b | (g << 8) | (r << 16);
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
        drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(rand() % 256, rand() % 256, rand() % 256));
        // drawPixel(rand() % m_frameWidth, rand() % m_frameHeight, rgb(255, 255, 255))
    }


    ++m_frameCounter;
    return m_framebuffer.data();
}
