LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := SQLite3Driver4AndroidSDK
LOCAL_SRC_FILES := SQLite3Driver4AndroidSDK.cpp
LOCAL_SRC_FILES += ../../../ThirdParty/sqlite3/sqlite-amalgamation.current/sqlite3.c
LOCAL_SRC_FILES += ../../../common/SQLiteDriverCPP.cpp
LOCAL_C_INCLUDES := $(JNI_H_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../ThirdParty/sqlite3/sqlite-amalgamation.current
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../common

include $(BUILD_SHARED_LIBRARY)
