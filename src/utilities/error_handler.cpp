#include "utilities/error_handler.h"
#include "storage/storage_manager.h"

QueueHandle_t errorQueue;

void initErrorHandler() {
  errorQueue = xQueueCreate(10, sizeof(error_code_t));
  xTaskCreate(errorHandlerTask, "ErrorTask", 2048, NULL, 5, NULL);
}

void logError(error_code_t code, const char* message) {
  Serial.printf("[ERROR] %d: %s\n", code, message);
  xQueueSend(errorQueue, &code, portMAX_DELAY);
  
  // Critical errors trigger restart
  if(code == ERR_SD_INIT || code == ERR_LORA) {
    esp_restart();
  }
}

void errorHandlerTask(void* pvParameters) {
  while(1) {
    error_code_t code;
    if(xQueueReceive(errorQueue, &code, portMAX_DELAY) == pdTRUE) {
      // Handle error (log to SD, send notification, etc.)
    }
  }
}