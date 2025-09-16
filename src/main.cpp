#include <WiFi.h>
#include "Utilities/TimeManager.h"

const char* ssid = "khaled";
const char* password = "khaled000";

// NTP server, offset in seconds (3600 = UTC+1), update interval (ms)
TimeManager timeMgr("pool.ntp.org", 3600, 60 * 1000);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  timeMgr.begin();
}

void loop() {
  timeMgr.update();

  // current date/time
  auto dt = timeMgr.getCurrentDateTime();
  Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n",
                dt.year, dt.month, dt.day,
                dt.hour, dt.minute, dt.second);

  // raw timestamp
  uint32_t ts = timeMgr.getTimestamp();
  Serial.print("Epoch timestamp: ");
  Serial.println(ts);

  // convert millis to human readable period
  String uptime = timeMgr.millisToPeriod(millis());
  Serial.print("Uptime: ");
  Serial.println(uptime);

  delay(2000);
}
