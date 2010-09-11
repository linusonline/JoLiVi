#include <stdlib.h>
#include "importgl.h"
#include "helpers.h"
#include "common.h"
#include "game_mode.h"

#define CONTROL_METHOD_UNDETERMINED -1
#define CONTROL_METHOD_TILT 1
#define CONTROL_METHOD_DPAD 2
#define CONTROL_METHOD_TOUCH 3

#define CONTROL_TILT_LEFT_THRESHHOLD 260
#define CONTROL_TILT_RIGHT_THRESHHOLD 280
#define CONTROL_TILT_LEFT_LIMIT 180
#define CONTROL_TILT_RIGHT_LIMIT 360

#define MOVE_NONE 0                     // 0x00000000
#define MOVE_LEFT 1                     // 0x00000001
#define MOVE_RIGHT 2                    // 0x00000010
#define MOVE_LEFT_TAKES_PRECEDENCE 4    // 0x00000100

/** Types **/

typedef struct Block {
    GlObject* gl_object;
    float pos_x;
    float pos_y;
} Block;

typedef struct Avatar {
    GlObject* gl_object;
    ifloat pos_x;
    float pos_y;
    float size;
    char movement;
    float speed; // pixels per second
} Avatar;

/** File-scoped variables **/

static short control_method = CONTROL_METHOD_TILT;
static int keys_pressed = 0;
static short block_size = 50;
static short blocks_wide = 12;
static short play_area_offset_x = 0;
static const float avatar_speed = 200.0f;
static float avatar_max_left = 0;
static float avatar_max_right = 430;
static float logic_fps;
static Avatar* the_square = NULL;
static Block* floor = NULL;

/** Predeclarations of static functions **/

static GlObject* newSquare(float x, float y, float width, float height, RGBA color_bl, RGBA color_br, RGBA color_tr, RGBA color_tl);
static void GlObject_setColor(GlObject* self, RGBA color_bl, RGBA color_br, RGBA color_tr, RGBA color_tl);
static Block* Block_new(float pos_x, float pos_y);
static void Block_delete(Block* self);
static void Avatar_delete(Avatar* self);
static Avatar* Avatar_new();
void createFloor();

/** Functions **/

GlObject* newSquare(float x, float y, float width, float height, RGBA color_bl, RGBA color_br, RGBA color_tr, RGBA color_tl)
{
    GlObject* square;
    square = (GlObject*)malloc(sizeof(GlObject));
    square->count = 6;
    square->vertexComponents = 2;
    square->vertexArray = (GLfixed*)malloc(12 * sizeof(GLfixed));
    square->colorArray = (GLubyte*)malloc(24 * sizeof(GLubyte));
    square->vertexArray[0] = FIXED(x);
    square->vertexArray[1] = FIXED(y);

    square->vertexArray[2] = FIXED(x+width);
    square->vertexArray[3] = FIXED(y);

    square->vertexArray[4] = FIXED(x+width);
    square->vertexArray[5] = FIXED(y+height);

    square->vertexArray[6] = FIXED(x+width);
    square->vertexArray[7] = FIXED(y+height);

    square->vertexArray[8] = FIXED(x);
    square->vertexArray[9] = FIXED(y+height);

    square->vertexArray[10] = FIXED(x);
    square->vertexArray[11] = FIXED(y);

    GlObject_setColor(square, color_bl, color_br, color_tr, color_tl);
    square->normalArray = NULL;
    return square;
}

void GlObject_setColor(GlObject* self, RGBA color_bl, RGBA color_br, RGBA color_tr, RGBA color_tl)
{
    self->colorArray[0] = RGBA_r(color_bl);
    self->colorArray[1] = RGBA_g(color_bl);
    self->colorArray[2] = RGBA_b(color_bl);
    self->colorArray[3] = RGBA_a(color_bl);

    self->colorArray[4] = RGBA_r(color_br);
    self->colorArray[5] = RGBA_g(color_br);
    self->colorArray[6] = RGBA_b(color_br);
    self->colorArray[7] = RGBA_a(color_br);

    self->colorArray[8] = RGBA_r(color_tr);
    self->colorArray[9] = RGBA_g(color_tr);
    self->colorArray[10] = RGBA_b(color_tr);
    self->colorArray[11] = RGBA_a(color_tr);

    self->colorArray[12] = RGBA_r(color_tr);
    self->colorArray[13] = RGBA_g(color_tr);
    self->colorArray[14] = RGBA_b(color_tr);
    self->colorArray[15] = RGBA_a(color_tr);

    self->colorArray[16] = RGBA_r(color_tl);
    self->colorArray[17] = RGBA_g(color_tl);
    self->colorArray[18] = RGBA_b(color_tl);
    self->colorArray[19] = RGBA_a(color_tl);

    self->colorArray[20] = RGBA_r(color_bl);
    self->colorArray[21] = RGBA_g(color_bl);
    self->colorArray[22] = RGBA_b(color_bl);
    self->colorArray[23] = RGBA_a(color_bl);
}

Block* Block_new(float pos_x, float pos_y)
{
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->gl_object = newSquare(pos_x, pos_y, block_size, block_size, RGBA3(255,0,0), RGBA3(255,255,0), RGBA3(0,255,0),RGBA3(0,0,255));
    new_block->pos_x = pos_x;
    new_block->pos_y = pos_y;
    return new_block;
}

void Block_delete(Block* self)
{
    freeGLObject(self->gl_object);
    free(self);
}

void Avatar_delete(Avatar* self)
{
    freeGLObject(self->gl_object);
    free(self);
}

Avatar* Avatar_new()
{
    Avatar* new_avatar = (Avatar*)malloc(sizeof(Avatar));
    new_avatar->size = block_size;
    ifloat_setTo(&new_avatar->pos_x, 0);
    new_avatar->pos_y = block_size;
    new_avatar->gl_object = newSquare(new_avatar->pos_x.a, new_avatar->pos_y, new_avatar->size, new_avatar->size,
                                      RGBA3(255,255,255), RGBA3(255,255,255), RGBA3(255,255,255), RGBA3(255,255,255));
    new_avatar->movement = 0;
    new_avatar->speed = 0;
    return new_avatar;
}

void createFloor()
{
    int i;
    floor = (Block*)malloc(sizeof(Block) * blocks_wide);
    for (i = 0; i < blocks_wide; ++i)
    {
        floor[i].gl_object = newSquare(play_area_offset_x + i*block_size, 0, block_size, block_size, RGBA3(255,0,0), RGBA3(255,255,0), RGBA3(0,255,0),RGBA3(0,0,255));
    }
}

void game_Init(float fps)
{
    debug("Initializing native app.");
    logic_fps = fps;
    importGLInit();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glClearColorx(FIXED(1.0f), FIXED(0.0f), FIXED(0.0f), FIXED(1.0f));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    block_size = g_globals.window_width / blocks_wide;
    play_area_offset_x = (g_globals.window_width - blocks_wide * block_size) / 2;

    the_square = Avatar_new();
    createFloor();
}

void game_DeInit()
{
    Avatar_delete(the_square);
    importGLDeinit();
}

void game_Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setScreenSize(g_globals.window_width, g_globals.window_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatex(FIXED(the_square->pos_x.b), FIXED(0.0f), FIXED(0.0f));
    drawGLObject(the_square->gl_object);
    glPopMatrix();

    int i;
    for (i = 0; i < blocks_wide; ++i)
    {
        drawGLObject(floor[i].gl_object);
    }
}

BOOL game_TouchEvent(BOOL down)
{
    if (down)
    {
        GlObject_setColor(the_square->gl_object, RGBA3(0,0,0), RGBA3(0,0,0), RGBA3(0,0,0), RGBA3(0,0,0));
    }
    else
    {
        GlObject_setColor(the_square->gl_object, RGBA3(255,255,255), RGBA3(255,255,255), RGBA3(255,255,255), RGBA3(255,255,255));
    }
    return TRUE;
}

BOOL game_KeyEvent(int key_code, BOOL down)
{
    switch(key_code)
    {
        case KEYCODE_DPAD_LEFT:
            if (down)
            {
                keys_pressed |= MOVE_LEFT;
                keys_pressed |= MOVE_LEFT_TAKES_PRECEDENCE;
            }
            else
            {
                keys_pressed &= ~MOVE_LEFT;
                keys_pressed &= ~MOVE_LEFT_TAKES_PRECEDENCE;
            }
            break;
        case KEYCODE_DPAD_RIGHT:
            if (down)
            {
                keys_pressed |= MOVE_RIGHT;
                keys_pressed &= ~MOVE_LEFT_TAKES_PRECEDENCE;
            }
            else
            {
                keys_pressed &= ~MOVE_RIGHT;
                keys_pressed |= MOVE_LEFT_TAKES_PRECEDENCE;
            }
            break;
        default:
            return FALSE;
            break;
    }
    return TRUE;
}

void game_OrientationEvent(short orientation)
{
    // device_orientation = orientation;
    // debug("Orientation: %i", orientation);
}

void game_ResizeEvent()
{
    avatar_max_right = g_globals.window_width - the_square->size;
}

void game_Heartbeat()
{
    switch (control_method)
    {
        case CONTROL_METHOD_TILT:
        {
            if (g_globals.device_orientation < CONTROL_TILT_LEFT_THRESHHOLD && g_globals.device_orientation > CONTROL_TILT_LEFT_LIMIT)
            {
                the_square->speed = -avatar_speed;
            }
            else if (g_globals.device_orientation > CONTROL_TILT_RIGHT_THRESHHOLD && g_globals.device_orientation < CONTROL_TILT_RIGHT_LIMIT)
            {
                the_square->speed = avatar_speed;
            }
            else
            {
                the_square->speed = 0.0f;
            }
        }
        break;
        case CONTROL_METHOD_TOUCH:
        {
        }
        break;
        case CONTROL_METHOD_UNDETERMINED:
        //fallthrough
        case CONTROL_METHOD_DPAD:
        {
            if (keys_pressed & MOVE_LEFT && keys_pressed & MOVE_LEFT_TAKES_PRECEDENCE)
            {
                the_square->speed = -avatar_speed;
            }
            else if (keys_pressed & MOVE_RIGHT && !(keys_pressed & MOVE_LEFT_TAKES_PRECEDENCE))
            {
                the_square->speed = avatar_speed;
            }
            else
            {
                the_square->speed = 0.0f;
            }
        }
        break;
        default:
            debug_scope("ERROR", "Unknown control_method!");
    }
    ifloat_moveTo(&(the_square->pos_x), MAX(MIN(the_square->pos_x.b + the_square->speed / logic_fps, avatar_max_right), avatar_max_left));
    // debug("Speed: %f, Position: %f", the_square->speed, the_square->pos_x.b);
}
