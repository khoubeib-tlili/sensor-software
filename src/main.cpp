#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include "Network/WiFiManager.h"   // Your Wi-Fi manager class
#include "Network/MQTTManager.h"   // Your MQTT manager class

// ===== MQTT Broker Credentials =====
const char* mqtt_server     = "rq-poc.water-sec.com";
const int   mqtt_port       = 1883;  // default MQTT port
const char* mqtt_user       = "test";
const char* mqtt_pass       = "Test123!";
const char* subscribe_topic = "esp32/test";

// Wi-Fi and MQTT objects
WiFiManager wifiManager;
WiFiClient espClient;
PubSubClient client(espClient);
MQTTManager mqttManager(client);

// Callback for incoming MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);
    Serial.print("Payload: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting ESP32 Wi-Fi + MQTT Test...");

    // ===== Connect to Wi-Fi using WiFiManager =====
    const char* ssid = "khaled";       // your Wi-Fi SSID
    const char* password = "khaled000"; // your Wi-Fi password
    wifiManager.init(ssid, password);

    // ===== Initialize MQTT =====
    mqttManager.setCallback(mqttCallback);
    mqttManager.init(mqtt_server, mqtt_port, "ESP32Client", mqtt_user, mqtt_pass, subscribe_topic);
}

void loop() {
    // Maintain MQTT connection
    if (!mqttManager.isConnected()) {
        Serial.println("MQTT disconnected, attempting to reconnect...");
        mqttManager.reconnect("ESP32Client", mqtt_user, mqtt_pass, subscribe_topic);
    }

    mqttManager.loop();

    // Publish a test message every 5 seconds
    static unsigned long lastPublish = 0;
    if (millis() - lastPublish > 5000) {
        const char* testMsg = "Hello from ESP32!";
        Serial.print("Publishing: ");
        Serial.println(testMsg);
        mqttManager.publish("esp32/test", testMsg);
        lastPublish = millis();
    }
}
