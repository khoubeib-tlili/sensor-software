#include "core/task_manager.h"
#include "utilities/time_manager.h"
#include "storage/storage_manager.h"
#include "core/communication.h"

TimeManager timeManager;
StorageManager storageManager;
CommunicationManager commManager(5, 2, 32); // LoRa pins

void setup() {
    Serial.begin(115200);
    
    // Initialize core systems
    timeManager.begin();
    storageManager.begin(SS);
    commManager.begin();
    
    // Create tasks
    createSystemTasks();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}