#pragma once
#include <PubSubClient.h>
#include <WiFi.h>
#include "Utilities/LogsManager.h"
#include "Utilities/TimeManager.h"
#include "Utilities/ErrorManager.h"

class MQTTManager {
public:
    MQTTManager(PubSubClient& client);

    void init(const char* server, int port, const char* gw_name,
              const char* user, const char* pass, const char* subscribeQueue);

    void reconnect(const char* gw_name, const char* user, const char* pass, const char* subscribeQueue);

    void setCallback(MQTT_CALLBACK_SIGNATURE);

    bool isConnected();

    bool publish(const char* topic, const char* payload, size_t length = 0);

    bool subscribe(const char* topic, uint8_t qos = 1);

    void loop();

private:
    PubSubClient& _client;
    // LogsManager& _logs;
    // TimeManager& _timeMgr;
    // ErrorManager& _errorMgr;
    void logMQTTError(const String& context, int code);
};