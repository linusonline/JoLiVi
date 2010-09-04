#include <jni.h>
#include "game.h"
// #include <importgl.h>
// #include <sys/time.h>
// #include <time.h>
#include <android/log.h>
// #include <stdint.h>
#include "helpers.h"

static int  g_window_width  = 320;
static int  g_window_height = 480;

/*
 * Class:     se_lolektivet_jolivi_DemoRenderer
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_DemoRenderer_nativeInit
  (JNIEnv* env, jclass clazz)
{
    appInit();
}

/*
 * Class:     se_lolektivet_jolivi_DemoRenderer
 * Method:    nativeResize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_DemoRenderer_nativeResize
  (JNIEnv* env, jclass clazz, jint width, jint height)
{
    g_window_width  = width;
    g_window_height = height;
    __android_log_print(ANDROID_LOG_INFO, "SanAngeles", "resize w=%d h=%d", width, height);
	setScreenSize(width, height);
}

/*
 * Class:     se_lolektivet_jolivi_DemoRenderer
 * Method:    nativeRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_DemoRenderer_nativeRender
  (JNIEnv* env, jclass clazz)
{
    appRender(g_window_width, g_window_height);
}

/*
 * Class:     se_lolektivet_jolivi_DemoRenderer
 * Method:    nativeDone
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_DemoRenderer_nativeDone
  (JNIEnv* env, jclass clazz)
{
    appDeinit();
}
