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
    md_mode = DMODE_SOFT_MUSIC | DMODE_16BITS | DMODE_STEREO | DMODE_HQMIXER | DMODE_INTERP | DMODE_SOFT_SNDFX;
    md_mixfreq = 44100;
    md_reverb = 5;

    /* initialize the library */
    if (MikMod_Init(const_cast<char*>(""))) {
        throw Exception(fmt::format("Could not initialize sound, reason: {}\n", MikMod_strerror(MikMod_errno)));
    }

    /* reserve 2 voices for sound effects */
    MikMod_SetNumVoices(-1, 2);

    MikMod_EnableOutput();
}

MikmodSound::~MikmodSound()
{
    if (m_module)
    {
        Player_Stop();
    }
    MikMod_Exit();
}


void MikmodSound::playModule(const std::string filename)
{
    // stop playback and free module if one is already running
    if (m_module)
    {
        Player_Stop();
    }

    /* load module */
    m_module = std::shared_ptr<MODULE>(
                Player_Load(const_cast<char*>(filename.c_str()), 64, false),
                [](MODULE* ptr) { Player_Free(ptr); });

    if (!m_module)
    {
        throw Exception(fmt::format("Could not load module, reason: {}\n", MikMod_strerror(MikMod_errno)));
    }

    m_module->loop = true;
    m_module->wrap = true;

    /* start module */
    Player_Start(m_module.get());

}

void MikmodSound::togglePause()
{
    Player_TogglePause();
}

SampleId MikmodSound::loadSample(const std::string filename)
{
    auto sample = Sample_Load(const_cast<char*>(filename.c_str()));
    if (!sample)
    {
        throw Exception(fmt::format("Could not load sample, reason: {}\n", MikMod_strerror(MikMod_errno)));
    }

    m_samples.push_back(
                std::shared_ptr<SAMPLE>(sample,
                    [](SAMPLE* ptr) { Sample_Free(ptr); }));

    return m_samples.size() - 1;
}

void MikmodSound::playSample(SampleId sampleId)
{
    if (m_samples.size() <= sampleId)
    {
        throw Exception(fmt::format("Could not play sample id: {}, there are only {} samples available.\n", sampleId, m_samples.size()));
    }
    auto voice = Sample_Play(m_samples[sampleId].get(), 0, 0);

    Voice_SetPanning(voice, PAN_CENTER);
}

void MikmodSound::renderAudioFrames(size_t frames, void* dest)
{
    auto requestedBytes = frames * 4;
    retro_bufferBytesRequested = requestedBytes;
    retro_bufferBytesWritten = 0;

    // MikMod_Update() will the now fill the retro_audioBuffer with up to
    // retro_bufferBytesRequested bytes of data. The actual number of bytes
    // will be written to retro_bufferBytesWritten.
    // In some cases no data will be written at all and retro_bufferBytesWritten
    // will not be set. Because of this you must set retro_bufferBytesWritten to
    // 0 before calling MikMod_Update().
    MikMod_Update();

    if (retro_bufferBytesWritten != requestedBytes)
    {
        memset((char*)dest + retro_bufferBytesWritten, 0, requestedBytes - retro_bufferBytesWritten);
    }
    memcpy(dest, retro_audioBuffer, retro_bufferBytesWritten);
}
