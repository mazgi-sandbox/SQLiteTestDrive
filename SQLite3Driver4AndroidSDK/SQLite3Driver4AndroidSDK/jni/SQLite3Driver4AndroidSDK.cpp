#include "SQLite3Driver4AndroidSDK.h"
#include "SQLiteDriverCPP.h"

JNIEXPORT void JNICALL Java_com_mazgi_android_sqlite3driver4androidsdk_JNIBridge_doNothing(JNIEnv *env, jobject) {
}

JNIEXPORT jstring JNICALL Java_com_mazgi_android_sqlite3driver4androidsdk_JNIBridge_sayHello(JNIEnv *env, jobject, jstring) {
	return env->NewStringUTF("Hello");
}

JNIEXPORT void JNICALL Java_com_mazgi_android_sqlite3driver4androidsdk_JNIBridge_callSQLite3Driver(JNIEnv *env, jobject, jstring) {
    SQLiteDriverCPP *cppDriver = new SQLiteDriverCPP();
    cppDriver->run("");
}
