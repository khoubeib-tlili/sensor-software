#include "config_manager.h"
#include "../storage/storage_manager.h"

static system_config_t currentConfig;

void initConfiguration()
{
    // Default values
    strcpy(currentConfig.wifi_ssid, "default_ssid");
    strcpy(currentConfig.wifi_pass, "default_pass");
    currentConfig.lora_freq = 868.0;

    // Try loading from SD card
    if (SD.exists("/config.json"))
    {
        File configFile = SD.open("/config.json");
        // Parse JSON config
        configFile.close();
    }
}

const system_config_t *getConfig()
{
    return &currentConfig;
}