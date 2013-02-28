//
//  SQLiteDriverCPP.h
//  SQLiteTestDrive
//
//  Created by MATSUKI Hidenori on 2/26/13.
//  Copyright (c) 2013 Matsuki Hidenori. All rights reserved.
//

#ifndef __SQLite3Driver4iOS__SQLiteDriverCPP__
#define __SQLite3Driver4iOS__SQLiteDriverCPP__

#include <iostream>
#include "sqlite3.h"

class SQLiteDriverCPP {
    static int callback(void *self, int col_count, char **col_values, char **col_names);
public:
    void run(const char *db_file_path);
    sqlite3* open_database(const char *db_file_path);
    bool create_table(sqlite3 *db);
    bool create_record(sqlite3 *db);
    bool read_record(sqlite3 *db);
    bool update_record(sqlite3 *db);
    bool delete_record(sqlite3 *db);
private:
    void printCells(int col_count, char **col_values, char **col_names);
};

#endif /* defined(__SQLite3Driver4iOS__SQLiteDriverCPP__) */
