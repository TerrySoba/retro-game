#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <functional>

class GameBase
{
public:
    GameBase(unsigned frameWidth, unsigned frameHeight);
    virtual ~GameBase() {}

    void init();
    const void* draw();

    void drawPixel(uint32_t x, uint32_t y, uint32_t pixel);
    void drawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t pixel);

    unsigned getFrameWidth()
    {
        return m_frameWidth;
    }

    unsigned getFrameHeight()
    {
        return m_frameHeight;
    }

private:
    uint32_t m_frameWidth;
    uint32_t m_frameHeight;

    std::vector<uint32_t> m_framebuffer;

    uint64_t m_frameCounter = 0;

};
