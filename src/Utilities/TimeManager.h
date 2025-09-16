#pragma once
#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

class TimeManager {
public:
    struct DateTime {
        int year, month, day, hour, minute, second;
    };

    // constructor: give NTP server, offset, and update interval
    TimeManager(const char* ntpAddress,
                long ntpOffset,
                unsigned long ntpInterval);

    void begin();      // call once after WiFi is connected
    void update();     // call periodically in loop()

    unsigned long getTimestamp();   // returns UNIX epoch time
    DateTime getCurrentDateTime();  // returns DateTime struct

    String millisToPeriod(unsigned long millisValue);


private:
    WiFiUDP _ntpUDP;
    NTPClient _timeClient;
};
