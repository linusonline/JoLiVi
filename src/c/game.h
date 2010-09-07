#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "common.h"

void appInit(float fps);
void appDeinit();
void appRender();
BOOL appTouchEvent(BOOL down);
BOOL appKeyEvent(int key_code, BOOL down);
void appResizeEvent();
void appOrientationEvent(short orientation);
void appHeartbeat();

#endif /* GAME_H_INCLUDED */
