//
//  SQLiteDriverCPP.cpp
//  SQLiteTestDrive
//
//  Created by MATSUKI Hidenori on 2/26/13.
//  Copyright (c) 2013 Matsuki Hidenori. All rights reserved.
//

#include "SQLiteDriverCPP.h"
#include <sys/stat.h>

int SQLiteDriverCPP::callback(void *not_use, int col_count, char **col_values, char **col_names)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    for (int i = 0; i < col_count; i++) {
        fprintf(stdout, "%05d:[info]%s|%s\n", __LINE__, col_names[i], col_values[i]);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    
    //If an sqlite3_exec() callback returns non-zero, the sqlite3_exec() routine returns SQLITE_ABORT without invoking the callback again and without running any subsequent SQL statements.
    return 0;
}

void SQLiteDriverCPP::run(const char *db_file_path)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    
    const char *TABLE_NAME = "SAMPLE_TABLE";
    const char *DDL_TABLE_CREATE_FORMAT =
    "CREATE TABLE %s("
    "ID INTEGER PRIMARY KEY,"
    "MESSAGE TEXT"
    ");";
    const char *DML_CREATE_FORMAT = "INSERT INTO %s VALUES(%d, %Q);";
    const char *DML_CREATE_PREPARE_FORMAT = "INSERT INTO %s VALUES(?, ?);";
    const char *DML_READ_FORMAT = "SELECT ID, MESSAGE FROM %s WHERE ID=%d;";
    const char *DML_READ_PREPARE_FORMAT = "SELECT ID, MESSAGE FROM %s WHERE ID=?;";
    const char *DML_UPDATE_FORMAT = "UPDATE %s SET MESSAGE=%Q WHERE ID=%d;";
    const char *DML_DELETE_FORMAT = "DELETE FROM %s WHERE ID=%d;";
    
    int result_code = SQLITE_OK;
    sqlite3 *db = NULL;
    
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
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    
    /*-----------------
     | create && read |
     -----------------*/
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DML_CREATE_FORMAT, TABLE_NAME, 1, "insert");
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    if (result_code != SQLITE_OK) goto close_and_return;
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DML_READ_FORMAT, TABLE_NAME, 1);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, &(SQLiteDriverCPP::callback), NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*-----------------
     | update && read |
     -----------------*/
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DML_UPDATE_FORMAT, TABLE_NAME, "update", 1);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    if (result_code != SQLITE_OK) goto close_and_return;
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DML_READ_FORMAT, TABLE_NAME, 1);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, &(SQLiteDriverCPP::callback), NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    if (result_code != SQLITE_OK) goto close_and_return;
    
    /*-----------------
     | delete && read |
     -----------------*/
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DML_DELETE_FORMAT, TABLE_NAME, 1);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    if (result_code != SQLITE_OK) goto close_and_return;
    {
        char *errmsg = NULL;
        char *query = sqlite3_mprintf(DML_READ_FORMAT, TABLE_NAME, 1);
        fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
        result_code = sqlite3_exec(db, query, &(SQLiteDriverCPP::callback), NULL, &errmsg);
        sqlite3_free(query);
        if (result_code != SQLITE_OK)
        {
            fprintf(stderr, "%05d:[err]exec_errmsg=>%s, code=>%d, msg=>%s\n", __LINE__, errmsg, sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_free(errmsg);
            goto close_and_return;
        }
    }
    if (result_code != SQLITE_OK) goto close_and_return;

close_and_return:
    //close
    if (result_code != SQLITE_OK) {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db));
    }
    sqlite3_close(db);
    
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
}