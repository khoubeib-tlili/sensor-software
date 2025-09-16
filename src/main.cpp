#include <Arduino.h>
#include <SPI.h>
#include "Storage/SDManager.h"
#include "Storage/DatabaseManager.h"

// --- SD Pins ---
#define SCK_SD  18
#define MISO_SD 19
#define MOSI_SD 23
#define CS_SD   5

// --- SPI bus for SD ---
SPIClass spiSD(VSPI); // we’ll set pins in begin()

// --- Managers ---
SDManager sdManager(CS_SD, spiSD, 4000000);  // 4 MHz
DatabaseManager* dbManager = nullptr;

// --- callback for SELECT queries ---
static int selectCallback(void* data, int argc, char** argv, char** azColName) {
  Serial.println("Row:");
  for (int i = 0; i < argc; i++) {
    Serial.printf("  %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  return 0;
}

#include <WiFi.h>
#include "Utilities/TimeManager.h"

const char* ssid = "khaled";
const char* password = "khaled000";

// NTP server, offset in seconds (3600 = UTC+1), update interval (ms)
TimeManager timeMgr("pool.ntp.org", 3600, 60 * 1000);


void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  timeMgr.begin();
  timeMgr.update();

  Serial.println("=== SD + SQLite Test ===");

  // Configure SPI pins
  spiSD.begin(SCK_SD, MISO_SD, MOSI_SD, CS_SD);
  Logs_init(sdManager, timeMgr);

  // 1) Init SD
  if (!sdManager.init()) {
    Serial.println("Failed to init SD!");
    while (1) delay(100);
  }
  Serial.println("SD mounted successfully");
   

  // 2) Test plain SD file write/read
  File f = sdManager.open("/test.txt", "a");
  if (f) {
    f.println("Hello from ESP32!");
    f.close();
    Serial.println("Wrote test.txt on SD");
  }

  f = sdManager.open("/test.txt", "r");
  if (f) {
    Serial.println("Contents of test.txt:");
    while (f.available()) {
      Serial.write(f.read());
    }
    f.close();
  }

  // 3) Create Database on SD
  dbManager = new DatabaseManager("/sd/test.db"); // path relative to SD
  if (!dbManager->open()) {
    Serial.println("Failed to open DB!");
    while (1) delay(100);
  }
  Serial.println("Database opened successfully");

  // Create a table
  const char* createTableSQL =
      "CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, name TEXT);";
  if (!dbManager->createTable(createTableSQL)) {
    Serial.println("Failed to create table!");
  } else {
    Serial.println("Table created OK");
  }

  // Insert some data
  const char* insertSQL = "INSERT INTO test_table (name) VALUES ('ESP32');";
  if (!dbManager->exec(insertSQL)) {
    Serial.println("Insert failed");
  } else {
    Serial.println("Inserted record");
  }

  // Select data
  const char* selectSQL = "SELECT * FROM test_table;";
  Serial.println("Querying records:");
  dbManager->exec(selectSQL, selectCallback, nullptr);

  // Close DB
  dbManager->close();
  Serial.println("DB closed");
}

void loop() {
  // Nothing to do
}
