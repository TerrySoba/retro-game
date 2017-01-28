#ifndef DRV_RETRO_GAME_H
#define DRV_RETRO_GAME_H

#include <mikmod.h>

#include <stdint.h>
#include <stdlib.h>

extern uint8_t* retro_audioBuffer;
extern size_t retro_bufferSize;
extern uint32_t retro_bufferContentLength;

extern MDRIVER drv_retrogame;

#endif // DRV_RETRO_GAME_H
