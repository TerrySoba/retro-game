#include "mikmod_sound.h"
#include "mikmod_driver/drv_retro_game.h"

#include "exception.h"
#include "fmt/format.h"

#include <mikmod.h>
#include <unistd.h>
#include <string.h>

#include <iostream>


MikmodSound::MikmodSound()
{
    // register our own special driver
    MikMod_RegisterDriver(&drv_retrogame);

    /* register all the module loaders */
    MikMod_RegisterAllLoaders();

    // set some settings of mikmod
    md_mode = DMODE_SOFT_MUSIC | DMODE_16BITS | DMODE_STEREO | DMODE_HQMIXER | DMODE_INTERP;
    md_mixfreq = 44100;
    md_reverb = 5;

    /* initialize the library */
    if (MikMod_Init("")) {
        throw Exception(fmt::format("Could not initialize sound, reason: {}\n", MikMod_strerror(MikMod_errno)));
    }
}

MikmodSound::~MikmodSound()
{
    if (m_module)
    {
        Player_Stop();
        Player_Free(m_module);
    }
    MikMod_Exit();
}


void MikmodSound::playModule(const std::string filename)
{
    // stop playback and free module if one is already running
    if (m_module)
    {
        Player_Stop();
        Player_Free(m_module);
    }

    /* load module */
    m_module = Player_Load(filename.c_str(), 64, false);

    if (!m_module)
    {
        throw Exception(fmt::format("Could not load module, reason: {}\n", MikMod_strerror(MikMod_errno)));
    }

    m_module->loop = true;
    m_module->wrap = true;

    /* start module */
    Player_Start(m_module);

}

void MikmodSound::renderAudioFrames(size_t frames, void* dest)
{
    auto requestedBytes = frames * 4;
    retro_bufferSize = requestedBytes;
    retro_bufferContentLength = 0;
    MikMod_Update();

    if (retro_bufferContentLength != requestedBytes)
    {
        memset((char*)dest + retro_bufferContentLength, 0, requestedBytes - retro_bufferContentLength);
    }
    memcpy(dest, retro_audioBuffer, retro_bufferContentLength);
}
