#include "importgl.h"
#include "common.h"
#include "app.h"
#include "game_mode.h"
#include "menu_mode.h"

static MODE current_mode = MODE_NONE;

static void startMode(MODE new_mode)
{
    debug_scope("Trace", "Starting mode: %i", new_mode);
    switch (new_mode)
    {
        case MODE_MENU:
            menu_Start();
            break;
        case MODE_GAME:
            game_Start();
            break;
        case MODE_NONE:
            // fallthrough
        default:
            break;
    }
}

void appInit(float fps)
{
    debug_scope("Trace", "Initializing native app.");
    g_globals.logic_fps = fps;
    g_globals.device_orientation = 0;
    importGLInit();
    game_Init();
    menu_Init();

    current_mode = MODE_GAME;
    startMode(current_mode);
}

void appDeinit()
{
    debug_scope("Trace", "Deinitializing native app.");
    game_DeInit();
    menu_DeInit();
    importGLDeinit();
}

void appRender()
{
    switch (current_mode)
    {
        case MODE_MENU:
            menu_Render();
            break;
        case MODE_GAME:
            game_Render();
            break;
        case MODE_NONE:
            // fallthrough
        default:
            break;
    }
}

BOOL appTouchEvent(BOOL down)
{
    debug_scope("Events", "Received touch event. Down: %s", down ? "TRUE" : "FALSE");
    switch (current_mode)
    {
        case MODE_MENU:
            return menu_TouchEvent(down);
            break;
        case MODE_GAME:
            return game_TouchEvent(down);
            break;
        case MODE_NONE:
            // fallthrough
        default:
            break;
    }
    return FALSE;
}

BOOL appKeyEvent(int key_code, BOOL down)
{
    debug_scope("Events", "Received key event. Down: %s. Key code: %i", down ? "TRUE" : "FALSE", key_code);
    return game_KeyEvent(key_code, down);
}

void appOrientationEvent(short orientation)
{
    debug_scope("Events", "Received orientation event. Orientation: %i", orientation);
    g_globals.device_orientation = orientation;
    // debug("Orientation: %i", orientation);
}

void appResizeEvent()
{
    debug_scope("Events", "Received resize event. New size: %i/%i", g_globals.window_width, g_globals.window_height);
    game_ResizeEvent();
}

void appHeartbeat()
{
    MODE next_mode = MODE_NONE;
    switch (current_mode)
    {
        case MODE_MENU:
            menu_Heartbeat();
            next_mode = menu_IsDone();
            break;
        case MODE_GAME:
            game_Heartbeat();
            next_mode = game_IsDone();
            break;
        case MODE_NONE:
            // fallthrough
        default:
            break;
    }
    if (next_mode != MODE_NONE)
    {
        current_mode = next_mode;
        startMode(current_mode);
    }
}
