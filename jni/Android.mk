# Copyright 2006 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	rild.c


LOCAL_LDLIBS := -llog

LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE:= nvram

include $(BUILD_EXECUTABLE)