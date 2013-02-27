#include "SQLite3Driver4AndroidSDK.h"
#include "SQLiteDriverCPP.h"
#include <android/log.h>

JNIEXPORT void JNICALL Java_com_mazgi_android_sqlite3driver4androidsdk_JNIBridge_doNothing(JNIEnv *env, jobject self) {
}

JNIEXPORT jstring JNICALL Java_com_mazgi_android_sqlite3driver4androidsdk_JNIBridge_sayHello(JNIEnv *env, jobject self, jstring jMsg) {
	return env->NewStringUTF("Hello");
}

JNIEXPORT void JNICALL Java_com_mazgi_android_sqlite3driver4androidsdk_JNIBridge_callSQLite3Driver(JNIEnv *env, jobject self, jstring jPath) {
	__android_log_print(ANDROID_LOG_INFO, "SQLite3Driver4AndroidSDK", "%d:in %s", __LINE__, __PRETTY_FUNCTION__);
	const char *path = env->GetStringUTFChars(jPath, 0);
	__android_log_print(ANDROID_LOG_INFO, "SQLite3Driver4AndroidSDK", "%d:path=>%s", __LINE__, path);
    SQLiteDriverCPP *cppDriver = new SQLiteDriverCPP();
    cppDriver->run(path);
	__android_log_print(ANDROID_LOG_INFO, "SQLite3Driver4AndroidSDK", "%d:out %s", __LINE__, __PRETTY_FUNCTION__);
}
