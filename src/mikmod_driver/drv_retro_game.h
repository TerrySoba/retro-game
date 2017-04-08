#ifndef DRV_RETRO_GAME_H
#define DRV_RETRO_GAME_H

#include <mikmod.h>

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RETRO_AUDIO_BUFFER_SIZE (735 * 4) * 5
extern uint8_t* retro_audioBuffer;
extern uint32_t retro_bufferBytesRequested;
extern uint32_t retro_bufferBytesWritten;

extern MDRIVER drv_retrogame;

#ifdef __cplusplus
}
#endif

#endif // DRV_RETRO_GAME_H
