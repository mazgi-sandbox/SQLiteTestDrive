//
//  SQLiteDriverCPP.cpp
//  SQLiteTestDrive
//
//  Created by MATSUKI Hidenori on 2/26/13.
//  Copyright (c) 2013 Matsuki Hidenori. All rights reserved.
//

#include "SQLiteDriverCPP.h"
#include <sys/stat.h>

void SQLiteDriverCPP::run(const char *db_file_path)
{
    const char *TABLE_NAME = "SAMPLE_TABLE";
    const char *DDL_TABLE_CREATE_FORMAT =
    "CREATE TABLE %s("
    "ID INTEGER PRIMARY KEY,"
    "MESSAGE TEXT"
    ");";
    const char *DML_CREATE_FORMAT = "INSERT INTO %s VALUES(%Q, %Q);";
    const char *DML_CREATE_PREPARE_FORMAT = "INSERT INTO %s VALUES(?, ?);";
    const char *DML_READ_FORMAT = "SELECT ID, MESSAGE FROM %s WHERE ID=%Q;";
    const char *DML_READ_PREPARE_FORMAT = "SELECT ID, MESSAGE FROM %s WHERE ID=?;";
    const char *DML_UPDATE_FORMAT = "UPDATE %s SET MESSAGE=%Q WHERE ID=%Q;";
    const char *DML_DELETE_FORMAT = "DELETE FROM %s WHERE ID=%Q;";
    
    int result_code = SQLITE_OK;
    sqlite3 *db = NULL;
    
    //既存ファイル削除
    struct stat st;
    if (stat(db_file_path, &st)) {
        if (remove(db_file_path))
        {
            fprintf(stdout, "%05d:[info]Delete %s.\n", __LINE__, db_file_path);
        } else {
            fprintf(stderr, "%05d:[err]Cannot delete %s.\n", __LINE__, db_file_path);
            return;
        }
    }
    
    /*-------
     | open |
     -------*/
    //sqlite3_openはfilenameがUTF-8, sqlite3_open16はfilenameがUTF-16です.
    result_code = sqlite3_open_v2(db_file_path, &db, SQLITE_OPEN_CREATE|SQLITE_OPEN_READWRITE, NULL);
    //openに失敗してもcloseする必要があります.
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*---------
     | define |
     ---------*/
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DDL_TABLE_CREATE_FORMAT, TABLE_NAME);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    
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