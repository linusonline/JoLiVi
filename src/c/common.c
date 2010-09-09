#include "common.h"

Globals g_globals;

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
    __android_log_vprint(ANDROID_LOG_VERBOSE, scope, fmt, args);
    va_end(args);
}
