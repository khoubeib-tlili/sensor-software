#include "communication.h"
#include <ArduinoJson.h>

CommunicationManager::CommunicationManager(uint8_t loraNSS, uint8_t loraDIO0, uint8_t loraRST)
    : radio(new Module(loraNSS, loraDIO0, loraRST)),
      mqttClient(wifiClient) {}

bool CommunicationManager::begin()
{
    // Initialize LoRa
    int state = radio.begin(LORA_BAND);
    if (state != RADIOLIB_ERR_NONE)
        return false;

    radio.setDio0Action([]() { /* ISR handler */ });

    // Initialize WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Initialize MQTT
    mqttClient.setServer(MQTT_SERVER, 1883);
    return true;
}

bool CommunicationManager::sendMQTT(const char *topic, const JsonDocument &payload)
{
    if (!mqttClient.connected())
    {
        mqttClient.connect("ESP32Gateway");
    }

    String jsonStr;
    serializeJson(payload, jsonStr);
    return mqttClient.publish(topic, jsonStr.c_str());
}