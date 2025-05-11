#include <sqlite3.h>
typedef struct
{
    char sensorID[32];
    float consumption;
} SensorRecord;

bool insertRecord(SensorRecord *rec);
bool getPendingRecords();

// database.cpp
sqlite3 *getDBConnection()
{
    // Connection pooling implementation
}