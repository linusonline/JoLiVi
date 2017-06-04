#include <jni.h>
#include <android/log.h>
#include "common.h"
#include "app.h"
#include "helpers.h"

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeInit
  (JNIEnv* env, jclass clazz, jfloat fps)
{
    appInit((float)fps);
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeResize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeResize
  (JNIEnv* env, jclass clazz, jint width, jint height)
{
	setScreenSize(width, height);
    appResizeEvent();
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeRender
  (JNIEnv* env, jclass clazz)
{
    appRender();
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeDone
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeDone
  (JNIEnv* env, jclass clazz)
{
    appDeinit();
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeTouchDown
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeTouchDown
  (JNIEnv* env, jclass clazz)
{
    return appTouchEvent(TRUE);
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeTouchUp
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeTouchUp
  (JNIEnv* env, jclass clazz)
{
    return appTouchEvent(FALSE);
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeKeyDown
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeKeyDown
  (JNIEnv* env, jclass clazz, jint keyCode)
{
    return appKeyEvent(keyCode, TRUE);
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeKeyUp
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeKeyUp
  (JNIEnv* env, jclass clazz, jint keyCode)
{
    return appKeyEvent(keyCode, FALSE);
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeOrientationChange
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeOrientationChange
  (JNIEnv* env, jclass clazz, jint orientation)
{
    appOrientationEvent((short)orientation);
}

/*
 * Class:     se_lolektivet_jolivi_NativeFunctions
 * Method:    nativeHeartbeat
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_se_lolektivet_jolivi_NativeFunctions_nativeHeartbeat
  (JNIEnv* env, jclass clazz)
{
    appHeartbeat();
}
