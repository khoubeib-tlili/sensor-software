#pragma once

#define SCK 18    // SCK on SPI3
#define MISO 19   // MISO on SPI3
#define MOSI 23   // MOSI on SPI3

#define SCK_sd 21
#define MISO_sd 22
#define MOSI_sd 13
#define CS_sd 15

// LoRa Pins (adjust according to your wiring)
#define LORA_NSS 5 //select pin on LoRa device
#define LORA_DIO0 35 // DIO0 pin on LoRa device, used for RX and TX done
#define LORA_RST 27 // reset pin on LoRa device

typedef struct
{
  char wifi_ssid[32];
  char wifi_pass[32];
  char mqtt_server[64];
  float lora_freq;
} system_config_t;

void initConfiguration();
const system_config_t *getConfig();