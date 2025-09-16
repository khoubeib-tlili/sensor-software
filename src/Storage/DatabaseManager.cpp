#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const char* path)
    : _path(path), _db(nullptr) 
{}

DatabaseManager::~DatabaseManager() {
    close();
}

bool DatabaseManager::open() {
    int rc = sqlite3_open(_path, &_db);
    if (rc != SQLITE_OK) {
        Serial.print("Failed to open DB: ");
        Serial.println(sqlite3_errmsg(_db));
        _db = nullptr;
        return false;
    }
    return true;
}

void DatabaseManager::close() {
    if (_db) {
        sqlite3_close(_db);
        _db = nullptr;
    }
}

bool DatabaseManager::exec(const char* sql, int (*callback)(void*, int, char**, char**), void* data) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(_db, sql, callback, data, &errMsg);
    if (rc != SQLITE_OK) {
        Serial.print("SQL error: ");
        Serial.println(errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool DatabaseManager::createTable(const char* sql) {
    return exec(sql);
}

bool DatabaseManager::isOpen() const {
    return _db != nullptr;
}

sqlite3* DatabaseManager::getDb() {
    return _db;
}