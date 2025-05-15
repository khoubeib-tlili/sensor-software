#pragma once
#include <stdint.h>

class ConfigManager
{
public:
  uint8_t getLoraNSS() const { return Lora_NSS; }
  uint8_t getLoraSCK() const { return Lora_SCK; }
  uint8_t getLoraMISO() const { return Lora_MISO; }
  uint8_t getLoraMOSI() const { return Lora_MOSI; }
  uint8_t getLoraNRESET() const { return Lora_NRESET; }
  uint8_t getLoraDIO0() const { return Lora_DIO0; }
  uint8_t getSD_SCK() const { return SCK_sd; }
  uint8_t getSD_MISO() const { return MISO_sd; }
  uint8_t getSD_MOSI() const { return MOSI_sd; }
  uint8_t getSD_LoraCS() const { return CS_sd; }
  uint8_t getLoraFreq() const { return loraFreq; }
  const char *getWifiSsid() const { return wifi_ssid; }
  const char *getWifiPwd() const { return wifi_pass; }
  const char *getMqttServer() const { return mqtt_server; }

private:
  uint8_t Lora_NSS = 5;     // select pin on LoRa device
  uint8_t Lora_SCK = 18;    // SCK on SPI3
  uint8_t Lora_MISO = 19;   // MISO on SPI3
  uint8_t Lora_MOSI = 23;   // MOSI on SPI3
  uint8_t Lora_NRESET = 27; // reset pin on LoRa device
  uint8_t Lora_DIO0 = 35;   // DIO0 pin on LoRa device, used for RX and TX done
  // SD CARD pins Config
  uint8_t SCK_sd = 21;
  uint8_t MISO_sd = 22;
  uint8_t MOSI_sd = 13;
  uint8_t CS_sd = 15;
  float loraFreq = 868.0;
  char wifi_ssid[32] = "Ooredoo000878";
  char wifi_pass[32] = "HSQF7P5PU7?C4";
  char mqtt_server[64] = "";
};

extern ConfigManager config;