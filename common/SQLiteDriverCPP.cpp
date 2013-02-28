//
//  SQLiteDriverCPP.cpp
//  SQLiteTestDrive
//
//  Created by MATSUKI Hidenori on 2/26/13.
//  Copyright (c) 2013 Matsuki Hidenori. All rights reserved.
//

#include "SQLiteDriverCPP.h"

static const char *TABLE_NAME = "SAMPLE_TABLE";
static const char *DDL_TABLE_CREATE_FORMAT =
"CREATE TABLE %s("
"ID INTEGER PRIMARY KEY,"
"MESSAGE TEXT"
");";
static const char *DML_CREATE_FORMAT = "INSERT INTO %s VALUES(%d, %Q);";
static const char *DML_CREATE_PREPARE_FORMAT = "INSERT INTO %s VALUES(?, ?);";
static const char *DML_READ_FORMAT = "SELECT ID, MESSAGE FROM %s WHERE ID=%d;";
static const char *DML_READ_PREPARE_FORMAT = "SELECT ID, MESSAGE FROM %s WHERE ID=?;";
static const char *DML_UPDATE_FORMAT = "UPDATE %s SET MESSAGE=%Q WHERE ID=%d;";
static const char *DML_DELETE_FORMAT = "DELETE FROM %s WHERE ID=%d;";

void SQLiteDriverCPP::printCells(int col_count, char **col_values, char **col_names)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    for (int i = 0; i < col_count; i++) {
        fprintf(stdout, "%05d:[info]%s|%s\n", __LINE__, col_names[i], col_values[i]);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
}

int SQLiteDriverCPP::callback(void *self, int col_count, char **col_values, char **col_names)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    SQLiteDriverCPP* driver=static_cast<SQLiteDriverCPP*>(self);
    driver->printCells(col_count, col_values, col_names);
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    
    //If an sqlite3_exec() callback returns non-zero, the sqlite3_exec() routine returns SQLITE_ABORT without invoking the callback again and without running any subsequent SQL statements.
    return 0;
}

void SQLiteDriverCPP::run(const char *db_file_path)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    sqlite3 *db = open_database(db_file_path);
    if (db) {
        bool success = create_table(db);
        if (success) {
            success &= create_record(db);
        }
        if (success) {
            success &= read_record(db);
        }
        if (success) {
            success &= update_record(db);
        }
        if (success) {
            success &= delete_record(db);
        }
    }
    //openに失敗してもcloseする必要があります.
    sqlite3_close(db);
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
}

sqlite3* SQLiteDriverCPP::open_database(const char *db_file_path)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    sqlite3 *db = NULL;
    int result_code = sqlite3_open_v2(db_file_path, &db, SQLITE_OPEN_CREATE|SQLITE_OPEN_READWRITE, NULL);
    if (result_code != SQLITE_OK) {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db));
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    return db;
}

bool SQLiteDriverCPP::create_table(sqlite3 *db)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    int result_code = SQLITE_OK;
    char *errmsg = NULL;
    char *query = sqlite3_mprintf(DDL_TABLE_CREATE_FORMAT, TABLE_NAME);
    fprintf(stdout, "%05d:[info]query=>%s\n", __LINE__, query);
    result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
    sqlite3_free(query);
    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s, function_msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db), errmsg);
        sqlite3_free(errmsg);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    return result_code == SQLITE_OK;
}
bool SQLiteDriverCPP::create_record(sqlite3 *db)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    int result_code = SQLITE_OK;
    char *errmsg = NULL;
    char *query = sqlite3_mprintf(DML_CREATE_FORMAT, TABLE_NAME, 1, "insert");
    fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
    result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
    sqlite3_free(query);
    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s, function_msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db), errmsg);
        sqlite3_free(errmsg);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    return result_code == SQLITE_OK;
}
bool SQLiteDriverCPP::read_record(sqlite3 *db)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    int result_code = SQLITE_OK;
    char *errmsg = NULL;
    char *query = sqlite3_mprintf(DML_READ_FORMAT, TABLE_NAME, 1);
    fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
    result_code = sqlite3_exec(db, query, &(SQLiteDriverCPP::callback), NULL, &errmsg);
    sqlite3_free(query);
    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s, function_msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db), errmsg);
        sqlite3_free(errmsg);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    return result_code == SQLITE_OK;
}
bool SQLiteDriverCPP::update_record(sqlite3 *db)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    int result_code = SQLITE_OK;
    char *errmsg = NULL;
    char *query = sqlite3_mprintf(DML_UPDATE_FORMAT, TABLE_NAME, "update", 1);
    fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
    result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
    sqlite3_free(query);
    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s, function_msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db), errmsg);
        sqlite3_free(errmsg);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    return result_code == SQLITE_OK;
}
bool SQLiteDriverCPP::delete_record(sqlite3 *db)
{
    fprintf(stdout, "%05d:[info]in %s.\n", __LINE__, __PRETTY_FUNCTION__);
    int result_code = SQLITE_OK;
    char *errmsg = NULL;
    char *query = sqlite3_mprintf(DML_DELETE_FORMAT, TABLE_NAME, 1);
    fprintf(stdout, "%05d:[info]%s\n", __LINE__, query);
    result_code = sqlite3_exec(db, query, NULL, NULL, &errmsg);
    sqlite3_free(query);
    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "%05d:[err]code=>%d, msg=>%s, function_msg=>%s\n", __LINE__, sqlite3_errcode(db), sqlite3_errmsg(db), errmsg);
        sqlite3_free(errmsg);
    }
    fprintf(stdout, "%05d:[info]out %s.\n", __LINE__, __PRETTY_FUNCTION__);
    return result_code == SQLITE_OK;
}
