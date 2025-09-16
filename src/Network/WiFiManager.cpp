#include "WiFiManager.h"

WiFiManager::WiFiManager() 
{
    Serial.begin(115200); // Initialize serial
}

void WiFiManager::init(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    int tryCount = 0;
    while (WiFi.status() != WL_CONNECTED && tryCount < 5 ) {
        addElementToFile("WiFi", "Connecting...");
        // _errorMgr.logInfo("WiFi connecting...");
        Serial.print("Connecting to WiFi"); Serial.print(" attempt "); Serial.println(tryCount + 1);
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        tryCount++;
        Serial.print("Status: ");
        Serial.println(WiFi.status());  // prints numeric status code
        delay(2000);
    }
    if (WiFi.status() == WL_CONNECTED) {
        String msg = "WiFi Connected. IP: " + WiFi.localIP().toString();
        addElementToFile("WiFi", msg.c_str());
        // _errorMgr.logInfo(msg);
        Serial.println(msg);
    } else {
        addElementToFile("WiFi", "WiFi connection failed");
        // _errorMgr.logError("WiFi connection failed");
        Serial.println("WiFi connection failed");
    }
}

void WiFiManager::reconnect(const char* ssid, const char* password) {
    int tryCount = 0;
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED && tryCount < 5 && WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
        addElementToFile("WiFi", "Reconnecting...");
        // _errorMgr.logWarning("WiFi reconnecting...");
        Serial.print("Reconnecting to WiFi"); Serial.print(" attempt "); Serial.println(tryCount + 1);
        tryCount++;
        Serial.print("Status: ");
        Serial.println(WiFi.status()); 
        delay(2000);
    }
    if (WiFi.status() == WL_CONNECTED) {
        String msg = "WiFi Reconnected. IP: " + WiFi.localIP().toString();
        addElementToFile("WiFi", msg.c_str());
        // _errorMgr.logInfo(msg);
        Serial.println(msg);
    } else {
        addElementToFile("WiFi", "WiFi reconnection failed");
        // _errorMgr.logError("WiFi reconnection failed");
        Serial.println("WiFi reconnection failed");
    }
}

IPAddress WiFiManager::getLocalIP() {
    // Returns the local IP address of the ESP
    return WiFi.localIP();
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
