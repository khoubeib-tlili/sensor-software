#include "TimeManager.h"
#include <time.h>
#include "Network/WiFiManager.h"

TimeManager::TimeManager(const char* ntpAddress,
                         long ntpOffset,
                         unsigned long ntpInterval,
                         unsigned long syncInterval,
                         WiFiManager* wifiMgr,
                         bool useRTC,
                         int sdaPin,
                         int sclPin )
    : _ntpUDP(),
      _timeClient(_ntpUDP, ntpAddress, ntpOffset, ntpInterval),
      _syncInterval(syncInterval),
      _wifiMgr(wifiMgr),
      _useRTC(useRTC)
{
    if (_useRTC) {
        Wire.begin(sdaPin, sclPin); // only init I2C if RTC is used
        if (!_rtc.begin()) {
            Serial.println("RTC not found");
        }
    }
}


void TimeManager::begin() {
    _timeClient.begin();

    if (!_rtc.begin()) {
        Serial.println("RTC not found");
    } else {
        Serial.println("RTC found");
        if (_rtc.lostPower()) {
            Serial.println("RTC lost power");
        }
    }
}

void TimeManager::update() {
    unsigned long nowMillis = millis();
    if (nowMillis - _lastSync > _syncInterval) {
        // Only try NTP if we have WiFi manager and connection
        if (_wifiMgr && _wifiMgr->isConnected()) {
            if (_timeClient.forceUpdate()) {   // true if NTP success
                syncRTC();
                _lastSync = nowMillis;
            } else {
                Serial.println("NTP update failed, keeping RTC time");
            }
        } else {
            Serial.println("No WiFi connection, using RTC only");
        }
    }
}

void TimeManager::forceSync() {
    // Force a sync right now
    if (_wifiMgr && _wifiMgr->isConnected()) {
        if (_timeClient.forceUpdate()) {
            syncRTC();
            _lastSync = millis();
        } else {
            Serial.println("Force sync failed (NTP error)");
        }
    } else {
        Serial.println("Force sync skipped (no WiFi)");
    }
}

void TimeManager::syncRTC() {
    DateTimeInfo dt = getCurrentDateTime();
    _rtc.adjust(DateTime(dt.year, dt.month, dt.day,
                         dt.hour, dt.minute, dt.second));
    Serial.println("RTC synced from NTP");
}

unsigned long TimeManager::getTimestamp() {
    // Use NTP if valid and WiFi connected
    if (_wifiMgr && _wifiMgr->isConnected() &&
        _timeClient.getEpochTime() > 100000) {
        return _timeClient.getEpochTime();
    }
    // Otherwise use RTC
    DateTime now = _rtc.now();
    return now.unixtime();
}

TimeManager::DateTimeInfo TimeManager::getCurrentDateTime() {
    DateTimeInfo dt;
    time_t epochTime;

    if (_wifiMgr && _wifiMgr->isConnected() &&
        _timeClient.getEpochTime() > 100000) {
        epochTime = _timeClient.getEpochTime();
    } else {
        DateTime now = _rtc.now();
        epochTime = now.unixtime();
    }

    struct tm *timeinfo = gmtime(&epochTime);
    dt.year   = timeinfo->tm_year + 1900;
    dt.month  = timeinfo->tm_mon + 1;
    dt.day    = timeinfo->tm_mday;
    dt.hour   = timeinfo->tm_hour;
    dt.minute = timeinfo->tm_min;
    dt.second = timeinfo->tm_sec;
    return dt;
}

String TimeManager::millisToPeriod(unsigned long millisValue) {
    unsigned long seconds = millisValue / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    unsigned long days = hours / 24;
    String periodString = String(days) + "d" + String(hours % 24) + "h" +
                          String(minutes % 60) + "m" + String(seconds % 60) + "s";
    return periodString;
}

void TimeManager::setSyncInterval(unsigned long newInterval) {
    _syncInterval = newInterval;
    Serial.print("Sync interval changed to: ");
    Serial.print(newInterval / 1000);
    Serial.println(" seconds");
}
