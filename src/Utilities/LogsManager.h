#ifndef LOGS_H
#define LOGS_H

#include <Arduino.h>
#include "TimeManager.h"
#include "SettingsGw.h" 

class SDManager;   // forward declare
// Initializes the logging system.
// Must be called once in setup() with your SDManager and TimeManager instances.
void Logs_init(SDManager& sd, TimeManager& timeMgr);

// Append a line with timestamp + element + value into daily log file.
void addElementToFile(const char* element, const char* value);

// Append a line with element + gateway name into a different log file.
void addLogLineToFile(const char* element);

// Logs a group of boot events (SSID, reboot reasons, boot date).
void logBootEvents(const char* ssid,
                   const char* rebootReason0,
                   const char* rebootReason1,
                        const char* bootDate);

#endif // LOGS_H
