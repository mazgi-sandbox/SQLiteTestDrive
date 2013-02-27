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
    static int callback(void *not_use, int col_count, char **col_values, char **col_names);
public:
    void run(const char *db_file_path);
};

#endif /* defined(__SQLite3Driver4iOS__SQLiteDriverCPP__) */
