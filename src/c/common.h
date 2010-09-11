#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdarg.h>
#include <android/log.h>

/* Very general stuff */

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a < b ? b : a)

/* Types **/

typedef struct ifloat {
    float a;
    float b;
} ifloat;

void ifloat_setTo(ifloat* self, int value);
void ifloat_moveTo(ifloat* self, int value);

typedef unsigned int RGBA;

#define RGBA4(r, g, b, a) ((r << 24) + (g << 16) + (b << 8) + a)
#define RGBA3(r, g, b) ((r << 24) + (g << 16) + (b << 8) + 0xFF)
#define RGBA_r(rgba) (rgba >> 24)
#define RGBA_g(rgba) ((rgba & 0xFF0000) >> 16)
#define RGBA_b(rgba) ((rgba & 0xFF00) >> 8)
#define RGBA_a(rgba) (rgba & 0XFF)

#define KEYCODE_DPAD_UP 0x00000013
#define KEYCODE_DPAD_DOWN 0x00000014
#define KEYCODE_DPAD_LEFT 0x00000015
#define KEYCODE_DPAD_RIGHT 0x00000016

typedef struct Globals {
    short window_width;
    short window_height;
    short device_orientation;
} Globals;

extern Globals g_globals;

#ifdef DEBUG
void debug(const char* fmt, ...);
void debug_scope(const char* scope, const char* fmt, ...);
#else
# define debug(fmt, ...) do {} while (FALSE)
# define debug_scope(scope, fmt, ...) do {} while (FALSE)
#endif

#endif /* COMMON_H_INCLUDED */
