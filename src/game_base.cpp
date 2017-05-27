#include "game_base.h"

#include "png_image.h"
#include "rectangle.h"
#include "mikmod_sound.h"
#include "mikmod_driver/drv_retro_game.h"

#include "actors/enemy_ship.h"
#include "actors/player_ship.h"
#include "actors/bullet.h"

#include "fmt/format.h"
#include "exception.h"

#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

#ifdef __linux__
	#include <unistd.h>
#endif

GameBase::GameBase(uint32_t frameWidth, uint32_t frameHeight) :
    m_framebuffer(frameWidth * frameHeight),
    m_surface(new PaintSurface(m_framebuffer.data(), frameWidth, frameHeight)),
    m_engine(new GfxEngine),
    m_sound(new MikmodSound),
    m_audioBuffer(735 * 4) // 44100 / 60 == 735 , one audio frame == 4 bytes
{
}


void GameBase::init()
{
    m_image = std::make_shared<PngImage>("assets/images/red_ship.png");
    m_bgImage = std::make_shared<PngImage>("assets/images/space_bg.png");
    m_anim = std::make_shared<Animation>("assets/animations/space_ship_64x32/*.png");
    m_font = std::make_shared<TextureFont>();
    // m_font->load("assets/fonts/DejaVuSans-Bold-10px.ytf");
    m_font->load("assets/fonts/Japanese-14px.ytf");


//    m_image = m_font->getImage();

    PaintSurface surface(*m_bgImage);

    m_font->renderToImage(surface, 20, 100, u8"これはテストです。Test123äöü");

    auto enemy = std::make_shared<EnemyShip>(m_anim);
    enemy->setInitialPos(Eigen::Vector2i(50, 40));
    m_engine->addActor(enemy, "TheEnemy");

    auto player = std::make_shared<PlayerShip>(m_image, Eigen::Vector2i(10, 10));
    m_engine->addActor(player, "ThePlayer");
    m_inputListeners.push_back(player);

    auto bullet = std::make_shared<Bullet>();
    m_engine->addActor(bullet, "Bullet");

    m_sound->playModule("assets/music/test_music.xm");

    m_sampleId = m_sound->loadSample("assets/sounds/Per-Reverb.wav");

    m_engine->start();
}

void GameBase::deinit()
{
}



const void* GameBase::run(GameInput input)
{
    handleInputs(input);

    if (input.button)
    {
        // m_sound->playSample(m_sampleId);
    }
        //m_sound->togglePause();

    m_surface->drawImage(*m_bgImage, 0, 0, false);

    if (input.left) m_posX--;
    if (input.right) m_posX++;
    if (input.down) m_posY++;
    if (input.up) m_posY--;
    m_anim->setFrame(static_cast<uint32_t>(m_frameCounter));

    ++m_frameCounter;

    m_engine->draw(*m_surface);

    return m_surface->getData();
}

void GameBase::handleInputs(GameInput input)
{
    auto callOnAllListeners = [this](std::function<void(InputListener&)> functor)
    {
        for (auto& listener : m_inputListeners)
        {
            auto ptr = listener.lock();
            if (ptr) functor(*ptr);
        }
    };

    if (input.left && !m_lastGameInput.left)
    {
        callOnAllListeners([](InputListener& listener) {listener.leftPressed();});
    }
    if (!input.left && m_lastGameInput.left)
    {
        callOnAllListeners([](InputListener& listener) {listener.leftReleased();});
    }
    if (input.right && !m_lastGameInput.right)
    {
        callOnAllListeners([](InputListener& listener) {listener.rightPressed();});
    }
    if (!input.right && m_lastGameInput.right)
    {
        callOnAllListeners([](InputListener& listener) {listener.rightReleased();});
    }

    if (input.up && !m_lastGameInput.up)
    {
        callOnAllListeners([](InputListener& listener) {listener.upPressed();});
    }
    if (!input.up && m_lastGameInput.up)
    {
        callOnAllListeners([](InputListener& listener) {listener.upReleased();});
    }
    if (input.down && !m_lastGameInput.down)
    {
        callOnAllListeners([](InputListener& listener) {listener.downPressed();});
    }
    if (!input.down && m_lastGameInput.down)
    {
        callOnAllListeners([](InputListener& listener) {listener.downReleased();});
    }

    if (input.button && !m_lastGameInput.button)
    {
        callOnAllListeners([](InputListener& listener) {listener.buttonPressed();});
    }
    if (!input.button && m_lastGameInput.button)
    {
        callOnAllListeners([](InputListener& listener) {listener.buttonReleased();});
    }

    m_lastGameInput = input;
}

void GameBase::audio(std::function<size_t(const int16_t*,size_t)> batchAudioCallback)
{
    m_sound->renderAudioFrames(735, m_audioBuffer.data());
    batchAudioCallback((int16_t*)m_audioBuffer.data(), 735);
}
