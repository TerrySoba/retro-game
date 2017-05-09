#include "mikmod_sound.h"
#include "mikmod_driver/drv_retro_game.h"

#include "exception.h"
#include "fmt/format.h"

#include <mikmod.h>

#ifdef __linux__
	#include <unistd.h>
#endif

#include <string.h>

#include <iostream>


MikmodSound::MikmodSound()
{
}

MikmodSound::~MikmodSound()
{
}


void MikmodSound::playModule(const std::string filename)
{
}

void MikmodSound::togglePause()
{
}

SampleId MikmodSound::loadSample(const std::string filename)
{
    return SampleId();
}

void MikmodSound::playSample(SampleId sampleId)
{
}

void MikmodSound::renderAudioFrames(size_t frames, void* dest)
{
    auto requestedBytes = frames * 4;
    memset(dest, 0, requestedBytes);
}
