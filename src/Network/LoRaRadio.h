#pragma once
#include <RadioLib.h>
#include <Arduino.h>
#include "Utilities/ErrorManager.h"
#include "Utilities/LogsManager.h"

// SX1278 pin mapping should be configured as per your hardware
class LoRaRadio {
public:
    LoRaRadio(uint8_t nss, uint8_t dio0, uint8_t nreset, SPIClass& spi);

    // Initialize LoRa with required parameters
    bool init(float freq, int bandwidth = 125, int spreadingFactor = 12, int codingRate = 5, int gain = 0);

    // Set LoRa parameters for transmit/receive
    void setTransmitMode(float freq, int power = 17);
    void setReceiveMode(float freq);

    // Transmit a packet, returns RadioLib status code
    int transmitData(const char* data);

    // Read received data (string version)
    int readData(String& str);

    // Read received data (raw buffer version)
    int readData(uint8_t* buf, size_t bufLen, size_t* outLen);

    // Get RSSI and SNR of the last packet
    int getRSSI();
    float getSNR();
    

    // Handlers for events
    void setPacketReceivedAction(void (*func)(void));
    void setPacketSentAction(void (*func)(void));

    // Start receive mode again after a packet
    int startReceive();

    // Access to underlying RadioLib SX1278 object
    SX1278& getRadio();

    // Print current LoRa status
    void printStatus();

private:
    SX1278 _radio;
    Module _module;

    // Utility for error logging
    void logRadioError(const String& context, int code);
};