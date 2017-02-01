#ifndef MIKMOD_SOUND_H
#define MIKMOD_SOUND_H

#include <cstdint>
#include <cstdlib>

#include <string>
#include <memory>
#include <vector>

// forward declaration
struct MODULE;
struct SAMPLE;

typedef size_t SampleId;

/**
 * This class is an abstraction for libmikmod.
 *
 * It can be used to play mod music and also to play
 * samples.
 */
class MikmodSound
{
public:
    /**
     * Constructor
     *
     * Initializes mikmod.
     */
    MikmodSound();

    /**
     * Destructor
     *
     * Deinitializes mikmod and frees all loaded samples and modules.
     */
    ~MikmodSound();

    /**
     * Plays the given module.
     * May throw exceptions if file is not found or mikmod
     * reports an error.
     *
     * @param filename The path to the file to be played.
     */
    void playModule(const std::string filename);

    /**
     * Toggles pause of the mod playback.
     */
    void togglePause();

    /**
     * Loads a sample from the given path and returns
     * an id for that sample.
     * May throw exceptions if file is not found or mikmod
     * reports an error.
     *
     * @param filename The path to the file to be loaded.
     * @return An id that represents the loaded sample.
     */
    SampleId loadSample(const std::string filename);

    /**
     * Plays the sample repesented by the id.
     * \see loadSample on how to get a sample id.
     *
     * @param sampleId The id of the sample to be played.
     */
    void playSample(SampleId sampleId);

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

private:
    std::shared_ptr<MODULE> m_module;
    std::vector<std::shared_ptr<SAMPLE>> m_samples;
};

#endif // MIKMOD_SOUND_H
