#include "TimeManager.h"
#include <time.h>

TimeManager::TimeManager(const char* ntpAddress,
                         long ntpOffset,
                         unsigned long ntpInterval)
    : _ntpUDP(),
      _timeClient(_ntpUDP, ntpAddress, ntpOffset, ntpInterval) {}

void TimeManager::begin() {
    _timeClient.begin();
}

void TimeManager::update() {
    _timeClient.update();
}

unsigned long TimeManager::getTimestamp() {
    return _timeClient.getEpochTime();
}

TimeManager::DateTime TimeManager::getCurrentDateTime() {
    time_t epochTime = _timeClient.getEpochTime();
    struct tm *timeinfo = gmtime(&epochTime);
    DateTime dt;
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

