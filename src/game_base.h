#pragma once

#include "image.h"

#include <cstdint>
#include <vector>
#include <array>
#include <functional>
#include <memory>

struct GameInput
{
    bool left;
    bool right;
    bool up;
    bool down;
};

class GameBase
{
public:
    GameBase(unsigned frameWidth, unsigned frameHeight);
    virtual ~GameBase() {}

    void init();
    const void* run(GameInput input);

    void drawPixel(uint32_t x, uint32_t y, uint32_t pixel);
    void drawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t pixel);

    void drawImage(Image& img, int32_t x, int32_t y, bool makePurpleTransparent = false);

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

    std::shared_ptr<Image> m_image;
    std::shared_ptr<Image> m_bgImage;

    int32_t m_posX = 100;
    int32_t m_posY = 100;

};
