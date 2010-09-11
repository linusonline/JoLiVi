#include "app.h"
#include "game_mode.h"

void appInit(float fps)
{
    debug("Initializing native app.");
    game_Init(fps);
}

void appDeinit()
{
    game_DeInit();
}

void appRender()
{
    game_Render();
}

BOOL appTouchEvent(BOOL down)
{
    return game_TouchEvent(down);
}

BOOL appKeyEvent(int key_code, BOOL down)
{
    return game_KeyEvent(key_code, down);
}

void appOrientationEvent(short orientation)
{
    g_globals.device_orientation = orientation;
    // debug("Orientation: %i", orientation);
}

void appResizeEvent()
{
    game_ResizeEvent();
}

void appHeartbeat()
{
    game_Heartbeat();
}
