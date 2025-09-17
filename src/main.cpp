#include <Arduino.h>
#include <Wire.h>
#include "Network/WiFiManager.h"
#include "Utilities/TimeManager.h"

// ---- Your WiFi credentials ----
const char* ssid = "khaled";
const char* password = "khaled000";

// ---- WiFi Manager ----
WiFiManager wifiMgr;

// ---- I2C pins for RTC ----
#define SDA_PIN 18
#define SCL_PIN 19

// ---- Time Manager ----
// Parameters: NTP server, UTC offset (3600 = 1h), NTP interval (60000ms), sync interval (10000ms),
// WiFi manager pointer, useRTC = true, SDA/SCL pins

TimeManager* timeMgr;
void setup() {
  Serial.begin(115200);
  Serial.println("\n--- TimeManager Test ---");

  // init WiFi
  wifiMgr.init(ssid, password);

  // init time manager (starts NTP + RTC)
  timeMgr = new TimeManager("pool.ntp.org", 3600, 60000, 10000, &wifiMgr, true, SDA_PIN, SCL_PIN);
  timeMgr->begin();

  // test changing sync interval
  Serial.println("Changing sync interval to 5 seconds...");
  timeMgr->setSyncInterval(5000);

  // Force a sync immediately
  Serial.println("Forcing NTP sync now...");
  timeMgr->forceSync();
}

void loop() {
  // // call update to perform periodic sync
  timeMgr->update();

  // test getTimestamp()
  unsigned long ts = timeMgr->getTimestamp();
  Serial.print("Timestamp: ");
  Serial.println(ts);

  // test getCurrentDateTime()
  TimeManager::DateTimeInfo dt = timeMgr->getCurrentDateTime();
  Serial.printf("Current DateTime: %04d-%02d-%02d %02d:%02d:%02d\n",
                dt.year, dt.month, dt.day,
                dt.hour, dt.minute, dt.second);

  // test millisToPeriod()
  String period = timeMgr->millisToPeriod(millis());
  Serial.print("Millis since boot = ");
  Serial.println(period);

  // Wait 1 second
  delay(1000);

  // After a few loops, test forceSync again
  static unsigned long lastForce = 0;
  if (millis() - lastForce > 30000) { // every 30s
    Serial.println("Forcing NTP sync again...");
    timeMgr->forceSync();
    lastForce = millis();
  }
}
