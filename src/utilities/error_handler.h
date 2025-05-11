#pragma once

typedef enum {
  ERR_NONE = 0,
  ERR_SD_INIT,
  ERR_SQLITE,
  ERR_LORA,
  ERR_WIFI,
  ERR_MQTT,
  ERR_MEMORY
} error_code_t;

void initErrorHandler();
void logError(error_code_t code, const char* message);
void errorHandlerTask(void* pvParameters);