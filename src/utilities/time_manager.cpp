#include "time_manager.h"

TimeManager::TimeManager() 
    : timeClient(ntpUDP, "pool.ntp.org", 3600, 60000) {}

void TimeManager::begin() {
    rtc.setTime(0); // Initialize with epoch
    timeClient.begin();
    if(timeClient.forceUpdate()) {
        rtc.setTime(timeClient.getEpochTime());
        ntpSynced = true;
    }
}

time_t TimeManager::getCurrentTime() {
    if(!ntpSynced && timeClient.update()) {
        rtc.setTime(timeClient.getEpochTime());
        ntpSynced = true;
    }
    return rtc.getEpoch();
}

String TimeManager::getFormattedTime() {
    return rtc.getTime("%Y-%m-%d %H:%M:%S");
}