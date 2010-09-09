#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdarg.h>
#include <android/log.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a < b ? b : a)

typedef struct Globals {
    short g_window_width;
    short g_window_height;
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
