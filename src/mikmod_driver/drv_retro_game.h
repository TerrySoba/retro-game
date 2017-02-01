#ifndef DRV_RETRO_GAME_H
#define DRV_RETRO_GAME_H

#include <mikmod.h>

#include <stdint.h>
#include <stdlib.h>

extern uint8_t* retro_audioBuffer;
extern uint32_t retro_bufferBytesRequested;
extern uint32_t retro_bufferBytesWritten;

extern MDRIVER drv_retrogame;

#endif // DRV_RETRO_GAME_H
