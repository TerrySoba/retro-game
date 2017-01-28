#ifndef DRV_RETRO_GAME_H
#define DRV_RETRO_GAME_H

#include <mikmod.h>

#include <stdint.h>

extern uint8_t* retro_audioBuffer;
extern uint32_t retro_bufferPos;
extern uint32_t retro_bufferSize;

extern MDRIVER drv_retrogame;

#endif // DRV_RETRO_GAME_H
