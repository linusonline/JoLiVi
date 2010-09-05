#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "common.h"

void appInit();
void appDeinit();
void appRender();
BOOL appTouchEvent(BOOL down);
BOOL appKeyEvent(int key_code, BOOL down);
void appOrientationEvent(short orientation);

#endif /* GAME_H_INCLUDED */
