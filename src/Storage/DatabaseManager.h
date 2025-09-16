#pragma once
#include <sqlite3.h>
#include <Arduino.h>
#include "Utilities/ErrorManager.h"

class DatabaseManager {
public:
    DatabaseManager(const char* path);
    ~DatabaseManager();
    bool open();
    void close();
    bool exec(const char* sql, int (*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
    bool createTable(const char* sql);
    bool isOpen() const;
    sqlite3* getDb();
private:
    const char* _path;
    sqlite3* _db;
    
};