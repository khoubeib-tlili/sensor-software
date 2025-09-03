// SX1278 pins: si ancien hard

#define NSS 5                      //select pin on LoRa device
#define SCK 18                     //SCK on SPI3
#define MISO 19                    //MISO on SPI3
#define MOSI 23                    //MOSI on SPI3
#define NRESET 27                  //reset pin on LoRa device
#define DIO0 35                    //DIO0 pin on LoRa device, used for RX and TX done

/*
//Si nouveau hard
#define NSS 15                                 
#define NRESET  27                          
#define DIO0 35                                                                      
#define SCK 14
#define MISO 12
#define MOSI 13
*/



#define LORA_DEVICE DEVICE_SX1278  //we need to define the device we are using
float listeningFreq = 440.00;

/*
//SD module pins: si nouveau hard
#define SCK_sd  18
#define MISO_sd  19
#define MOSI_sd  23
#define CS_sd  5
*/
// SD Module pins:si ancien hard

#define SCK_sd 21
#define MISO_sd 22
#define MOSI_sd 13
#define CS_sd 15

// Queues for Publiishing and Routing Keys for Subscription
const char* DataQueue = "water_sec.data.income";
const char* logFileQueue = "water_sec.data.logs";
const char* HealthCheckQueue = "water_sec.data.health_check";
const char* NotifsQueue = "water_sec.data.notifications";
const char* subscribeQueue = "water_sec.data.device.z3YaOpbxql";
IPAddress local_IP(192, 168, 1, 253);   // Adresse IP de l'ESP32
IPAddress gateway(192, 168, 1, 1);      // Passerelle (généralement l'adresse du routeur)
IPAddress subnet(255, 255, 255, 0);     // Masque de sous-réseau
IPAddress primaryDNS(8, 8, 8, 8);       // Serveur DNS primaire (Google DNS)
IPAddress secondaryDNS(8, 8, 4, 4);     // Serveur DNS secondaire (Google DNS)

int setup_off = 0;

char GW_name[9] = "HPHPBG1";
char GW_id[11] = "z3YaOpbxql";






const char* ssid = "TOPNET_XGSL";  
const char* password = "55v6vhvusq";


const char* mqtt_server = "rq-poc.water-sec.com";  // RabitMQ
const char* mqtt_user = "test";                   // RabitMQ
const char* mqtt_pass = "Test123!";            // RabitMQ



