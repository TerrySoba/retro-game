#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <cmath>
#include <limits>
#include <iostream>

#include "libretro/libretro.h"
#include "game_base.h"

std::unique_ptr<GameBase> s_game;

static const unsigned FRAMEBUFFER_WIDTH = 320;
static const unsigned FRAMEBUFFER_HEIGHT = 240;

// Callbacks
static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static retro_environment_t environ_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;

unsigned retro_api_version(void) { return RETRO_API_VERSION; }

// Cheats
void retro_cheat_reset(void) {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}

// Load a cartridge
bool retro_load_game(const struct retro_game_info *info)
{
    return true;
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) { return false; }

// Unload the cartridge
void retro_unload_game(void) {  }

unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }

// libretro unused api functions
void retro_set_controller_port_device(unsigned port, unsigned device) {}


void *retro_get_memory_data(unsigned id) { return NULL; }
size_t retro_get_memory_size(unsigned id){ return 0; }

// Serialisation methods
size_t retro_serialize_size(void) { return 0; }
bool retro_serialize(void *data, size_t size) { return false; }
bool retro_unserialize(const void *data, size_t size) { return false; }

// End of retrolib
void retro_deinit(void)
{
    s_game.reset();
}

// libretro global setters
void retro_set_environment(retro_environment_t cb)
{
    environ_cb = cb;
    bool no_rom = true;
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

void retro_init(void)
{
    s_game = std::make_unique<GameBase>(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

    s_game->init();

    /* set up some logging */
    struct retro_log_callback log;
    unsigned level = 4;

    if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
        log_cb = log.log;
    else
        log_cb = NULL;

    // the performance level is guide to frontend to give an idea of how intensive this core is to run
    environ_cb(RETRO_ENVIRONMENT_SET_PERFORMANCE_LEVEL, &level);
}


/*
 * Tell libretro about this core, it's name, version and which rom files it supports.
 */
void retro_get_system_info(struct retro_system_info *info)
{
    memset(info, 0, sizeof(*info));
    info->library_name = "RetroGame";
    info->library_version = "0.1";
    info->need_fullpath = false;
    info->valid_extensions = "game";
}

/*
 * Tell libretro about the AV system; the fps, sound sample rate and the
 * resolution of the display.
 */
void retro_get_system_av_info(struct retro_system_av_info *info)
{

    int pixel_format = RETRO_PIXEL_FORMAT_XRGB8888;

    memset(info, 0, sizeof(*info));
    info->timing.fps            = 60.0f;
    info->timing.sample_rate    = 44100;
    info->geometry.base_width   = FRAMEBUFFER_WIDTH;
    info->geometry.base_height  = FRAMEBUFFER_HEIGHT;
    info->geometry.max_width    = FRAMEBUFFER_WIDTH;
    info->geometry.max_height   = FRAMEBUFFER_HEIGHT;
    info->geometry.aspect_ratio = 4.0/3.0;

    environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixel_format);
}

void retro_reset(void) { }

static int offset = 0;
static uint64_t audioFrame = 0;


// Run a single frame
void retro_run(void)
{
    /*
    for (int i = 0; i < (44100 / 60); i++)
    {
        audioFrame++;
        uint16_t sine = (sin(audioFrame / 100) + 1) * std::numeric_limits<uint16_t>::max() * 0.1;
        audio_cb(sine, sine);
    }
    */

//    for (int i = 0; i < 320 * 200; ++i)
//    {
//        framebuffer[i] = i + offset;
//    }

//    offset+=320 * 200;

    // retro_input_poll_t input;
    input_poll_cb();

    // RETRO_DEVICE_JOYPAD
    // unsigned port, unsigned device, unsigned index, unsigned id

    GameInput input;

    input.right = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT);
    input.left = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT);
    input.up = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP);
    input.down = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN);

    // std::cout << "data: " << data << std::endl;


    auto frameBuffer = s_game->run(input);

    video_cb(frameBuffer, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, sizeof(uint32_t) * FRAMEBUFFER_WIDTH);
}
