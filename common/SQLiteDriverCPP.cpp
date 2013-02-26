//
//  SQLiteDriverCPP.cpp
//  SQLiteTestDrive
//
//  Created by MATSUKI Hidenori on 2/26/13.
//  Copyright (c) 2013 Matsuki Hidenori. All rights reserved.
//

#include "SQLiteDriverCPP.h"

void SQLiteDriverCPP::run()
{
    const char *DDL_TABLE_CREATE =
    "CREATE TABLE SAMPLE_TABLE("
    "ID INTEGER PRIMARY KEY,"
    "MESSAGE TEXT"
    ");";
    const char *DML_CREATE = "INSERT INTO SAMPLE_TABLE VALUES(?, ?);";
    const char *DML_READ = "SELECT ID, MESSAGE FROM SAMPLE_TABLE WHERE ID=?;";
    const char *DML_UPDATE = "UPDATE SAMPLE_TABLE SET MESSAGE=? WHERE ID=?;";
    const char *DML_DELETE = "DELETE FROM SAMPLE_TABLE WHERE ID=?;";
    
    int result_code = SQLITE_OK;
    sqlite3 *db = NULL;
    
    //TODO: 既存ファイル削除
    
    /*-------
     | open |
     -------*/
    //sqlite3_openはfilenameがUTF-8, sqlite3_open16はfilenameがUTF-16です.
    result_code = sqlite3_open_v2("sample.db", &db, SQLITE_OPEN_CREATE|SQLITE_OPEN_READWRITE, NULL);
    //openに失敗してもcloseする必要があります.
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*---------
     | define |
     ---------*/
    {
        sqlite3_stmt *stmt = NULL;
        result_code = sqlite3_prepare_v2(db, DDL_TABLE_CREATE, -1, &stmt, NULL);
        sqlite3_finalize(stmt);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, DDL_TABLE_CREATE);
    }
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*-----------------
     | create && read |
     -----------------*/
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*-----------------
     | update && read |
     -----------------*/
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*-----------------
     | delete && read |
     -----------------*/
    if (result_code != SQLITE_OK) goto close_and_return;

close_and_return:
    //close
    if (result_code != SQLITE_OK) {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db));
    }
    sqlite3_close(db);
}