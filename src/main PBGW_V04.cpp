
// #include <RadioLib.h>
// #include <PubSubClient.h>
// #include <WiFi.h>
// #include <NTPClient.h>
// #include <ArduinoJson.h>
// #include "SettingsGw.h"
// //#include <stdlib.h>
// #include <iostream>
// //#include <string>
// #include <sstream>
// #include "FS.h"
// #include "SD.h"
// #include "SPI.h"
// //#include <stdio.h>
// #include "esp32/rom/rtc.h"
// //#include <ESP32Time.h>
// //#include <RTClib.h>
// #include <sqlite3.h>
// #include <time.h>
// //#include <TimeLib.h>

// SPIClass spi_cd = SPIClass(HSPI);


// String mqttPayload = "";
// const char* data = "Callback function called";
// char* zErrMsg = 0;
// int transmissionState = RADIOLIB_ERR_NONE;
// volatile bool transmittedFlag = false;
// int sdAttempts = 0;

// int retryCount = 0;

// #define Program_Version "V_26_FEV_2025"
// #define NTP_OFFSET 3600     // In seconds
// #define NTP_INTERVAL 60 * 1000  // In miliseconds
// #define NTP_ADDRESS "pool.ntp.org"
// #define MQTT_KEEP_ALIVE 60000

// unsigned long wifiStartTime = 0;

// unsigned long wifiRuntime = 0;
// // Définition de l'adresse IP fixe


// bool sdState = false;

// int SDtrialCount = 0;

// int MQTTtrialCount = 0;
// static portMUX_TYPE TimeMux = portMUX_INITIALIZER_UNLOCKED;
// // SX1278 radio = new Module(5, 2, 32, -1, SPI);

// SX1278 radio = new Module(NSS, DIO0, NRESET, -1, SPI);
// volatile bool receivedFlag = false;

// sqlite3* db1;  // Assuming this is declared somewhere in your code
// // Variables for processing and storing data
// int counter = 0;
// // const std::string delimiter = "/";
// String concatenatedlineID;
// int cardFreqInt = 0;


// WiFiUDP ntpUDP;
// WiFiClient espClient;
// PubSubClient client(espClient);
// NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);


// //ESP32Time rtc(3600);  // offset in seconds GMT+1

// uint32_t currentTime = 0;
// unsigned long currentTimetemp = 0;
// unsigned long offsetmillis = 0;

// int RSSI = 0;


// TaskHandle_t transmitTask;
// TaskHandle_t checkbutask;
// TaskHandle_t Datatask;
// TaskHandle_t wifiTask;
// TaskHandle_t LoRaTask;
// TaskHandle_t transmitterModeINVENTAIREtask;
// TaskHandle_t transmitFuncInventaireTask;
// TaskHandle_t transmitFuncTimeTask;
// TaskHandle_t SdInitTask;
// TaskHandle_t WiFiXmqttTask;

// unsigned long time_temp;


// std::string delimiter = "/";
// std::string consumption;
// std::string duration;
// std::string Sensor_ID;
// std::string line_ID;
// std::string card_freq;
// std::string indicator;
// std::string logLine;
// std::string dateString;
// std::string times;
// std::string frequency;
// std::string freqHZ;
// std::string cardID;
// std::string notifValue;
// std::string prGW_id;
// std::string notifSensorID;
// std::string notifType;
// std::string notifDate;
// std::string card_id_hc;
// std::string token_hc;
// std::string sensor_id_ack;
// std::string cons_ack;
// std::string dur_ack;

// int freq;
// String cardIDTH;
// String sensorIDTH;
// int timeTH;
// float consumptionTH;

// int indicatorMQTT;
// String cardIdHC;
// String token;
// int freqHC;
// int freqInv;

// void IRAM_ATTR setFlag(void) {
//   receivedFlag = true;
// }

// void setFlagT(void) {
//   // we sent a packet, set the flag
//   transmittedFlag = true;
// }

// void reconnectMQTT() {
//   int MQTTtrials = 0;
//   int MQTTtrialsSub = 0;

//   while (MQTTtrials < 2) {
//     if (client.connect(GW_name, mqtt_user, mqtt_pass)) {
//       // Mount Success, exit the loop
//       Serial.println("connected to mqtt");
//       break;
//     } else {
//       Serial.println("Connecting to MQTT Failed");
//       MQTTtrials++;


//       delay(10);
//     }
//   }
//   while (MQTTtrialsSub < 2) {

//     if (client.subscribe(subscribeQueue, 1)) {

//       Serial.println("subscribed to the desired topic");
//       break;
//     } else {
//       Serial.println("Subscribing to MQTT Failed");
//       MQTTtrialsSub++;
//       delay(10);
//     }
//   }
// }

// void reconnectWiFi() {
//   int TryCount = 0;
//   WiFi.disconnect();
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED && TryCount < 5 && WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
//     Serial.println("Connecting to WiFi..");
//     TryCount++;

//   }
// }
// String resetReason(int reason) {
//   switch (reason) {
//     case 1: return "POWERON_RESET"; break;           /**<1,  Vbat power on reset*/
//     case 3: return "SW_RESET"; break;                /**<3,  Software reset digital core*/
//     case 4: return "OWDT_RESET"; break;              /**<4,  Legacy watch dog reset digital core*/
//     case 5: return "DEEPSLEEP_RESET"; break;         /**<5,  Deep Sleep reset digital core*/
//     case 6: return "SDIO_RESET"; break;              /**<6,  Reset by SLC module, reset digital core*/
//     case 7: return "TG0WDT_SYS_RESET"; break;        /**<7,  Timer Group0 Watch dog reset digital core*/
//     case 8: return "TG1WDT_SYS_RESET"; break;        /**<8,  Timer Group1 Watch dog reset digital core*/
//     case 9: return "RTCWDT_SYS_RESET"; break;        /**<9,  RTC Watch dog Reset digital core*/
//     case 10: return "INTRUSION_RESET"; break;        /**<10, Instrusion tested to reset CPU*/
//     case 11: return "TGWDT_CPU_RESET"; break;        /**<11, Time Group reset CPU*/
//     case 12: return "SW_CPU_RESET"; break;           /**<12, Software reset CPU*/
//     case 13: return "RTCWDT_CPU_RESET"; break;       /**<13, RTC Watch dog Reset CPU*/
//     case 14: return "EXT_CPU_RESET"; break;          /**<14, for APP CPU, reseted by PRO CPU*/
//     case 15: return "RTCWDT_BROWN_OUT_RESET"; break; /**<15, Reset when the vdd voltage is not stable*/
//     case 16: return "RTCWDT_RTC_RESET"; break;       /**<16, RTC Watch dog reset digital core and rtc module*/
//     default: return "NO_MEAN";
//   }
// }

// static int callback_(void* data, int argc, char** argv, char** azColName) {
//   return 0;
// }

// sqlite3* db;
// int callbackTranFunc(void* data, int argc, char** argv, char** azColName) {
//   Serial.println(F("callbackTranFunc*****************************"));

//   int i;
//   std::stringstream ss;
//   for (i = 3; i < argc - 2; i++) {
//     ss << argv[i] << "/";
//   }
//   std::string SensorData = ss.str();
//   std::string buffer(SensorData.c_str());

//   Sensor_ID = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   consumption = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   times = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   duration = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());


//   DynamicJsonDocument docBu(128);
//   JsonObject data1;
//   char out1[128];
//   data1 = docBu.createNestedObject(F("data"));
//   docBu["device"] = Sensor_ID;
//   data1["consumption"] = consumption;
//   data1["time"] = times;
//   data1["period"] = duration;
//   size_t n1 = serializeJson(docBu, out1);
//   Serial.println(F("Sending message to MQTT topic.."));
//   Serial.print(F("bytes = "));
//   Serial.println(n1, DEC);
//   Serial.println(out1);
//   if(WiFi.status() != WL_CONNECTED){
//   reconnectWiFi();
//   }
//  if(!client.connected()){
//   reconnectMQTT();
//  }

  
//   if (client.publish(DataQueue, out1, n1)) {
//     Serial.println(F("Success Sending message to MQTT topic !"));
//     std::string currentLine(argv[0]);
//     int rowValue = std::stoi(currentLine);
//     std::string SqlQuery = "UPDATE BackupDB SET sentFlag = 1 WHERE row =" + std::to_string(rowValue) + ";";
//     Serial.println(SqlQuery.c_str());
//     int rc1 = sqlite3_exec(db, SqlQuery.c_str(), NULL, NULL, NULL);  //callbackTranFunc, (void*)data, &zErrMsg
//     Serial.print("ESP.getFreeHeap()");
//     Serial.println(ESP.getFreeHeap());
//     Serial.print("rc1 = ");
//     Serial.println(rc1);
//     if (rc1 != SQLITE_OK) {
//       Serial.println(F("SQL error: manajmench nbadlou el sentFlag to 1"));
//       Serial.printf("SQL error: %s\n", zErrMsg);
//       sqlite3_free(zErrMsg);
//       Serial.print("rc1 = ");
//       Serial.println(rc1);
//     } else {
//       Serial.println(" badelna el sentFlag successfully\n");
//     }
//   } else {
//     Serial.println("No Successful Sending message to MQTT topic !");
//   }
//   vTaskDelay(300);
//   return 0;

// }


// int (*callback_P)(void*, int, char**, char**) = callbackTranFunc;


// int (*callbackTranFuncPointer)(void*, int, char**, char**) = callbackTranFunc;


// void transmitFunc(void* pvParameters) {
//   Serial.print("transmit function task  running ");

//   for (;;) {
//     ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
//     Serial.println("FL TRANSMISSION TASK");
//     int rc1 = sqlite3_open("/sd/databaseTRY.db", &db);
//     if (rc1 == SQLITE_OK) {
//       rc1 = sqlite3_exec(db, "select * from BackupDB where sentFlag = 0 ;", callbackTranFunc, (void*)data, &zErrMsg);
//       Serial.print("ESP.getFreeHeap()");
//       Serial.println(ESP.getFreeHeap());
//       if (rc1 != SQLITE_OK) {
//         Serial.println("SQL error: manajmtch n selectionni les sentFlag a 0 ");
//         //sqlite3_free(zErrMsg);
//         Serial.printf("SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//       } else {
//         Serial.println("Operation done successfully\n");
//       }
//     } else {
//       Serial.println("database not open  ");
//     }
//     sqlite3_close(db);
//   }
// }



// void SdInitFunc(void* pvParameters) {
//   for (;;) {
//     Serial.println(" SD Init function ....... ");
//     ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
//     Serial.println(" CARD NOT MOUNTED W HANA DKHALNA NHWALOU ");
//     SD.end();
//     sdAttempts = 0;
//     while (sdAttempts < 1) {
//       if (SD.begin(CS_sd, spi_cd, 4000000)) {
//         Serial.println(" CARD MOUNTED ");
//         break;
//       }
//       Serial.println("Card Mount Failed");
//       sdAttempts++;
//       delay(100);
//     }
//     if (SD.begin(CS_sd, spi_cd, 4000000)) {
//       sdState = true;
//     } else {
//       sdState = false;
//     }
//     // sdState = (sdAttempts == 2) ? false : true;
//     Serial.print("Sd state is == **************************************  ");
//     Serial.println(sdState);
//   }
// }



// void processLogFilePrGW() {
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//     //SdInitFunc1();
//   }
//   Serial.print("J'ai entré dans le process du file ");
  
//   // zebda
// portENTER_CRITICAL(&TimeMux);
//   currentTime = currentTime + (millis() - offsetmillis )/1000; 
//   offsetmillis = millis();
// portEXIT_CRITICAL(&TimeMux);
// time_t epochTime = currentTime;
// Serial.println(currentTime);
   
// struct tm *timeinfo;
// timeinfo = gmtime(&epochTime); // Convertir epoch en date UTC

// int year = timeinfo->tm_year + 1900;
// Serial.println(year);
// int month = timeinfo->tm_mon + 1; // Janvier = 0, donc +1
// Serial.println(month);
// int day = timeinfo->tm_mday;
// Serial.println(day);
// int hour = timeinfo->tm_hour;  
// int minute = timeinfo->tm_min;
// int second = timeinfo->tm_sec;


//   // Create the file name in the format "YY/MM/DD_LogFile.txt"
//   char fileName[30];
//   snprintf(fileName, sizeof(fileName), "%02d_%02d_%02d_PrGwLF.txt", year, month, day);
//   String path = "/" + String(fileName);
//   const char* stringPath = path.c_str();
//   Serial.print(fileName);
//   if (!SD.exists(stringPath)) {
//     Serial.print(fileName);
//     Serial.println(F(" doesn't exist. please check what's wrong..."));
//   }

//   // Open the file in read mode
//   File logFile = SD.open(stringPath);
//   Serial.println("After opening file");

//   // Open the file
//   String dataBeforeDelimiter = "";

//   // Check if the file opened successfully
//   if (logFile) {
//     bool fileProcessed = false;  // Flag to track whether the file has been processed or not

//     // Read data from the file until there's nothing left
//     while (logFile.available() && !fileProcessed) {
//       // Read a character
//       char character = logFile.read();
//       if (character == '\n') {
//         // Print a newline character when the separator is found
//         Serial.println();
//         // For now, let's just print it
//         Serial.println("Data before delimiter: " + dataBeforeDelimiter);
//         //_____________ here we are going to send data to MQTT
//         const char* dataBeforeDelimiterMQTTT = dataBeforeDelimiter.c_str();
//         if(WiFi.status() != WL_CONNECTED){
//           reconnectWiFi();
//           }
//         if(!client.connected()){
//          reconnectMQTT();
//         }
//         if (client.publish(logFileQueue, dataBeforeDelimiterMQTTT)) {
//           // Success sending message
//           Serial.println("Success sending message");
//         } else {
//           // Error sending message to MQTT
//           Serial.println(F("Error sending Message to MQTT : "));
//           Serial.print(F("failed, rc="));
//           Serial.print(client.state());
//         }

//         // Reset the variable for the next set of data
//         dataBeforeDelimiter = "";
//       } else {
//         // Concatenate the character to the string variable
//         dataBeforeDelimiter += character;
//       }
//     }

//     // Close the file
//     logFile.close();

//     // Set the flag to indicate that the file has been processed
//     fileProcessed = true;
//   } else {
//     // If the file didn't open, print an error
//     Serial.println("Error opening file.");
//   }
// }

// bool fileProcessed = false;
// void processLogFile() {
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//     //SdInitFunc1();
//   }
//   Serial.print("J'ai entré dans le process du file ");

//   portENTER_CRITICAL(&TimeMux);
//   currentTime = currentTime + (millis() - offsetmillis )/1000; 
//   offsetmillis = millis();
//  portEXIT_CRITICAL(&TimeMux);

//  time_t epochTime = currentTime;
// Serial.println(currentTime);
   
// struct tm *timeinfo;
// timeinfo = gmtime(&epochTime); // Convertir epoch en date UTC

// int year = timeinfo->tm_year + 1900;
// Serial.println(year);
// int month = timeinfo->tm_mon + 1; // Janvier = 0, donc +1
// Serial.println(month);
// int day = timeinfo->tm_mday;
// Serial.println(day);
// int hour = timeinfo->tm_hour;  
// int minute = timeinfo->tm_min;
// int second = timeinfo->tm_sec;

   
   

//   char fileName[30];
//   snprintf(fileName, sizeof(fileName), "%02d_%02d_%02d_LogFile.txt", year, month, day);
//   String path = "/" + String(fileName);
//   const char* stringPath = path.c_str();
//   Serial.print(fileName);
//   if (!SD.exists(stringPath)) {
//     Serial.print(fileName);
//     Serial.println(F(" doesn't exist. please check what's wrong..."));
//   }

//   // Open the file in read mode
//   File logFile = SD.open(stringPath);
//   Serial.println("After opening file");

//   // Open the file
//   String dataBeforeDelimiter = "";

//   // Check if the file opened successfully
//   if (logFile) {
//     // Flag to track whether the file has been processed or not

//     // Read data from the file until there's nothing left
//     while (logFile.available() && !fileProcessed) {
//       // Read a character
//       char character = logFile.read();
//       if (character == '\n') {
//         // Print a newline character when the separator is found
//         Serial.println();
//         // For now, let's just print it
//         Serial.println("Data before delimiter: " + dataBeforeDelimiter);
//         //_____________ here we are going to send data to MQTT
//         const char* dataBeforeDelimiterMQTTT = dataBeforeDelimiter.c_str();
//         if(WiFi.status() != WL_CONNECTED){
//           reconnectWiFi();
//           }
//         if(!client.connected()){
//           reconnectMQTT();
//          }
//         //    if (!client.connected() || !client.subscribe("water_sec.data.health_check.e4dadf61-25f0-4914-82ab-39fdecb9dba5", 1)) {
//         //       xTaskNotify(mqttTask, 0, eNoAction);
//         //  }

//         if (client.publish(logFileQueue, dataBeforeDelimiterMQTTT)) {
//           // Success sending message
//           Serial.println("Success sending message");
//         } else {
//           // Error sending message to MQTT
//           Serial.println(F("Error sending Message to MQTT : "));
//           Serial.print(F("failed, rc="));
//           Serial.print(client.state());
//         }

//         // Reset the variable for the next set of data
//         dataBeforeDelimiter = "";
//       } else {
//         // Concatenate the character to the string variable
//         dataBeforeDelimiter += character;
//       }
//     }
//   }

//   // // Close the file
//   // logFile.close();

//   // // Set the flag to indicate that the file has been processed
//   // fileProcessed = true;
//   else {
//     // If the file didn't open, print an error
//     Serial.println("Error opening file.");
//   }
//   // Close the file
//   logFile.close();

//   // Set the flag to indicate that the file has been processed
//   fileProcessed = true;
// }


// void addElementToFile(const char* element, const char* value) {
//   // Mount Success, exit the loop
//   // Serial.println("Add element to file****************************");
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//     //SdInitFunc1();
//   }
//   if (sdState) {

//  portENTER_CRITICAL(&TimeMux);
//   currentTime = currentTime + (millis() - offsetmillis )/1000; 
//   offsetmillis = millis();
//  portEXIT_CRITICAL(&TimeMux);
// Serial.println(currentTime);
// time_t epochTime = currentTime;
// Serial.println(currentTime);
   
// struct tm *timeinfo;
// timeinfo = gmtime(&epochTime); // Convertir epoch en date UTC

// int year = timeinfo->tm_year + 1900;
// Serial.println(year);
// int month = timeinfo->tm_mon + 1; // Janvier = 0, donc +1
// Serial.println(month);
// int day = timeinfo->tm_mday;
// Serial.println(day);
// int hour = timeinfo->tm_hour;  
// int minute = timeinfo->tm_min;
// int second = timeinfo->tm_sec;



//     // Create the file name in the format "YY/MM/DD_LogFile.txt"
//     char fileName[30];
//     snprintf(fileName, sizeof(fileName), "%02d_%02d_%02d_LogFile.txt", year, month, day);
//     String path = "/" + String(fileName);
//     const char* stringPath = path.c_str();
//     if (!SD.exists(stringPath)) {
//       Serial.print(fileName);
//       Serial.println(F(" doesn't exist. Creating file..."));
//     }
//     // Open the file in append mode
//     File logFile = SD.open(stringPath, FILE_APPEND);
//     // Check if the file opened successfully
//     if (logFile) {
//       // Write the element and its value to the file
//       char dataDate[30];
//       snprintf(dataDate, sizeof(dataDate), "%02d-%02d-%02dT%02d:%02d:%02d ", year, month, day, hour, minute, second);
//       //2023-11-15T23:15:00 warning "last reboot power button"
//       String StringDataDate = String(dataDate);
//       const char* StringDataDatec = StringDataDate.c_str();
//       logFile.print(StringDataDatec);
//       logFile.print(element);
//       logFile.print(" ");
//       logFile.print("\"");
//       logFile.print(value);
//       logFile.print("\"");
//       logFile.print(" ");

//       logFile.println(GW_id);

//       String toPrint = StringDataDatec + String(element) + " " + "\"" + String(value) + "\"" + " " + GW_id;
//       Serial.println(toPrint);
//       // Close the file
//       logFile.close();
//       Serial.print("File name  : ");

//       Serial.println(fileName);
//       Serial.println("Element added to file successfully!");
//     } else {
//       Serial.println("Error opening file!");
//     }
//   }
// }


// // Function to convert DateTime to timestamp
// uint32_t dateTimeToTimestamp(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
//   struct tm timeinfo;

//   // Set the fields of the tm structure
//   timeinfo.tm_year = year - 1900;  // Years since 1900
//   timeinfo.tm_mon = month - 1;     // Months from 0 to 11
//   timeinfo.tm_mday = day;
//   timeinfo.tm_hour = hour;
//   timeinfo.tm_min = min;
//   timeinfo.tm_sec = sec;

//   // Convert to timestamp (seconds since epoch)
//   uint32_t timestamp = mktime(&timeinfo);

//   return timestamp;
// }

// // for transmission of the threasholds via LoRa to the private Gw
// int transmitData(const char* dataS) {
//   // Serial.println("transmitData ****************************");

//   // radio.setFrequency(440.0);
//   transmissionState = radio.startTransmit(dataS);  //will return packet length sent if OK, otherwise 0 if transmit error
//   if (transmittedFlag) {
//     transmittedFlag = false;
//     if (transmissionState == RADIOLIB_ERR_NONE) {
//       // packet was successfully sent
//       Serial.print("str= ");
//       Serial.println(dataS);
//       Serial.print("SUCCESS sending the data to the receiver  ");
//       return 1;
//     } else {
//       Serial.print(F("failed, code "));
//       Serial.println(transmissionState);
//       String stringSNR = "LoRa transmission Failed, CODE " + String(transmissionState);
//       const char* stringF = stringSNR.c_str();
//       addElementToFile("Critical", stringF);
//       return 0;
//     }
//   }
// }

// void SetLoRaTransMode(float freq) {
//   // Serial.println("SetLoRaTransMode ****************************");

//   int state = radio.begin();
//   if (state == RADIOLIB_ERR_NONE) {
//     Serial.println(F("success!"));
//   } else {
//     Serial.print(F("failed, code "));
//     Serial.println(state);
//     while (true)
//       ;
//   }
//   radio.setPacketSentAction(setFlagT);
//   Serial.print(F("[SX1278] Sending first packet ... "));
//   radio.setFrequency(freq);
//   radio.setBandwidth(125);
//   radio.setSpreadingFactor(12);
//   radio.setCodingRate(5);
//   radio.setOutputPower(20);
//   // transmissionState = radio.startTransmit("init done!");
//   // to transmit the data we have to the private gateway
//   Serial.println(" init to transmit the data we have to the private gateway done ");
// }

// void initializeAndListen(float listeningFreq) {
//   delay(33);
//   radio.setFrequency(listeningFreq);
//   radio.setBandwidth(125.0);
//   radio.setSpreadingFactor(12);
//   radio.setCodingRate(5);
//   radio.setOutputPower(20);
//   radio.setPacketReceivedAction(setFlag);
//   int state = radio.startReceive();
//   if (state != RADIOLIB_ERR_NONE) {
//     Serial.print(F("Lora listning failed, code "));
//     Serial.println(state);
//   } else {
//     Serial.print(F("[SX1278] Starting to listen ... "));

//     Serial.println(F("Lora listning success!"));
//   }
// }

// int callback_ack(void* data, int argc, char** argv, char** azColName) {
//   Serial.println("DKAAAALLLL LEL CALLBACKKKKKKKKKKKKKKKKKKKKKK  ____________________ ");

//   int i;
//   std::stringstream ss;
//   for (i = 1; i < argc; i++) {
//     ss << argv[i] << "/";
//   }

//   std::string Sensor_thre = ss.str();
//   Serial.print("ss.str()");
//   Serial.println(Sensor_thre.c_str());
//   std::string buffer(Sensor_thre.c_str());

//   std::string pr_id = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   Serial.println("this is the iddddd from processing the payload in HZ");
//   Serial.println(pr_id.c_str());

//   std::string pr_freq = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   Serial.println("this is the frequency from processing the payload in HZ");
//   Serial.println(pr_freq.c_str());

//   std::string s_id = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   std::string s_cons = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   std::string s_dur = buffer.substr(0, buffer.find(delimiter));
//   buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//   Serial.println("this is the duration from processing the payload in HZ");
//   Serial.println(s_dur.c_str());

//   if (s_id == sensor_id_ack && (s_cons != cons_ack || s_dur != dur_ack)) {
//     Serial.print(" we are suspending the data task heeeeeeeere fl if ");

//     // vTaskSuspend(Datatask);  // ___________________________ bch ta5laa lahnee !!!!!!!!!!!!!
//     //delay(1000);

//     float freqen = std::stoi(pr_freq) / 1000000;
//     Serial.print("la frequence est ");
//     Serial.println(freqen);
//     SetLoRaTransMode(freqen);
//     //delay(700);
//     std::string transString = "S/" + pr_id + "/" + s_id + "/" + s_cons + "/" + s_dur + "/";
//     //delay(3000);
//     const char* dataToTransmit1 = transString.c_str();
//     Serial.print("The data of the threasholds to tansmit is :");
//     Serial.println(String(dataToTransmit1));

//     transmitData(dataToTransmit1);
//     Serial.print("The data 1 to tansmit is :");
//     Serial.println(String(dataToTransmit1));
//     //delay(3500);

//     initializeAndListen(listeningFreq);
//     // vTaskResume(Datatask);
//     // Serial.println("Raja3na el data task te5dem  transmitterMode simple");
//   }


//   else if (s_id == sensor_id_ack && s_cons == cons_ack && s_dur == dur_ack) {
//       Serial.print(" we are fl elseeeeeeeeeeeeeeee, config done for the sensor");
//       DynamicJsonDocument docAck(128);
//       char outAck[128];
//       JsonObject ackThr = docAck.to<JsonObject>();  // Convert doc1 to a JsonObject
//       ackThr["sensor_id"] = s_id.c_str();
//       ackThr["duration"] = atoi(s_dur.c_str());
//       ackThr["consumption"] = atoi(s_cons.c_str());
//       ackThr["frequency"] = atol(pr_freq.c_str());
//       ackThr["card_id"] = pr_id.c_str();

//       size_t n1 = serializeJson(docAck, outAck);
//       Serial.println(F("Sending message to MQTT topic.."));
//       Serial.print(F("bytes = "));
//       Serial.println(n1, DEC);
//       Serial.println(outAck);
//       if(WiFi.status() != WL_CONNECTED){
//         reconnectWiFi();
//         }
//       if(!client.connected()){
//         reconnectMQTT();
//        }
//       if (client.publish(HealthCheckQueue, outAck, n1)) {
//         Serial.println("Success sending message");
//         delay(100);
//       }
//     }

//   return 0;
// }
// void sendDataMQTT() {
//   // Serial.println("send data mqtt ****************************");

//   sqlite3* db2;
//   DynamicJsonDocument doc1(128);
//   JsonObject data1;
//   std::string delim = "_";
//   std::string std_string = line_ID;

//   dateString = std_string.substr(0, std_string.find(delim));
//   std_string.erase(0, std_string.find(delim) + delim.length());


//   String arduinoStr = String(std_string.c_str());
//   Serial.print("this is the string  ");

//   Serial.println(arduinoStr);

//   int year = arduinoStr.substring(0, 4).toInt();
//   int month = arduinoStr.substring(5, 7).toInt();
//   int day = arduinoStr.substring(8, 10).toInt();
//   int hour = arduinoStr.substring(11, 13).toInt();
//   int minute = arduinoStr.substring(14, 16).toInt();
//   int second = arduinoStr.substring(17, 19).toInt();

//   Serial.print("Year: ");
//   Serial.println(year);
//   Serial.print("Month: ");
//   Serial.println(month);
//   Serial.print("Day: ");
//   Serial.println(day);
//   Serial.print("Hour: ");
//   Serial.println(hour);
//   Serial.print("Minute: ");
//   Serial.println(minute);
//   Serial.print("Second: ");
//   Serial.println(second);

//  // DateTime dt(year, month, day, hour, minute, second);
//   // DateTime dt(2024, 1, 25, 12, 30, 45);
//   uint32_t timestamp = dateTimeToTimestamp(year, month, day, hour, minute, second);
//   Serial.print("Timestamp: ");
//   Serial.println(timestamp);
//   times = std::to_string(timestamp);
//   char out1[128];
//   data1 = doc1.createNestedObject(F("data"));

//   doc1["device"] = Sensor_ID;
//   data1["consumption"] = consumption;
//   data1["time"] = times;
//   data1["period"] = duration;
//   size_t n1 = serializeJson(doc1, out1);
//   Serial.println(F("Sending message to MQTT topic.."));
//   Serial.print(F("bytes = "));
//   Serial.println(n1, DEC);
//   Serial.println(out1);
//   if(WiFi.status() != WL_CONNECTED){
//     reconnectWiFi();
//     }
//   if(!client.connected()){
//     reconnectMQTT();
//    }
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//   }
//   if (client.publish(DataQueue, out1, n1)) {
//     //save a few CPU cycles by passing the size of the payload
//     Serial.println("Success sending message");

//     delay(10);
//     Serial.println("here we will send data to mqtt which was not sent before, we are sending the notification to the taskk to start ");
//     xTaskNotify(transmitTask, 0, eNoAction);
//     if (sdState) {
//       int rc1 = sqlite3_open("/sd/databaseTRY.db", &db2);
//       if (rc1 == SQLITE_OK) {
//         Serial.println("D5alna lel data base and we are inserting  ");
//         std::stringstream ss;
//         ss << "'" << line_ID << "', '" << card_freq << "', '" << Sensor_ID << "', '" << consumption << "', '" << times << "', '" << duration << "', " << 1 << ", " << 0;
//         std::string SqlQuery = "INSERT INTO BackupDB ( line_ID, card_freq,  Sensor_ID, consumption, times , duration, sentFlag, acked) VALUES (" + ss.str() + ");";
//         int rc2 = sqlite3_exec(db2, SqlQuery.c_str(), NULL, NULL, NULL);

//         Serial.print("ESP.getFreeHeap()");
//         Serial.println(ESP.getFreeHeap());

//         if (rc2 != SQLITE_OK) {
//           Serial.println("Berrasmi fl Tab3aaaaaa  ");
//           std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db2) << std::endl;
//           sdState = false;
//         } else {
//           Serial.println("insertion doneeeeeeeeeeeeeeeeeeee ");
//           // sdState = true;
//         }
//       } else {

//         Serial.println("database not open aaaaaaaaaaaaaaaaaaaaaaaaa ");
//         sdState = false;
//       }
//     }
//     sqlite3_close(db2);
//     Serial.println("sakarna el Data Base");

//   } else {
//     Serial.println(F("Error sending message"));
//     Serial.print(F("failed, rc="));
//     Serial.println(client.state());
//     if (sdState) {
//       int rc1 = sqlite3_open("/sd/databaseTRY.db", &db2);
//       if (rc1 == SQLITE_OK) {
//         Serial.println("D5alna to insert fl database dans le cas taa not sent mqtt  ");
//         std::stringstream ss;
//         ss << "'" << line_ID << "', '" << card_freq << "', '" << Sensor_ID << "', '" << consumption << "', '" << times << "', '" << duration << "', " << 0 << ", " << 0;
//         std::string SqlQuery = "INSERT INTO BackupDB ( line_ID, card_freq,  Sensor_ID, consumption, times , duration, sentFlag, acked) VALUES (" + ss.str() + ");";
//         int rc2 = sqlite3_exec(db2, SqlQuery.c_str(), NULL, NULL, NULL);
//         Serial.print("ESP.getFreeHeap()");

//         Serial.println(ESP.getFreeHeap());
//         if (rc2 != SQLITE_OK) {
//           Serial.println("Berrasmi fl Tab3a taw  ");
//           std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db2) << std::endl;
//         } else {
//           Serial.println("cbnnnnnnnnnnnnnnnnnnnnnnnn  ");
//         }
//       } else {
//         Serial.println("cbnnnnnnnnnnnnnnnnnnnnnnnn error  ");
//       }
//     }
//     Serial.println("sakarna el Data Base");
//     sqlite3_close(db2);
//   }

//   Serial.println(F("-------------"));
//   doc1.clear();
// }




// String millisToPeriod(unsigned long millisValue) {
//   unsigned long seconds = millisValue / 1000;
//   unsigned long minutes = seconds / 60;
//   unsigned long hours = minutes / 60;
//   unsigned long days = hours / 24;
//   String periodString = String(days) + "d" + String(hours % 24) + "h" + String(minutes % 60) + "m" + String(seconds % 60) + "s";
//   return periodString;
// }

// void addLOGlineToFile(const char* element) {  // add elements in the log file for debug
//   Serial.println("addLOGlineToFile ****************************");
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//     //SdInitFunc1();
//   }
//   if (sdState) {

//     portENTER_CRITICAL(&TimeMux);
//     currentTime = currentTime + (millis() - offsetmillis )/1000; 
//     offsetmillis = millis();
//     portEXIT_CRITICAL(&TimeMux);

//     time_t epochTime = currentTime;
// Serial.println(currentTime);
   
// struct tm *timeinfo;
// timeinfo = gmtime(&epochTime); // Convertir epoch en date UTC

// int year = timeinfo->tm_year + 1900;
// Serial.println(year);
// int month = timeinfo->tm_mon + 1; // Janvier = 0, donc +1
// Serial.println(month);
// int day = timeinfo->tm_mday;
// Serial.println(day);
// int hour = timeinfo->tm_hour;  
// int minute = timeinfo->tm_min;
// int second = timeinfo->tm_sec;


//     // Create the file name in the format "YY/MM/DD_LogFile.txt"
//     char fileName[30];
//     snprintf(fileName, sizeof(fileName), "%02d_%02d_%02d_PrGwLF.txt", year, month, day);
//     String path = "/" + String(fileName);
//     const char* stringPath = path.c_str();
//     if (!SD.exists(stringPath)) {
//       Serial.print(fileName);
//       Serial.println(F(" doesn't exist. Creating file..."));
//     }
//     File logFile = SD.open(stringPath, FILE_APPEND);
//     if (logFile) {
//       logFile.print(element);
//       logFile.print(" ");
//       // logFile.print("\"");
//       logFile.println(GW_name);
//       // logFile.println("\"");
//       // Close the file
//       logFile.close();
//       Serial.println("Element log line  added to file successfully!");
//     } else {
//       Serial.println("Error opening file in log line from pr gw!");
//     }
//   }
// }

// void sendNotifMQTT() {
//   DynamicJsonDocument doc1(128);
//   char out1[128];

//   JsonObject notification = doc1.to<JsonObject>();  // Convert doc1 to a JsonObject

//   notification["sensor_id"] = notifSensorID;
//   notification["type"] = notifType;
//   notification["value"] = notifValue;
//   notification["date"] = notifDate;

//   size_t n1 = serializeJson(doc1, out1);
//   Serial.println(F("Sending message to MQTT topic.."));
//   Serial.print(F("bytes = "));
//   Serial.println(n1, DEC);
//   Serial.println(out1);
//   if(WiFi.status() != WL_CONNECTED){
//     reconnectWiFi();
//     }
//   if(!client.connected()){
//     reconnectMQTT();
//    }
//   if (client.publish(NotifsQueue, out1, n1)) {
//     Serial.println("Success sending message");
//     delay(100);
//   }
// }

// void sendHCMQTT() {
//   DynamicJsonDocument docHC(128);
//   char outHC[128];

//   JsonObject healthCheck = docHC.to<JsonObject>();  // Convert doc1 to a JsonObject

//   healthCheck["card_id"] = card_id_hc;
//   healthCheck["token"] = token_hc;

//   size_t n1 = serializeJson(docHC, outHC);
//   Serial.println(F("Sending message to MQTT topic.."));
//   Serial.print(F("bytes = "));
//   Serial.println(n1, DEC);
//   Serial.println(outHC);
//   if(WiFi.status() != WL_CONNECTED){
//     reconnectWiFi();
//     }
//   if(!client.connected()){
//     reconnectMQTT();
//    }

//   if (client.publish(HealthCheckQueue, outHC, n1)) {
//     Serial.println("Success sending message");
//     delay(100);
//   }
// }


// sqlite3* db_ack;
// void sendAckTHmqtt() {

//   int rc1 = sqlite3_open("/sd/threasholdsDB.db", &db_ack);
//   if (rc1 == SQLITE_OK) {
//     std::string selectQuery = "SELECT * FROM ThreashDB WHERE sensor_id = '" + sensor_id_ack + "'";
//     Serial.print(selectQuery.c_str());
//     int rc = sqlite3_exec(db_ack, selectQuery.c_str(), callback_ack, NULL, NULL);
//     Serial.print("ESP.getFreeHeap()");
//     Serial.println(ESP.getFreeHeap());
//     if (rc1 != SQLITE_OK) {
//       Serial.println("SQL error: manajmtch n selectionni les sentFlag a 0 ");
//       //sqlite3_free(zErrMsg);
//       Serial.printf("SQL error: %s\n", zErrMsg);
//       sqlite3_free(zErrMsg);
//     } else {
//       Serial.println("Operation done successfully\n");
//     }
//   } else {
//     Serial.println("database not open  ");
//   }
//   sqlite3_close(db_ack);
// }

// void Data(void* pvParameters) {
//   Serial.print("Data running on core :");
//   Serial.println(xPortGetCoreID());
//   for (;;) {
//     if (receivedFlag) {
//       receivedFlag = false;
//       String str;

//       int state = radio.readData(str);
//       RSSI = radio.getRSSI();
//       Serial.println(F("[SX1278] Received packet!"));
//       Serial.print(F("[SX1278] Data:\t\t"));
//       Serial.println(str);
//       Serial.print(F("[SX1278] RSSI:\t\t"));
//       Serial.print(RSSI);
//       Serial.println(F(" dBm"));
//       Serial.print(F("[SX1278] SNR:\t\t"));
//       Serial.print(radio.getSNR());
//       Serial.println(F(" dB"));

//       if (state == RADIOLIB_ERR_NONE) {

//         String stringSNR = "LoRa SNR " + String(RSSI);
//         const char* stringSNRc = stringSNR.c_str();
//         addElementToFile("Debug", stringSNRc);
//         std::string buffer(str.c_str());
//         str = "";


//         indicator = buffer.substr(0, buffer.find(delimiter));
//         buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//         if (indicator == "D") {
//           card_freq = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//           line_ID = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//           consumption = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//           duration = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//           Sensor_ID = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           sendDataMQTT();

//         } else if (indicator == "L") {
//           logLine = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           addLOGlineToFile(logLine.c_str());
//         } else if (indicator == "test") {
//           Serial.print(F(" WE HAVE THE FREQUENCY; E9LEB MODE TRANSMITTER "));

//           frequency = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           prGW_id = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//           int frequencyInt = std::stoi(frequency);
//           Serial.println(F("we extracted the frequency from the trame and we are notifying the transmitFuncInventaireTask "));
//           xTaskNotify(transmitFuncInventaireTask, frequencyInt, eSetValueWithoutOverwrite);
//         } else if (indicator == "T") {
//           frequency = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           int frequencyInt = std::stoi(frequency);
//           Serial.println(F("we extracted the frequency from the trame and we are notifying the transmitFuncInventaireTask "));
//           xTaskNotify(transmitFuncTimeTask, frequencyInt, eSetValueWithoutOverwrite);

//         } else if (indicator == "N") {
//           notifSensorID = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           notifType = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           notifValue = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           notifDate = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());

//           sendNotifMQTT();
//         } else if (indicator == "HC") {
//           card_id_hc = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           token_hc = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           sendHCMQTT();
//         } else if (indicator == "S") {
//           std::string card_id_ack = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           sensor_id_ack = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           cons_ack = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           dur_ack = buffer.substr(0, buffer.find(delimiter));
//           buffer.erase(0, buffer.find(delimiter) + delimiter.length());
//           sendAckTHmqtt();
//         } else {
//           Serial.println(F("Data erroneé !!!!!!!!!!!!!"));
//           addElementToFile("Critical", str.c_str());
//         }
//       } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
//         Serial.println(F("[SX1278] CRC error!"));
//         // CRC_Error_LogInFile();
//         addElementToFile("Critical", str.c_str());
//       } else {
//         Serial.print(F("[SX1278] Failed, code "));
//         Serial.println(state);
//       }
//     }
//   }
//   vTaskDelay(pdMS_TO_TICKS(60));
// }





// void transmitterModeTime(void* pvParameters) {
//   // Serial.println("transmitterMode of time  ****************************");
//   for (;;) {
//     uint32_t freqHZ = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // i am going to recieve the frequency en HZ
//     float freq = freqHZ / 1000000;
//     Serial.print("la frequence est ");
//     Serial.println(freq);
//     Serial.println("----------------------- we are suspending the data task ");
//     vTaskSuspend(Datatask);
//     Serial.println("----------------------- DATA Suspended");
//     SetLoRaTransMode(freq);
//     //delay(200);
    


//     portENTER_CRITICAL(&TimeMux);
//   currentTime = currentTime + (millis() - offsetmillis )/1000; 
//   offsetmillis = millis();
//    portEXIT_CRITICAL(&TimeMux);
     
//     if (currentTime > 100000) {
//       // String  = current.toString();
//       std::string transString = std::to_string(currentTime);

//       const char* dataToTransmit1 = transString.c_str();
//       String dataToTransmitWithPrefix = "T/" + String(dataToTransmit1);

//       Serial.print("The Time to tansmit is :");
//       Serial.println(String(dataToTransmit1));
//       transmitData(dataToTransmitWithPrefix.c_str());
//      // delay(1500);
//     } else {
//       ;
//       delay(200);
//     }
//     initializeAndListen(listeningFreq);
//     vTaskResume(Datatask);
//     Serial.println("Raja3na el data task te5dem  transmitterModeTime");
//   }
// }








// void connectToWiFi() {
//   WiFi.begin(ssid, password);
//   int TryCount = 0;

//   while (WiFi.status() != WL_CONNECTED && TryCount < 5 && WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
//     Serial.println("Connecting to WiFi..");
//     TryCount++;
//     //WiFi.disconnect();
//     //WiFi.begin(ssid, password);
//     delay(2000);
//   }
//   if (WiFi.status() == WL_CONNECTED) {
//     wifiStartTime = millis();
//     Serial.print(" _________________________ wifiStartTime :  ");
//     Serial.println(wifiStartTime);
//     Serial.println("Puissance Signal Wifi : ");
//     Serial.println(WiFi.RSSI());
//   }
// }




// void WiFiXmqttFunc(void* parameter) {
//   for (;;) {
//     Serial.println("We are checking the WiFi connexion and MQTT");
//     if (WiFi.status() != WL_CONNECTED) {
//           reconnectWiFi();
//     }
//     if(!client.connected()){
//       reconnectMQTT();
//      }

//     timeClient.begin();
//     timeClient.update();
//     vTaskDelay(1000);
//     currentTimetemp = timeClient.getEpochTime();
//     if(currentTimetemp > 1000000){
//     portENTER_CRITICAL(&TimeMux);
//       currentTime = timeClient.getEpochTime();
//       offsetmillis = millis();
//     portEXIT_CRITICAL(&TimeMux);
//     Serial.println("time from NTP à jour :");
//     Serial.println(currentTime);}
//     vTaskDelay(pdMS_TO_TICKS(300000));  //every 5 minutes
//   }
// }


// sqlite3* db_th;
// int nbSensorid = 0;
// int callbackTH(void* data, int argc, char** argv, char** azColName) {
//   nbSensorid = atoi(argv[0]);
//   Serial.println("The number of sensoresssss is ");
//   Serial.println(nbSensorid);
//   if (nbSensorid == 1) {
//     Serial.println("Alreadyyyy existtttttttttttt");
//     // Row with sensor_id exists, perform UPDATE
//     std::stringstream updateSS;
//     updateSS << "UPDATE ThreashDB SET consumption = '" << consumptionTH << "', duration = '" << timeTH << "' WHERE sensor_id = '" << std::string(sensorIDTH.c_str()) << "'";
//     std::string updateQuery = updateSS.str();
//     int rc = sqlite3_exec(db_th, updateQuery.c_str(), NULL, NULL, NULL);
//     // if (rc != SQLITE_OK) {
//     //   std::cerr << "Error updating row: " << sqlite3_errmsg(db_th) << std::endl;
//     // }
//   }
//   return 0;
// }

// void processMqttPayload(const String& payload) {
//   // const char* dataToTransmit;
//   Serial.print("Processing MQTT payload: ");
//   Serial.println(payload);
//   std::string payloadP(payload.c_str());

//   DynamicJsonDocument jsonDoc(200);  // Use DynamicJsonDocument for String
//   deserializeJson(jsonDoc, payload);
//   indicatorMQTT = jsonDoc["indicator"];

//   if (indicatorMQTT == 1) {  // THREAS
//     // Extract values
//     sensorIDTH = jsonDoc["sensor_id"].as<String>();
//     timeTH = jsonDoc["duration"];
//     ;
//     consumptionTH = jsonDoc["consumption"];
//     freq = jsonDoc["frequency"];
//     cardIDTH = jsonDoc["card_id"].as<String>();
//     ;

//     Serial.println("this is the frequency from processing the payload in HZ");
//     Serial.println(freq);

//     Serial.println("this is the cardID from processing the payload ");
//     Serial.println(cardIDTH);

//     Serial.println("this is the SensorID from processing the payload ");
//     Serial.println(sensorIDTH);

//     Serial.println("this is the timeTH from processing the payload ");
//     Serial.println(timeTH);

//     Serial.println("this is the consumptionTH from processing the payload ");
//     Serial.println(consumptionTH);
//     delay(50);

//     if (!sdState) {
//       Serial.println("card not mounted");
//       xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//       //SdInitFunc1();
//     }


//     if (sdState) {
//       // Open the SQLite database
//       int rc1 = sqlite3_open("/sd/threasholdsDB.db", &db_th);
//       if (rc1 == SQLITE_OK) {
//         Serial.println("we are selecting ...................");
//         // Check if sensor_id already exists
//         std::string selectQuery = "SELECT COUNT (*) FROM ThreashDB WHERE sensor_id = '" + std::string(sensorIDTH.c_str()) + "'";
//         int rc = sqlite3_exec(db_th, selectQuery.c_str(), callbackTH, NULL, NULL);
//         // Serial.print("the select query retuuuuuurnss rc = ");
//         // Serial.println(rc);
//         // if (rc != SQLITE_OK) {
//         //   std::cerr << "Error executing SELECT statement: " << sqlite3_errmsg(db_th) << std::endl;
//         // } else {

//         // }
//         if (nbSensorid == 0) {
//           Serial.println("raw testina w mch mawjoud, hana bch nzidouh --------------");
//           // Row with sensor_id does not exist, perform INSERT
//           Serial.println("We are inserting Threasholds in the Database");
//           std::stringstream ss;
//           ss << "'" << std::string(cardIDTH.c_str()) << "', '" << freq << "', '" << std::string(sensorIDTH.c_str()) << "', '" << consumptionTH << "', '" << timeTH << "'";
//           std::string SqlQuery = "INSERT INTO ThreashDB (card_id, card_freq, sensor_id, consumption, duration) VALUES (" + ss.str() + ");";
//           Serial.println(SqlQuery.c_str());
//           int rc2 = sqlite3_exec(db_th, SqlQuery.c_str(), NULL, NULL, NULL);

//           // Check if the insertion was successful
//           if (rc2 != SQLITE_OK) {
//             Serial.println("Error executing SQL query for insertion of thresholds");
//             std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db_th) << std::endl;
//             sdState = false;
//           } else {
//             Serial.println("Insertion done for thresholds");
//           }
//         }
//         // Close the database connection
//         sqlite3_close(db_th);
//       } else {
//         Serial.println("Error opening database for thresholds");
//         sdState = false;
//       }
//     }

//     // ____________________________________  we are going to enter the mode sender
//     Serial.println("----------------------- we are suspending the data task ");
//     // delay(2000);
//     vTaskSuspend(Datatask);  // ___________________________ bch ta5laa lahnee !!!!!!!!!!!!!
//     delay(1000);

//     float freqen = freq / 1000000;
//     Serial.print("la frequence est ");
//     Serial.println(freqen);
//     SetLoRaTransMode(freqen);
//     //delay(700);
//     String transString = "S/" + cardIDTH + "/" + sensorIDTH + "/" + String(consumptionTH) + "/" + String(timeTH) + "/";
//     //delay(3000);
//     const char* dataToTransmit1 = transString.c_str();
//     Serial.print("The data of the threasholds to tansmit is :");
//     Serial.println(String(dataToTransmit1));

//     transmitData(dataToTransmit1);
//     Serial.print("The data 1 to tansmit is :");
//     Serial.println(String(dataToTransmit1));
//     //delay(3500);

//     initializeAndListen(listeningFreq);
//     vTaskResume(Datatask);
//     Serial.println("Raja3na el data task te5dem  transmitterMode simple");
//     // xTaskNotify(transmitterModeTask, freq, eSetValueWithOverwrite);
//   } else if (indicatorMQTT == 2) {  // HEALTH CHECK
//     // Extract values
//     cardIdHC = jsonDoc["card_id"].as<String>();
//     freqHC = jsonDoc["frequency"];
//     ;
//     token = jsonDoc["token"].as<String>();
//     Serial.println("this is the frequency from processing the payload in HZ");
//     Serial.println(freqHC);

//     Serial.println("this is the cardID from processing the payload ");
//     Serial.println(cardIdHC);

//     Serial.println("this is the token from processing the payload ");
//     Serial.println(token);
//     if (cardIdHC == GW_id) {
//       DynamicJsonDocument docHC(128);
//       char outHC[128];

//       JsonObject healthCheck = docHC.to<JsonObject>();  // Convert doc1 to a JsonObject

//       healthCheck["card_id"] = cardIdHC;
//       healthCheck["token"] = token;

//       size_t n1 = serializeJson(docHC, outHC);
//       Serial.println(F("Sending message to MQTT topic.."));
//       Serial.print(F("bytes = "));
//       Serial.println(n1, DEC);
//       Serial.println(outHC);
//       if(WiFi.status() != WL_CONNECTED){
//         reconnectWiFi();
//         }
//       if(!client.connected()){
//         reconnectMQTT();
//        }

//       if (client.publish(HealthCheckQueue, outHC, n1)) {
//         Serial.println("Success sending message");
//         delay(100);
//       }
//     } else {
//       // ____________________________________  we are going to enter the mode sender
//       Serial.println("----------------------- we are suspending the data task ");
//       vTaskSuspend(Datatask);  // ___________________________ bch ta5laa lahnee !!!!!!!!!!!!!
//       delay(1000);
//       float freq = freqHC / 1000000;
//       Serial.print("la frequence est ");
//       Serial.println(freq);
//       SetLoRaTransMode(freq);
//      // delay(700);
//       String transString = "HC/" + cardIdHC + "/" + token + "/";
//      // delay(3000);
//       const char* dataToTransmit1 = transString.c_str();
//       Serial.print("The data of the threasholds to tansmit is :");
//       Serial.println(String(dataToTransmit1));
//       transmitData(dataToTransmit1);
//       Serial.print("The data 1 to tansmit is :");
//       Serial.println(String(dataToTransmit1));
//       //delay(2000);
//       initializeAndListen(listeningFreq);
//       vTaskResume(Datatask);
//       Serial.println("Raja3na el data task te5dem");
//     }
//   } else if (indicatorMQTT == 3) {  // Inventaire
//     // {"indicator": 2,"frequency":440000000}

//     freqInv = jsonDoc["frequency"];


//     Serial.println("this is the frequency from processing the payload in HZ");
//     Serial.println(freqInv);

//     delay(50);
//     // ____________________________________  we are going to enter the mode sender
//     Serial.println("----------------------- we are suspending the data task ");
//     // delay(2000);
//     vTaskSuspend(Datatask);  // ___________________________ bch ta5laa lahnee !!!!!!!!!!!!!
//     delay(1000);

//     float freqen = freqInv / 1000000;
//     Serial.print("la frequence est ");
//     Serial.println(freqen);
//     SetLoRaTransMode(freqen);
//     delay(700);
//     String transString = "TESTBU/";
//     delay(3000);
//     const char* dataToTransmit1 = transString.c_str();
//     Serial.print("The data of the threasholds to tansmit is :");
//     Serial.println(String(dataToTransmit1));

//     transmitData(dataToTransmit1);
//     Serial.print("The data 1 to tansmit is :");
//     Serial.println(String(dataToTransmit1));
//     delay(2000);

//     initializeAndListen(listeningFreq);
//     vTaskResume(Datatask);
//     Serial.println("Raja3na el data task te5dem  transmitterMode simple");
//     // xTaskNotify(transmitterModeTask, freq, eSetValueWithOverwrite);
//   }

//   else if (indicatorMQTT == 4) {
//     processLogFile();
//     Serial.println("*************************************___After process");
//     processLogFilePrGW();
//   }


//   else if (indicatorMQTT == 5) {  // HEALTH CHECK
//     // Extract values
//     cardIdHC = jsonDoc["card_id"].as<String>();
//     freqHC = jsonDoc["frequency"];
//     ;
//     Serial.println("this is the frequency from processing the payload in HZ");
//     Serial.println(freqHC);

//     Serial.println("this is the cardID from processing the payload ");
//     Serial.println(cardIdHC);

//     if (cardIdHC == GW_id) {
//       ESP.restart();
//     } else {
//       // ____________________________________  we are going to enter the mode sender
//       Serial.println("----------------------- we are suspending the data task ");
//       vTaskSuspend(Datatask);  // ___________________________ bch ta5laa lahnee !!!!!!!!!!!!!
//      // delay(1000);
//       float freq = freqHC / 1000000;
//       Serial.print("la frequence est ");
//       Serial.println(freq);
//       SetLoRaTransMode(freq);
//      // delay(700);
//       String transString = "RESET/" + cardIdHC + "/";
//      // delay(3000);
//       const char* dataToTransmit1 = transString.c_str();
//       Serial.print("The data of the threasholds to tansmit is :");
//       Serial.println(String(dataToTransmit1));
//       transmitData(dataToTransmit1);
//       Serial.print("The data 1 to tansmit is :");
//       Serial.println(String(dataToTransmit1));
//      // delay(2000);
//       initializeAndListen(listeningFreq);
//       vTaskResume(Datatask);
//       Serial.println("Raja3na el data task te5dem");
//     }
//   }
// }




// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message arrived in topic: ");
//   Serial.println(topic);

//   Serial.print("Message:");
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)payload[i]);
//     mqttPayload += (char)payload[i];
//   }
//   // if (mqttPayload.length() > 0) {
//   processMqttPayload(mqttPayload);
//   mqttPayload = "";
//   // }
//   Serial.println();
//   Serial.println("-----------------------");
// }






// void transmitterMode(void* pvParameters) {
//   Serial.println("transmitterMode ****************************");

//   for (;;) {
//     uint32_t freqHZ = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // i am going to recieve the frequency en HZ
//     float freq = freqHZ / 1000000;
//     Serial.print("la frequence est ");
//     Serial.println(freq);
//     SetLoRaTransMode(freq);
//     delay(700);
//     String transString = "S/" + cardIDTH + "/" + sensorIDTH + "/" + String(consumptionTH) + "/" + String(timeTH) + "/";
//     delay(3000);
//     const char* dataToTransmit1 = transString.c_str();
//     Serial.print("The data of the threasholds to tansmit is :");
//     Serial.println(String(dataToTransmit1));

//     transmitData(dataToTransmit1);
//     Serial.print("The data 1 to tansmit is :");
//     Serial.println(String(dataToTransmit1));
//     delay(3500);

//     initializeAndListen(listeningFreq);
//     vTaskResume(Datatask);
//     Serial.println("Raja3na el data task te5dem  transmitterMode simple");
//   }
// }


// //___________________________________________________________________________________________________________
// std::string linestocheck;
// std::string Last_id_selected;
// int last_row_fetched = 0;
// int Last_id_auto = 0;
// int first_id_auto = 0;
// sqlite3* dbi;
// int offset = 0;
// int flag_callbackfunction = 0;

// int callbackbackup(void* data, int argc, char** argv, char** azColName) {
//   Serial.println(" ++++++++++++++++++++  Callback function of test backup ++++++++++++++++");
//   std::string currentLine(argv[1]);

//   Serial.print("--> Offffseeeet fil backup  ====  ");
//   Serial.print(offset);
//   delay(500);
//   if (!linestocheck.empty()) {
//     linestocheck.append("/");
//   }
//   linestocheck.append(currentLine);

//   Serial.print(" Lined to Send id :::::: ");
//   Serial.println(linestocheck.c_str());
//   // update checked flag
//   std::string SqlQuery = "UPDATE BackupDB SET acked = 1 WHERE line_ID ='" + currentLine + "';";
//   int rc1 = sqlite3_exec(dbi, SqlQuery.c_str(), NULL, (void*)data, &zErrMsg);
//   Serial.print("rc1 = ");
//   Serial.println(rc1);
//   if (rc1 != SQLITE_OK) {
//     Serial.println("SQL error Update checked column :: ");
//     sqlite3_free(zErrMsg);
//   } else {
//     Serial.println(" badelna el acked to 1 successfully\n");
//   }
//   offset = atoi(argv[0]);
//   flag_callbackfunction = 1;
//   return 0;
// }



// int flag_id = 0;
// std::string first_id;
// std::string Last_id;

// int callbackFirstid(void* data, int argc, char** argv, char** azColName) {
//   if (flag_id == 1) {
//     Serial.println(" ******************Calllbaack Firrrst Id Fuunctioon**********************");
//     first_id = std::string(argv[1]);
//     first_id_auto = atoi(argv[0]);
//     Serial.print("Fiirst id is ");
//     Serial.println(first_id.c_str());
//     Serial.print("  ,,,,, First id num row is  ");
//     Serial.println(first_id_auto);
//     flag_id = 0;
//     return 0;
//   }
//   if (flag_id == 0) {
//     Serial.println(" ******************Calllbaack Laaaast Id Fuunctioon**********************");
//     Last_id = std::string(argv[1]);
//     Last_id_auto = atoi(argv[0]);
//     Serial.print("Last id is ");
//     Serial.print(Last_id.c_str());
//     Serial.print("  ,,,,, Last id num row is  ");
//     Serial.println(Last_id_auto);
//     return 0;
//   }
// }



// void send_test_back_up(uint32_t freqValue) {
//   // id board
//   offset = 0;
//   flag_id = 1;
//   int limit = 3;
//   // char* id_board = prGW_id.c_str();
//   std::string id_board = prGW_id;
//   std::string todayDate;
//   std::string xStr = std::to_string(freqValue);
//   std::string xStrl = std::to_string(limit);
  
//   portENTER_CRITICAL(&TimeMux);
//   currentTime = currentTime + (millis() - offsetmillis )/1000; 
//   offsetmillis = millis();
// portEXIT_CRITICAL(&TimeMux);
 
// time_t epochTime = currentTime;
// Serial.println(currentTime);
   
// struct tm *timeinfo;
// timeinfo = gmtime(&epochTime); // Convertir epoch en date UTC

// int year = timeinfo->tm_year + 1900;
// Serial.println(year);
// int month = timeinfo->tm_mon + 1; // Janvier = 0, donc +1
// Serial.println(month);
// int day = timeinfo->tm_mday;
// Serial.println(day);
// int hour = timeinfo->tm_hour;  
// int minute = timeinfo->tm_min;
// int second = timeinfo->tm_sec;


//   // Create the file name in the format "YY/MM/DD_LogFile.txt"
//   char tempDate[20];
//   snprintf(tempDate, sizeof(tempDate), "%02d-%02d-%02d", year, month, day);
//   todayDate = tempDate;
//   // char tempppDate[11] = "2024-01-26";
//   std::string identifier = id_board + "_" + tempDate;

//   Serial.print("-------------------------- First ID to be extracted--------------------- ");
//   Serial.println(identifier.c_str());

//   float freq = freqValue / 1000000;
//   Serial.print("la frequence est dans l inventaire = ");
//   Serial.println(freq);
//   SetLoRaTransMode(freq);

//   int rc1 = sqlite3_open("/sd/databaseTRY.db", &dbi);
//   // TEST PURPOSES
//   std::string selectFirstIdQuery = "SELECT * FROM BackupDB WHERE card_freq = " + xStr + " AND line_ID LIKE '" + identifier + "%' LIMIT 1;";
//   Serial.println(selectFirstIdQuery.c_str());
//   int rc = sqlite3_exec(dbi, selectFirstIdQuery.c_str(), callbackFirstid, (void*)data, &zErrMsg);
//   if (rc != SQLITE_OK) {
//     Serial.println("SQL error Select Fiirst  id  ");
//     sqlite3_free(zErrMsg);
//   } else {
//     Serial.print(" Select First id successfully :: ");
//     Serial.println(first_id.c_str());
//   }

//   // Last id to extracted
//   Serial.print("-------------------------- Last ID to be extracted--------------------- ");
//   std::string selectLastIdQuery = "SELECT * FROM BackupDB WHERE card_freq = " + xStr + " AND line_ID LIKE '" + identifier + "%' ORDER BY row DESC LIMIT 1;";
//   Serial.println(selectLastIdQuery.c_str());
//   int rc2 = sqlite3_exec(dbi, selectLastIdQuery.c_str(), callbackFirstid, (void*)data, &zErrMsg);
//   if (rc2 != SQLITE_OK) {
//     Serial.println("SQL error Select last id  ");
//     sqlite3_free(zErrMsg);
//   } else {
//     Serial.print(" Select Last id successfully :: ");
//     Serial.println(first_id.c_str());
//   }
//   sqlite3_close(dbi);

//   while (offset < Last_id_auto) {
//     flag_callbackfunction = 0;
//     Serial.println(" ----------------------------- WHILE --------------------------------");
//     int rc = sqlite3_open("/sd/databaseTRY.db", &dbi);  //acked = 0  and
//     std::string selectQuery2 = "SELECT * FROM BackupDB WHERE card_freq = " + xStr + " AND line_ID LIKE '" + identifier + "%' ORDER BY row LIMIT " + xStrl + " OFFSET " + std::to_string(offset) + ";";
//     // std::string selectQuery2 = "select * from sensors where sent = 1 and id_Line like '" + identifier + "%' LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

//     Serial.println(selectQuery2.c_str());
//     rc = sqlite3_exec(dbi, selectQuery2.c_str(), callbackbackup, (void*)data, &zErrMsg);
//     if (rc != SQLITE_OK) {
//       Serial.printf("SQL error Selecting BackUp : %s\n", sqlite3_errmsg(dbi));
//       sqlite3_free(zErrMsg);
//     } else {
//       Serial.print("Back Up Operation done successfully offset jdiida == ");
//       Serial.println(offset);
//       if (flag_callbackfunction == 0) {
//         offset = offset + limit;
//       }
//     }
//     sqlite3_close(dbi);
//     // xTaskNotify(transmitterModeINVENTAIREtask, freqValue, eSetValueWithOverwrite);

//     Serial.print("this is the line to send  ");
//     const char* lts = linestocheck.c_str();
//     Serial.println(lts);
//    // delay(77);

//     const char* cstr = linestocheck.c_str();
//     String hhh = String(cstr);
//     String transString1 = "M/" + hhh + "/";
//     const char* dataToTransmit2 = transString1.c_str();
//     //delay(2000);
//     transmitData(dataToTransmit2);
//     Serial.print("The data 2 to tansmit is :");
//     Serial.println(String(dataToTransmit2));
//     //delay(2500);
//     if (!linestocheck.empty()) {
//       // sqlite3_close(db);
//       linestocheck.clear();
//     }
//   //  delay(500);
//     Serial.println("khrajna mel fonction");
//   }
// //delay(2000);
//   transmitData("DONE/");
//   client.publish(DataQueue, "{\"Inventaire\":'done'}");
//   Serial.println("khrajna mel boucle while bkollou  ");
//  // delay(1000);
//   initializeAndListen(listeningFreq);
//   vTaskResume(Datatask);
//   Serial.println("Raja3na el data task te5dem INVENTAIIIIIIIIIIIIIIIIIIIIIIRE ");
// }

// void transmitFuncInventaire(void* pvParameters) {
//   for (;;) {
//     // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
//     uint32_t X = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
//     Serial.println(F("we received the notification to the inventaire and we are treating it "));
//     Serial.println("FL TRANSMISSION TASK TAA L INVENTAIRE ************* ");
//     Serial.println("----------------------- we are suspending the data task ");
//     vTaskSuspend(Datatask);
//     Serial.println("----------------------- DATA Suspended");
//     delay(2000);
//     std::string xStr = std::to_string(X);
//     send_test_back_up(X);
//     delay(500);
//   }
// }






// int createDatabaseData() {
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//   }
//   sqlite3* db3;
//   int rc1 = sqlite3_open("/sd/databaseTRY.db", &db3);

//   if (rc1 != SQLITE_OK) {
//     std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db3) << std::endl;
//     return rc1;
//   }
//   std::string createTableQuery = "CREATE TABLE IF NOT EXISTS BackupDB (row INTEGER PRIMARY KEY ,line_ID TEXT ,card_freq TEXT ,Sensor_ID TEXT, consumption TEXT, times TEXT, duration TEXT, sentFlag INTEGER, acked INTEGER);";
//   int rc2 = sqlite3_exec(db3, createTableQuery.c_str(), callback_P, (void*)data, &zErrMsg);
//   Serial.print("ESP.getFreeHeap()");

//   Serial.println(ESP.getFreeHeap());
//   if (rc2 != SQLITE_OK) {
//     std::cerr << "Error creating table: " << sqlite3_errmsg(db3) << std::endl;
//   }
//   sqlite3_close(db3);
//   return rc2;
// }

// int createDatabaseThreasholds() {
//   if (!sdState) {
//     Serial.println("card not mounted");
//     xTaskNotify(SdInitTask, 0, eNoAction);  // will either change sdState to true or it stays false
//   }
//   sqlite3* db3;
//   int rc1 = sqlite3_open("/sd/threasholdsDB.db", &db3);

//   if (rc1 != SQLITE_OK) {
//     std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db3) << std::endl;
//     return rc1;
//   }
//   std::string createTableQuery = "CREATE TABLE IF NOT EXISTS ThreashDB (row_num INTEGER PRIMARY KEY ,card_id TEXT ,card_freq TEXT ,sensor_id TEXT, consumption TEXT, duration TEXT);";
//   int rc2 = sqlite3_exec(db3, createTableQuery.c_str(), NULL, (void*)data, &zErrMsg);
//   Serial.print("ESP.getFreeHeap()");

//   Serial.println(ESP.getFreeHeap());
//   if (rc2 != SQLITE_OK) {
//     std::cerr << "Error creating table: " << sqlite3_errmsg(db3) << std::endl;
//   }
//   sqlite3_close(db3);
//   return rc2;
// }


// bool taskFileExecuted = false;  // Flag to track whether tasks have been executed
// bool taskTransExecuted = false;
// bool taskHWGwExecuted = false;


// void setup() {
//   delay(setup_off);
//   Serial.begin(115200);
//   Serial.println();
//   Serial.print(F(__TIME__));
//   Serial.print(F(" "));
//   Serial.println(F(__DATE__));
//   Serial.println(F(Program_Version));
//   Serial.println();
//   Serial.println(F(GW_name));
//   Serial.println();
  
//   Serial.println("CPU0 reset reason:");
//   Serial.println(resetReason(rtc_get_reset_reason(0)));
//   spi_cd.begin(SCK_sd, MISO_sd, MOSI_sd, CS_sd);

//   while (SDtrialCount < 5) {
//     if (SD.begin(CS_sd, spi_cd, 4000000)) {
//       // Mount Success, exit the loop
//       sdState = true;
//       break;
//     } else {
//       Serial.println("Card Mount Failed");
//       SDtrialCount++;
//       sdState = false;
//       delay(500);
//     }
//   }
//   xTaskCreate(SdInitFunc, "SdInitFunc", 5000, NULL, 5, &SdInitTask);
//   WiFi.mode(WIFI_STA);
//   //WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
//   connectToWiFi();
  


//   Serial.print("Adresse IP de l'ESP32 : ");
//   Serial.println(WiFi.localIP());
//   int timetry = 0; 

//   timeClient.begin();
//   timeClient.update();
//   currentTime = timeClient.getEpochTime();

//   while (currentTime < 1000000 && timetry < 3 ){
//    // WiFi.disconnect();
//     //reconnectWiFi();
//   timeClient.begin();
//   timeClient.update();
//   timetry ++;
  
//     currentTime = timeClient.getEpochTime();
//     offsetmillis = millis();
//     Serial.println("time from NTP attempt :");
//     Serial.println(currentTime);
//   }


//   Serial.println("time from NTP :");
//   Serial.println(currentTime);
//   String stringwifiRuntime = " WiFi connected to " + String(ssid);
//   const char* stringLog12 = stringwifiRuntime.c_str();
  
//   String concatStringBootReason0 = "Last Reboot Reason CPU0 " + resetReason(rtc_get_reset_reason(0));
//   const char* rebootReason0 = concatStringBootReason0.c_str();

//   String concatStringBootReason1 = "Last Reboot Reason CPU1 " + resetReason(rtc_get_reset_reason(1));
//   const char* rebootReason1 = concatStringBootReason1.c_str();
  

//   SPI.begin(SCK, MISO, MOSI, NSS);

//   Serial.print(F("[SX1278] Initializing ... "));

//   int state = radio.begin();

//   radio.setFrequency(listeningFreq);
//   radio.setBandwidth(125);
//   radio.setSpreadingFactor(12);
//   radio.setCodingRate(5);
//   radio.setGain(0);

//   if (state == RADIOLIB_ERR_NONE) {
//     Serial.println(F("Lora init success!"));
//   } else {
//     Serial.print(F("Lora init failed, code "));
//     Serial.println(state);
//   }

//   int rc1 = createDatabaseData();
//   int rc2 = createDatabaseThreasholds();


//   radio.setPacketReceivedAction(setFlag);

//   Serial.print(F("[SX1278] Starting to listen ... "));
//   state = radio.startReceive();


//   while (retryCount < 3) {
//     if (state == RADIOLIB_ERR_NONE) {
//       Serial.println(F("Lora listening success!"));
//       break;  // Exit the loop since the operation was successful
//     } else {
//       Serial.print(F("Lora listening failed, code "));
//       Serial.println(state);
//       retryCount++;  // Increment the retry counter
//     }
//   }

// portENTER_CRITICAL(&TimeMux);
//   currentTime = currentTime + (millis() - offsetmillis )/1000; 
//   offsetmillis = millis();
// portEXIT_CRITICAL(&TimeMux);

// time_t epochTime = currentTime;
// Serial.println(currentTime);
   
// struct tm *timeinfo;
// timeinfo = gmtime(&epochTime); // Convertir epoch en date UTC

// int year = timeinfo->tm_year + 1900;
// Serial.println(year);
// int month = timeinfo->tm_mon + 1; // Janvier = 0, donc +1
// Serial.println(month);
// int day = timeinfo->tm_mday;
// Serial.println(day);
// int hour = timeinfo->tm_hour;  
// int minute = timeinfo->tm_min;
// int second = timeinfo->tm_sec;


//   char dataDate[30];
//   snprintf(dataDate, sizeof(dataDate), "%02d-%02d-%02d %02d:%02d:%02d ", year, month, day, hour, minute, second);
//   String StringBootDate = "Last Reboot Date " + String(dataDate);
//   const char* StringBootDatec = StringBootDate.c_str();
  
//       // Network setup
//       client.setBufferSize(512);
//       client.setKeepAlive(60);
//       client.setSocketTimeout(10);
//       client.setServer(mqtt_server, 1883);
//       client.setCallback(callback);
//       client.setKeepAlive(MQTT_KEEP_ALIVE);

//   while (MQTTtrialCount < 3) {
//     if (client.connect(GW_name, mqtt_user, mqtt_pass)) {
//       // Mount Success, exit the loop
//       Serial.println("connected to mqtt");
//       break;
//     } else {
//       Serial.println("Connecting to MQTT Failed");
//       MQTTtrialCount++;
//       delay(1000);
//     }
//   }
//   if (client.subscribe(subscribeQueue, 1)) {
//     Serial.println("subscribed to the desired topic");
//   }
//   Serial.setDebugOutput(true);
 
   
//   Serial.println("time from NTP after millis :");
//   Serial.println(currentTime);
  
//   addElementToFile("Debug", stringLog12);
//   addElementToFile("Warning", rebootReason0);
//   addElementToFile("Warning", rebootReason1);
//   addElementToFile("Warning", StringBootDatec);
//   xTaskCreate(Data, "Data", 12000, NULL, tskIDLE_PRIORITY, &Datatask);                                         // 7000
//   xTaskCreate(transmitFunc, "transmitFunc", 8000, NULL, 1, &transmitTask);                                     // 5000
//   xTaskCreate(transmitFuncInventaire, "transmitFuncInventaireT", 6000, NULL, 1, &transmitFuncInventaireTask);  // Adjust stack size as needed; 5000
//   xTaskCreate(transmitterModeTime, "SdInitFunc", 5000, NULL, 1, &transmitFuncTimeTask);
//   xTaskCreate(WiFiXmqttFunc, "WiFiXmqttFunc", 3000, NULL, 1, &WiFiXmqttTask);
// }


// void loop() {
//   client.loop();
// }
