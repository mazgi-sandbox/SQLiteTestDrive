LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := SQLite3Driver4AndroidSDK
LOCAL_SRC_FILES := SQLite3Driver4AndroidSDK.cpp
LOCAL_C_INCLUDES := $(JNI_H_INCLUDE)

include $(BUILD_SHARED_LIBRARY)
