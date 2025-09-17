#include "LogsManager.h"
#include "SettingsGw.h"   // for GW_id / GW_name
#include "Storage/SDManager.h"

// Global pointers
SDManager* g_sd = nullptr;
TimeManager* g_timeMgr = nullptr;

void Logs_init(SDManager& sd, TimeManager& timeMgr) {
  g_sd = &sd;
  g_timeMgr = &timeMgr;
}

// Helper to print timestamped line to Serial
static void printToSerial(const char* element, const char* value) {
  if (!g_timeMgr) {
    Serial.print(element);
    Serial.print(": ");
    Serial.println(value);
    return;
  }
  TimeManager::DateTimeInfo date = g_timeMgr->getCurrentDateTime();
  Serial.printf("%02d-%02d-%02dT%02d:%02d:%02d %s \"%s\" %s\n",
                date.year, date.month, date.day,
                date.hour, date.minute, date.second,
                element, value, GW_id);
}

void addElementToFile(const char* element, const char* value="") {
  if (!g_sd || !g_timeMgr) {
    Serial.println("Logs not initialized!");
    return;
  }

  // If SD is not mounted, just print to Serial
  if (!g_sd->isMounted()) {
    printToSerial(element, value);
    return;
  }

  TimeManager::DateTimeInfo date = g_timeMgr->getCurrentDateTime();
  char fileName[32];
  snprintf(fileName, sizeof(fileName),
           "%02d_%02d_%02d_LogFile.txt",
           date.year, date.month, date.day);

  String path = "/" + String(fileName);
  File logFile = g_sd->open(path.c_str(), "a");

  if (logFile) {
    char dataDate[32];
    snprintf(dataDate, sizeof(dataDate),
             "%02d-%02d-%02dT%02d:%02d:%02d ",
             date.year, date.month, date.day,
             date.hour, date.minute, date.second);

    logFile.print(dataDate);
    logFile.print(element);
    logFile.print(" \"");
    logFile.print(value);
    logFile.print("\" ");
    logFile.println(GW_id);
    logFile.close();
  } else {
    // fallback to Serial if file open fails
    printToSerial(element, value);
  }
}

void addLogLineToFile(const char* element) {
  if (!g_sd || !g_timeMgr) {
    Serial.println("Logs not initialized!");
    return;
  }

  if (!g_sd->isMounted()) {
    // fallback to Serial if no SD
    Serial.print(element);
    Serial.print(" ");
    Serial.println(GW_name);
    return;
  }

  TimeManager::DateTimeInfo date = g_timeMgr->getCurrentDateTime();
  char fileName[32];
  snprintf(fileName, sizeof(fileName),
           "%02d_%02d_%02d_PrGwLF.txt",
           date.year, date.month, date.day);

  String path = "/" + String(fileName);
  File logFile = g_sd->open(path.c_str(), "a");

  if (logFile) {
    logFile.print(element);
    logFile.print(" ");
    logFile.println(GW_name);
    logFile.close();
  } else {
    // fallback to Serial if file open fails
    Serial.print(element);
    Serial.print(" ");
    Serial.println(GW_name);
  }
}

void logBootEvents(const char* ssid,
                   const char* rebootReason0,
                   const char* rebootReason1,
                   const char* bootDate) {
  addElementToFile("Debug", ssid);
  addElementToFile("Warning", rebootReason0);
  addElementToFile("Warning", rebootReason1);
  addElementToFile("Warning", bootDate);
}
