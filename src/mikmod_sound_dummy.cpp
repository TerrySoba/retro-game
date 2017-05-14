#include "mikmod_sound.h"

#include <string.h>

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
