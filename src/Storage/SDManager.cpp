    #include "SDManager.h"

    SDManager::SDManager(uint8_t csPin, SPIClass& spi, uint32_t freq)
        : _csPin(csPin), _spi(spi), _freq(freq), _mounted(false) {}

    bool SDManager::init() {
        _spi.begin();
        _mounted = SD.begin(_csPin, _spi, _freq);
        if (_mounted) {
            addElementToFile("Debug", "SD Card mounted");
            // _errorMgr.logInfo("SD Card mounted");
        } else {
            addElementToFile("Error", "SD Card mount failed");
            // _errorMgr.logError("SD Card mount failed");
        }
        return _mounted;
    }

    bool SDManager::isMounted() {
        return _mounted;
    }

    File SDManager::open(const char* path, const char* mode) {
        if (!_mounted) {
            addElementToFile("Error", "SD card not mounted");
            // _errorMgr.logError("Attempted file open but SD not mounted");
            return File();
        }
        return SD.open(path, mode[0] == 'a' ? FILE_APPEND : (mode[0] == 'w' ? FILE_WRITE : FILE_READ));
    }

    bool SDManager::exists(const char* path) {
        if (!_mounted) return false;
        return SD.exists(path);
    }

    void SDManager::end() {
        SD.end();
        _mounted = false;
    }

    void SDManager::logSDStatus(const char* element, const char* value) {
        addElementToFile(element, value);
    }