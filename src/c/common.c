#include <string.h>
#include "common.h"

Globals g_globals;
static const char* debug_events = "Events";
static const char* debug_trace = "Trace";
static const BOOL debug_events_on = FALSE;
static const BOOL debug_trace_on = TRUE;

void ifloat_setTo(ifloat* self, int value)
{
    self->a = value;
    self->b = value;
}

void ifloat_moveTo(ifloat* self, int value)
{
    self->a = self->b;
    self->b = value;
}

#ifdef DEBUG
void debug(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_VERBOSE, "JOLIVI", fmt, args);
    va_end(args);
}
void debug_scope(const char* scope, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (debug_events_on && strcmp(scope, debug_events))
    {
        __android_log_vprint(ANDROID_LOG_VERBOSE, "JOLIVI:Events", fmt, args);
    }
    else if (debug_trace_on && strcmp(scope, debug_trace))
    {
        __android_log_vprint(ANDROID_LOG_VERBOSE, "JOLIVI:Trace", fmt, args);
    }
    else
    {
        __android_log_vprint(ANDROID_LOG_VERBOSE, scope, fmt, args);
    }

    va_end(args);
}
#endif
