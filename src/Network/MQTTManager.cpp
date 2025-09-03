#include "MQTTManager.h"

MQTTManager::MQTTManager(PubSubClient& client)
    : _client(client)
{}

void MQTTManager::init(const char* server, int port, const char* gw_name,
                       const char* user, const char* pass, const char* subscribeQueue)
{
    _client.setBufferSize(512);
    _client.setKeepAlive(60);
    _client.setSocketTimeout(10);
    _client.setServer(server, port);

    int trialCount = 0;
    bool connected = false;
    while (trialCount < 3) {
        if (_client.connect(gw_name, user, pass)) {
            // _logs.addElementToFile("MQTT", "Connected to broker");
            // _errorMgr.logInfo("MQTT connected");
            Serial.println("MQTT connected to broker");
            connected = true;
            break;
        } else {
            // _logs.addElementToFile("MQTT", "Connecting to MQTT failed");
            // _errorMgr.logWarning("MQTT connection failed");
            Serial.print("MQTT connection attempt ");
            Serial.print(trialCount + 1);
            Serial.println(" failed");
            trialCount++;
            delay(1000);
        }
    }
    if (connected) {
        if (_client.subscribe(subscribeQueue, 1)) {
            // _logs.addElementToFile("MQTT", "Subscribed to topic");
            char msg[128];
            snprintf(msg, sizeof(msg), "Subscribed to topic: %s", subscribeQueue);
            // _errorMgr.logInfo(msg);
            Serial.println(msg);
        } else {
            // _logs.addElementToFile("MQTT", "Subscription failed");
            // _errorMgr.logError("MQTT subscription failed");
            Serial.print("MQTT subscription failed for topic: ");
            Serial.println(subscribeQueue);
        }
    }
}

void MQTTManager::reconnect(const char* gw_name, const char* user, const char* pass, const char* subscribeQueue)
{
    int trials = 0, trialsSub = 0;
    while (!_client.connected() && trials < 2) {
        if (_client.connect(gw_name, user, pass)) {
            // _logs.addElementToFile("MQTT", "Reconnected to broker");
            // _errorMgr.logInfo("MQTT reconnected");
            Serial.println("MQTT reconnected to broker");
            break;
        } else {
            // _logs.addElementToFile("MQTT", "MQTT reconnect failed");
            // _errorMgr.logWarning("MQTT reconnect failed");
            Serial.print("MQTT reconnect attempt ");
            Serial.print(trials + 1);
            Serial.println(" failed");
            trials++;
            delay(100);
        }
    }
    while (trialsSub < 2) {
        if (_client.subscribe(subscribeQueue, 1)) {
            // _logs.addElementToFile("MQTT", "Subscribed to topic after reconnect");
            char msg[128];
            snprintf(msg, sizeof(msg), "Subscribed to topic after reconnect: %s", subscribeQueue);
            // _errorMgr.logInfo(msg);
            Serial.println(msg);
            break;
        } else {
            // _logs.addElementToFile("MQTT", "MQTT subscribe failed after reconnect");
            // _errorMgr.logError("MQTT subscribe failed after reconnect");
            Serial.print("MQTT subscription after reconnect failed for topic: ");
            Serial.println(subscribeQueue);
            trialsSub++;
            delay(100);
        }
    }
}

void MQTTManager::setCallback(MQTT_CALLBACK_SIGNATURE) {
    _client.setCallback(callback);
}

bool MQTTManager::isConnected() {
    return _client.connected();
}

bool MQTTManager::publish(const char* topic, const char* payload, size_t length) {
    bool result = false;
    if (length == 0)
        result = _client.publish(topic, payload);
    else
        result = _client.publish(topic, payload, length);

    char msg[128];
    if (result) {
        snprintf(msg, sizeof(msg), "Published to %s", topic);
        // _logs.addElementToFile("MQTT", msg);

        snprintf(msg, sizeof(msg), "MQTT published to: %s", topic);
        // _errorMgr.logInfo(msg);
        Serial.println(msg);
    } else {
        snprintf(msg, sizeof(msg), "Publish failed to %s", topic);
        // _logs.addElementToFile("MQTT", msg);

        snprintf(msg, sizeof(msg), "MQTT publish failed to: %s", topic);
        // _errorMgr.logError(msg);
        Serial.println(msg);
    }
    return result;
}

bool MQTTManager::subscribe(const char* topic, uint8_t qos) {
    bool result = _client.subscribe(topic, qos);
    char msg[128];
    if (result) {
        snprintf(msg, sizeof(msg), "Subscribed to %s", topic);
        // _logs.addElementToFile("MQTT", msg);

        snprintf(msg, sizeof(msg), "MQTT subscribed to: %s", topic);
        // _errorMgr.logInfo(msg);
        Serial.println(msg);
    } else {
        snprintf(msg, sizeof(msg), "Subscribe failed to %s", topic);
        // _logs.addElementToFile("MQTT", msg);

        snprintf(msg, sizeof(msg), "MQTT subscribe failed to: %s", topic);
        // _errorMgr.logError(msg);
        Serial.println(msg);
    }
    return result;
}

void MQTTManager::loop() {
    _client.loop();
}

void MQTTManager::logMQTTError(const String& context, int code) {
    char msg[128];
    snprintf(msg, sizeof(msg), "%s failed, code: %d", context.c_str(), code);
    // _logs.addElementToFile("MQTTError", msg);
    // _errorMgr.logError(msg);
    Serial.print("[MQTT ERROR] ");
    Serial.println(msg);
}
