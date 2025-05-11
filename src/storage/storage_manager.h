#pragma once
#include <sqlite3.h>
#include <SD.h>
#include <ArduinoJson.h>

class StorageManager
{
public:
    bool begin(uint8_t csPin);
    bool logSensorData(const char *sensorId, float value);
    bool getPendingRecords(JsonDocument &output);

private:
    sqlite3 *db;
    bool initDB();
};