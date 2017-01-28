#include <stdint.h>
#include <stdlib.h>
#include <mikmod.h>
#include <string.h>
#include <stdio.h>


static BOOL retro_IsThere(void)
{  
	return 1;
}

#define RETRO_AUDIO_BUFFER_SIZE (735 * 4) * 5
uint8_t* retro_audioBuffer = NULL;
uint32_t retro_bufferSize = 0;
uint32_t retro_bufferContentLength = 0;

static BOOL retro_Init(void)
{
    retro_audioBuffer = (SBYTE*)malloc(sizeof(SBYTE) * RETRO_AUDIO_BUFFER_SIZE);
    // retro_bufferPos = 0;
    return VC_Init();
}

static void retro_Exit(void)
{
    free(retro_audioBuffer);
    VC_Exit();
}

static void retro_Update(void)
{
    retro_bufferContentLength = VC_WriteBytes(retro_audioBuffer, retro_bufferSize);
}

static BOOL retro_Reset(void)
{
	VC_Exit();
	return VC_Init();
}

MDRIVER drv_retrogame =
{
	NULL,
    "RetroGame",
    "RetroGame v0.1",

    0,
    255,

    "retro",
    NULL,

    NULL, // todo: may this be NULL?
    retro_IsThere,
	VC_SampleLoad,
	VC_SampleUnload,
	VC_SampleSpace,
	VC_SampleLength,
    retro_Init,
    retro_Exit,
    retro_Reset,
	VC_SetNumVoices,
	VC_PlayStart,
	VC_PlayStop,
    retro_Update,
	NULL,
	VC_VoiceSetVolume,
	VC_VoiceGetVolume,
	VC_VoiceSetFrequency,
	VC_VoiceGetFrequency,
	VC_VoiceSetPanning,
	VC_VoiceGetPanning,
	VC_VoicePlay,
	VC_VoiceStop,
	VC_VoiceStopped,
	VC_VoiceGetPosition,
	VC_VoiceRealVolume
};
