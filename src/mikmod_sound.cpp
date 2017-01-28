#include "mikmod_sound.h"

#include "mikmod_driver/drv_retro_game.h"

#include <mikmod.h>
#include <unistd.h>

#include <iostream>


MikmodSound::MikmodSound()
{

}


void MikmodSound::initMikmod()
{
    MODULE *module;

    /* register all the drivers */
    // MikMod_RegisterAllDrivers();

    MikMod_RegisterDriver(&drv_retrogame);


    /* register all the module loaders */
    MikMod_RegisterAllLoaders();

    /* initialize the library */
    md_mode = DMODE_SOFT_MUSIC | DMODE_16BITS | DMODE_STEREO | DMODE_HQMIXER | DMODE_INTERP;
    md_mixfreq = 44100;
    md_reverb = 5;

    // std::cout << MikMod_InfoDriver() << std::endl;

    if (MikMod_Init("")) {
        fprintf(stderr, "Could not initialize sound, reason: %s\n",
                MikMod_strerror(MikMod_errno));
        return;
    }

    /* load module */
    module = Player_Load("/home/yoshi252/Downloads/external.xm", 64, 0);
    if (module) {
        /* start module */
        Player_Start(module);

    }
//        while (Player_Active()) {
//            /* we're playing */
//            usleep(10000);
//            MikMod_Update();
//        }

//        Player_Stop();
//        Player_Free(module);
//    } else
//        fprintf(stderr, "Could not load module, reason: %s\n",
//                MikMod_strerror(MikMod_errno));

//    /* give up */
//    MikMod_Exit();
}

void MikmodSound::update()
{
    MikMod_Update();
}


uint32_t& MikmodSound::getBufferSize()
{
    return retro_bufferPos;
}

int16_t* MikmodSound::getBuffer()
{
    return reinterpret_cast<int16_t*>(retro_audioBuffer);
}

void renderAudioFrames(size_t frames, void* dest)
{

}
