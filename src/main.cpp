#include <Arduino.h>
#include "Storage/SDManager.h"


// === Your SD pins ===
#define CS_SD   5
#define SCK_SD  18
#define MISO_SD 19
#define MOSI_SD 23

// Create SPI bus instance
SPIClass spiSD(VSPI);

// Create SDManager
SDManager sdManager(CS_SD, spiSD, 4000000); // 4 MHz

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("=== SDManager Test ===");

  // Init SPI
  spiSD.begin(SCK_SD, MISO_SD, MOSI_SD, CS_SD);

  // Mount SD card
  if (!sdManager.init()) {
    Serial.println("SD mount failed");
    while (1) delay(100);
  }
  Serial.println("SD mounted successfully");

  // Test: write a file
  File f = sdManager.open("/test.txt", "w");
  if (f) {
    f.println("Hello from ESP32 SDManager!");
    f.close();
    Serial.println("Wrote /test.txt");
  } else {
    Serial.println("Could not open /test.txt for writing");
  }

  // Test: check if file exists
  if (sdManager.exists("/test.txt")) {
    Serial.println("/test.txt exists");
  } else {
    Serial.println("/test.txt not found");
  }

  // Test: append to file
  File fa = sdManager.open("/test.txt", "a");
  if (fa) {
    fa.println("new line appended");
    fa.close();
    Serial.println("Appended to /test.txt");
  }

  // Test: read file back
  File fr = sdManager.open("/test.txt", "r");
  if (fr) {
    Serial.println("=== File contents ===");
    while (fr.available()) {
      Serial.write(fr.read());
    }
    fr.close();
    Serial.println("\n=====================");
  } else {
    Serial.println("Could not open /test.txt for reading");
  }

  // End SD session
  sdManager.end();
  Serial.println("SD session ended");
}

void loop() {
  // nothing here
}
