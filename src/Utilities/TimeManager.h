#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "RTClib.h"

class WiFiManager; // forward declare

class TimeManager {
public:
    struct DateTimeInfo {
        int year, month, day, hour, minute, second;
    };

    // Constructor: all elements optional
    TimeManager(const char* ntpAddress = "pool.ntp.org",
                long ntpOffset = 0,
                unsigned long ntpInterval = 60 * 1000,
                unsigned long syncInterval = 3600 * 1000,
                WiFiManager* wifiMgr = nullptr,
                bool useRTC = true,
                int sdaPin = 21,
                int sclPin = 22);

    void begin();                 // initialize NTP and optionally RTC
    void update();                // periodic update (NTP if WiFi connected)
    void forceSync();             // force NTP sync
    unsigned long getTimestamp(); // get epoch time, from NTP or RTC
    DateTimeInfo getCurrentDateTime(); // get structured date/time
    String millisToPeriod(unsigned long millisValue);
    void setSyncInterval(unsigned long newInterval);

private:
    void syncRTC();               // push NTP time into RTC

    WiFiManager* _wifiMgr;
    bool _useRTC;
    RTC_DS3231 _rtc;

    WiFiUDP _ntpUDP;
    NTPClient _timeClient;

    unsigned long _lastSync = 0;
    unsigned long _syncInterval;
};
