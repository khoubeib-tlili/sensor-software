#include "communication.h"
#include "../utilities/error_handler.h"
#include <Arduino.h>
#include <utilities/config_manager.h>

SX1278 radio = new Module(LORA_NSS, LORA_DIO0, LORA_RST);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

QueueHandle_t loraRxQueue;
QueueHandle_t mqttTxQueue;

// Constructor now initializes the Module pointer
CommunicationManager::CommunicationManager(uint8_t loraNSS, uint8_t loraDIO0, uint8_t loraRST) :
    loraModule(new Module(loraNSS, loraDIO0, loraRST, RADIOLIB_NC, LORA_SPI)),
    radio(loraModule) {}

bool CommunicationManager::begin() {
    // Initialize SPI
    SPI.begin(SCK, MISO, MOSI, loraModule->getNss());
    
    // Initialize LoRa with ESP32-compatible settings
    int state = radio.begin(LORA_BAND);
    if(state != RADIOLIB_ERR_NONE) {
        Serial.print("LoRa init failed (ESP32): ");
        Serial.println(state);
        return false;
    }

    // ESP32-specific interrupt setup
    pinMode(loraModule->getIrq(), INPUT);
    attachInterrupt(digitalPinToInterrupt(loraModule->getIrq()), []() {
        // Your ISR handling here
    }, RISING);

    return true;
}

volatile bool receivedFlag = false;

void IRAM_ATTR setFlag()
{
    receivedFlag = true;
}

void initCommunication()
{
    // Initialize LoRa
    int state = radio.begin(868.0);
    if (state != RADIOLIB_ERR_NONE)
    {
        logError(ERR_LORA, "LoRa init failed");
        return;
    }

    radio.setPacketReceivedAction(setFlag);

    // Initialize WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Initialize MQTT
    mqttClient.setServer(MQTT_SERVER, 1883);

    // Create queues
    loraRxQueue = xQueueCreate(LORA_QUEUE_SIZE, sizeof(lora_packet_t));
    mqttTxQueue = xQueueCreate(MQTT_QUEUE_SIZE, sizeof(mqtt_message_t));
}

void communicationTask(void *pvParameters)
{
    while (1)
    {
        // Handle LoRa reception
        if (receivedFlag)
        {
            receivedFlag = false;
            lora_packet_t packet;
            int state = radio.readData(packet.data, packet.length);
            if (state == RADIOLIB_ERR_NONE)
            {
                packet.rssi = radio.getRSSI();
                packet.snr = radio.getSNR();
                xQueueSend(loraRxQueue, &packet, portMAX_DELAY);
            }
        }

        // Handle MQTT transmission
        mqtt_message_t msg;
        if (xQueueReceive(mqttTxQueue, &msg, 0) == pdTRUE)
        {
            if (!mqttClient.connected())
            {
                mqttClient.connect("ESP32Gateway");
            }
            mqttClient.publish(msg.topic, msg.payload);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}