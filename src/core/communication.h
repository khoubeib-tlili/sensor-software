#pragma once
#include <RadioLib.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>
#include <ArduinoJson.h>

#define LORA_BAND 868.0
#define LORA_SPI SPI

class CommunicationManager
{
public:
    CommunicationManager(uint8_t loraNSS, uint8_t loraDIO0, uint8_t loraRST);
    bool begin();
    bool sendLoRaMessage(const String &message);
    bool sendMQTT(const char *topic, const JsonDocument &payload);

private:
    Module *loraModule;
    SX1278 radio;
    WiFiClient wifiClient;
    PubSubClient mqttClient;
};