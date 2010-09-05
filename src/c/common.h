#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct Globals {
    short g_window_width;
    short g_window_height;
} Globals;

extern Globals g_globals;

#endif /* COMMON_H_INCLUDED */
