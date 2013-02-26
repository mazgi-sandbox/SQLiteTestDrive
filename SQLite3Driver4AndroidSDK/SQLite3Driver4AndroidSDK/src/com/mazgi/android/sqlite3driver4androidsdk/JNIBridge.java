package com.mazgi.android.sqlite3driver4androidsdk;

import android.util.Log;

public class JNIBridge {
	static {
		System.loadLibrary("SQLite3Driver4AndroidSDK");
	}
	public void run() {
		Log.i("SQLite3DriverAndroidSDK", "running doNothing.");
		doNothing();
		Log.i("SQLite3DriverAndroidSDK", "running sayHello.");
		Log.i("SQLite3Driver4AndroidSDK", sayHello("from Java"));
	}
	private native void doNothing();
	private native String sayHello(String msg);
}
