package com.mazgi.android.sqlite3driver4androidsdk;

import java.io.File;

import android.util.Log;

public class JNIBridge {
	private File filesDir = null;
	static {
		System.loadLibrary("SQLite3Driver4AndroidSDK");
	}
	private File getFilesDir() {
		return filesDir;
	}
	public void setFilesDir(File databaseFile) {
		this.filesDir = databaseFile;
	}
	public void run() {
		Log.i("SQLite3DriverAndroidSDK", "running doNothing.");
		doNothing();
		Log.i("SQLite3DriverAndroidSDK", "running sayHello.");
		Log.i("SQLite3Driver4AndroidSDK", sayHello("from Java"));
		
		Log.i("SQLite3DriverAndroidSDK", "running callSQLite3Driver.");
		String path = getFilesDir().toString() + "/sample.sqlite3";
		Log.i("SQLite3DriverAndroidSDK", "database file path=>" + path);
		File old = new File(path);
		if (old.exists()) {
			Log.i("SQLite3DriverAndroidSDK", "deleting old database file...");
			old.delete();
		}
		callSQLite3Driver(path);
	}
	private native void doNothing();
	private native String sayHello(String msg);
	private native void callSQLite3Driver(String path);
}
