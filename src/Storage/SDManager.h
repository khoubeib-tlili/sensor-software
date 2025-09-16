#pragma once
#include <SD.h>
#include <SPI.h>
#include "Utilities/LogsManager.h"
#include "Utilities/TimeManager.h"
#include "Utilities/ErrorManager.h"

class SDManager {
public:
    SDManager(uint8_t csPin, SPIClass& spi, uint32_t freq = 4000000);
    bool init();
    bool isMounted();
    File open(const char* path, const char* mode = "r");
    bool exists(const char* path);
    void end();
    void logSDStatus(const char* element, const char* value);
private:
    uint8_t _csPin;
    SPIClass& _spi;
    uint32_t _freq;
    bool _mounted;
};