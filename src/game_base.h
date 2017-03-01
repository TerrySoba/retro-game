#pragma once

#include "image.h"
#include "animation.h"
#include "input_listener.h"
#include "paint_surface.h"
#include "gfx_engine.h"

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

    unsigned getFrameWidth()
    {
        return m_surface->getWidth();
    }

    unsigned getFrameHeight()
    {
        return m_surface->getHeight();
    }

private:
    void handleInputs(GameInput input);

private:

    std::shared_ptr<PaintSurface> m_surface;

    std::shared_ptr<GfxEngine> m_engine;

    uint64_t m_frameCounter = 0;

    std::shared_ptr<Image> m_image;
    std::shared_ptr<Image> m_bgImage;
    std::shared_ptr<Animation> m_anim;

    int32_t m_posX = 100;
    int32_t m_posY = 100;

    std::shared_ptr<MikmodSound> m_sound;
    std::vector<char> m_audioBuffer;

    std::vector<std::weak_ptr<InputListener>> m_inputListeners;

    size_t m_sampleId;

    GameInput m_lastGameInput;
};
