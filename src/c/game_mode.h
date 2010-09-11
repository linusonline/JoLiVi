#ifndef GAME_MODE_H_INCLUDED
#define GAME_MODE_H_INCLUDED

#include "common.h"

void game_Init(float fps);
void game_DeInit();
void game_Render();
BOOL game_TouchEvent(BOOL down);
BOOL game_KeyEvent(int key_code, BOOL down);
void game_ResizeEvent();
void game_OrientationEvent(short orientation);
void game_Heartbeat();

#endif /* GAME_MODE_H_INCLUDED */
