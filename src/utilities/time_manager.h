#pragma once
#include <ESP32Time.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeManager {
public:
    TimeManager();
    void begin();
    time_t getCurrentTime();
    String getFormattedTime();

private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    ESP32Time rtc;
    bool ntpSynced = false;
};