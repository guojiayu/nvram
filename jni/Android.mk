LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    nvram.cpp \

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

LOCAL_CFLAGS += -Wno-unused-parameter

LOCAL_MODULE:= nvram
LOCAL_CLANG := true
LOCAL_SANITIZE := integer

include $(BUILD_SHARED_LIBRARY)


# =========================================
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	nvram.c

LOCAL_SHARED_LIBRARIES := \
	libnvram \

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

LOCAL_MODULE:= nvramd

include $(BUILD_EXECUTABLE)