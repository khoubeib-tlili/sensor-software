#include <Arduino.h>
#include <SPI.h>
#include "Network/LoRaRadio.h"

// LoRa pins
#define LORA_NSS   5
#define LORA_DIO0  35
#define LORA_RESET 27

// SPI instance
SPIClass loraSPI(VSPI);

// LoRaRadio instance
LoRaRadio lora(LORA_NSS, LORA_DIO0, LORA_RESET, loraSPI);

// Packet received callback
void onPacketReceived() {
    String packet;
    int bytesRead = lora.readData(packet);
    if (bytesRead > 0) {
        Serial.print("Received: "); Serial.println(packet);
        Serial.print("RSSI: "); Serial.print(lora.getRSSI());
        Serial.print(" | SNR: "); Serial.println(lora.getSNR(), 2);
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("---- LoRa Receiver ----");

    // Initialize SPI
    loraSPI.begin(18, 19, 23, LORA_NSS); // SCK, MISO, MOSI, CS

    // Initialize LoRa radio
    if (!lora.init(868.0, 125000, 7, 5, 0)) { // freq, BW, SF, CR, gain
        Serial.println("LoRa init failed!");
        while(1);
    }
    Serial.println("LoRa initialized successfully.");

    // Set LoRa to receive mode
    lora.setReceiveMode(868.0);

    // Set callbacks
    lora.setPacketReceivedAction(onPacketReceived);
}

void loop() {
    int rxState = lora.startReceive();
    if (rxState != RADIOLIB_ERR_NONE && rxState != RADIOLIB_ERR_RX_TIMEOUT) {
        Serial.print("Receive error, code: "); Serial.println(rxState);
    }
    delay(100);
}




#include <Arduino.h>
#include <SPI.h>
#include "Network/LoRaRadio.h"

// LoRa pins
#define LORA_NSS   5
#define LORA_DIO0  35
#define LORA_RESET 27

// SPI instance
SPIClass loraSPI(VSPI);

// LoRaRadio instance
LoRaRadio lora(LORA_NSS, LORA_DIO0, LORA_RESET, loraSPI);

// Test message
const char* testMsg = "Hello LoRa!";

// Packet sent callback
void onPacketSent() {
    Serial.println("Packet successfully sent (callback).");
}

// void setup() {
//     Serial.begin(115200);
//     delay(1000);
//     Serial.println("---- LoRa Sender ----");

//     // Initialize SPI
//     loraSPI.begin(18, 19, 23, LORA_NSS);

//     // Initialize LoRa radio
//     if (!lora.init(868.0, 125000, 7, 5, 0)) {
//         Serial.println("LoRa init failed!");
//         while(1);
//     }
//     Serial.println("LoRa initialized successfully.");

//     // Set callbacks
//     lora.setPacketSentAction(onPacketSent);

//     // Send a test message
//     int txState = lora.transmitData(testMsg);
//     if (txState == RADIOLIB_ERR_NONE) {
//         Serial.println("Test message transmitted.");
//     } else {
//         Serial.print("Transmit error, code: "); Serial.println(txState);
//     }
// }

// void loop() {
//     // Can send periodically
//     static unsigned long lastSend = 0;
//     if (millis() - lastSend > 5000) { // every 5 seconds
//         int txState = lora.transmitData(testMsg);
//         if (txState == RADIOLIB_ERR_NONE) {
//             Serial.println("Message transmitted.");
//         } else {
//             Serial.print("Transmit error, code: "); Serial.println(txState);
//         }
//         lastSend = millis();
//     }
//     delay(100);
// }
