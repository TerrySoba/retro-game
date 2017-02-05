#pragma once

#include "image.h"
#include "animation.h"
#include "enemy_ship.h"
#include "player_ship.h"
#include "input_listener.h"

#include "boost/optional.hpp"

#include <cstdint>
#include <vector>
#include <array>
#include <functional>
#include <memory>

struct GameInput
{
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool button = false;
};

// forward declaration
class MikmodSound;

class GameBase
{
public:
    GameBase(unsigned frameWidth, unsigned frameHeight);
    virtual ~GameBase() {}

    void init();
    void deinit();
    const void* run(GameInput input);
    void audio(std::function<size_t(const int16_t*,size_t)> batchAudioCallback);

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
    void handleInputs(GameInput input);

private:
    uint32_t m_frameWidth;
    uint32_t m_frameHeight;

    std::vector<uint32_t> m_framebuffer;

    uint64_t m_frameCounter = 0;

    std::shared_ptr<Image> m_image;
    std::shared_ptr<Image> m_bgImage;
    std::shared_ptr<Animation> m_anim;
    std::shared_ptr<EnemyShip> m_enemy;
    std::shared_ptr<PlayerShip> m_player;

    int32_t m_posX = 100;
    int32_t m_posY = 100;

    std::shared_ptr<MikmodSound> m_sound;
    std::vector<char> m_audioBuffer;

    std::vector<std::weak_ptr<InputListener>> m_inputListeners;

    size_t m_sampleId;

    GameInput m_lastGameInput;
};
