#pragma once
#include <WiFi.h>
#include "Utilities/LogsManager.h"
#include "Utilities/TimeManager.h"
#include "Utilities/ErrorManager.h"

class WiFiManager {
public:
    WiFiManager();

    void init(const char* ssid, const char* password);
    void reconnect(const char* ssid, const char* password);
    bool isConnected();
    IPAddress getLocalIP();

};