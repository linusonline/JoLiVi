V=1

#LOCAL_PATH := $(call my-dir)/src/jni
LOCAL_PATH := $(shell cygpath "$(call my-dir)/../src/c")
#LOCAL_PATH := /cygdrive/d/Pyssel/Koda/jolivi/src/jni

$(info Local path is: '$(LOCAL_PATH)')

include $(CLEAR_VARS)

LOCAL_MODULE := jolivi

LOCAL_CFLAGS := -DANDROID_NDK -Wall -pedantic -std=c99 -Wno-variadic-macros \
                -DDISABLE_IMPORTGL

LOCAL_ALLOW_UNDEFINED_SYMBOLS := false

LOCAL_SRC_FILES := \
    importgl.c \
	se_lolektivet_jolivi.c \
	helpers.c \
	game.c

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog

include $(BUILD_SHARED_LIBRARY)
