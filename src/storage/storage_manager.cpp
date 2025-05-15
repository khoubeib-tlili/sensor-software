#include "storage_manager.h"
#include "../utilities/error_handler.h"

bool StorageManager::begin(uint8_t csPin) {
    if(!SD.begin(csPin)) return false;
    
    int rc = sqlite3_open("/sd/sensors.db", &db);
    if(rc != SQLITE_OK) {
        logError(ERR_SQLITE, sqlite3_errmsg(db));
        return false;
    }
    
    const char* sql = 
        "CREATE TABLE IF NOT EXISTS sensor_data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "sensor_id TEXT NOT NULL,"
        "value REAL NOT NULL,"
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "sent BOOLEAN DEFAULT 0)";
        
    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if(rc != SQLITE_OK) {
        logError(ERR_SQLITE, errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool StorageManager::logSensorData(const char* sensorId, float value) {
    String sql = "INSERT INTO sensor_data (sensor_id, value) VALUES ('" + 
                String(sensorId) + "', " + String(value) + ")";
                
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if(rc != SQLITE_OK) {
        logError(ERR_SQLITE, errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}