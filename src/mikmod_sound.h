#ifndef MIKMOD_SOUND_H
#define MIKMOD_SOUND_H

#include <cstdint>
#include <cstdlib>

class MikmodSound
{
public:
    MikmodSound();

    void initMikmod();
    void update();

    uint32_t& getBufferSize();
    int16_t* getBuffer();

    /**
     * Renders the given number of audioframes to the destination buffer.
     *
     * An audio frame is 32bits wide. The first 16 bit of the frame represent
     * the audio sample of the left audio channel. The second 16bit represent
     * the audio sample of the right audio channel.
     *
     * @param frames Number of frsames to be rendered. (bytes = frames * 4)
     * @param dest The buffer to render the audio frames to.
     */
    void renderAudioFrames(size_t frames, void* dest);

};

#endif // MIKMOD_SOUND_H
