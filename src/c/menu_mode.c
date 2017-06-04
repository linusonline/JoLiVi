#include "importgl.h"
#include "common.h"
#include "helpers.h"
#include "menu_mode.h"

static MODE next_mode = MODE_GAME;
static BOOL done = FALSE;

void menu_Init()
{
    debug_scope("Trace", "Menu initializing.");
}

void menu_Start()
{
    debug_scope("Trace", "Menu started.");
    glClearColorx(FIXED(0.0f), FIXED(0.0f), FIXED(1.0f), FIXED(1.0f));
    done = FALSE;
}

void menu_DeInit()
{
    debug_scope("Trace", "Menu deinitializing.");
}

void menu_Render()
{
    setScreenSize(g_globals.window_width, g_globals.window_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

BOOL menu_TouchEvent(BOOL down)
{
    debug_scope("Events", "Menu received touch event. Down: %s", down ? "TRUE" : "FALSE");
    if (!down)
    {
        done = TRUE;
        return TRUE;
    }
    return FALSE;
}

MODE menu_IsDone()
{
    if (done)
    {
        debug_scope("Trace", "Menu is done.");
        return next_mode;
    }
    else
    {
        return MODE_NONE;
    }
}

void menu_Heartbeat()
{
}
