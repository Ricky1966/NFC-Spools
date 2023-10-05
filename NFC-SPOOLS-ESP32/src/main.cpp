#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>
#include <MFRC522.h>
#include <NfcAdapter.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <Update.h>

#include "tag_clear.h"
#include "tag_erase.h"
#include "tag_format.h"
//#include "tag_read.h"
#include "new_tag_read.h"
#include "tag_write.h"
#include "parser_json.h"
#include "init_fs.h"
#include "def_pages.h"

#define SS_PIN_1 4 // ESP32 pin GPIO4
#define SS_PIN_2 5  // ESP32 pin GPIO5 
#define SS_PIN_3 6 // ESP32 pin GPIO4
#define SS_PIN_4 7  // ESP32 pin GPIO5
#define MAX_SENSORS 4 //max number of sensors 
#define RST_PIN 27 // ESP32 pin GPIO27 
// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";
const char* PARAM_INPUT_5 = "n_sensors";
String ssid;
String pass;
String ip;
String gateway;
String n_sensors;
unsigned long previousMillis = 0;
const long interval = 10000;  
String functionCalled;
char uid[30];
String uid_str ;
char tag_msg[100];
String tag_msg_str ;
char wrt_msg[30];
String wrt_msg_str ;
String mat_type,mat_color,spool_lenght,spool_weigth,temp_bed,temp_ext,t_fl_b,t_fl_e;
String function, sensor_n;

AsyncWebServer server(80);
Preferences preferences;
IPAddress localIP;
IPAddress localGateway;
IPAddress subnet(255, 255, 0, 0);
MFRC522 mfrc522_1(SS_PIN_1, RST_PIN);
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN);
MFRC522 mfrc522_3(SS_PIN_3, RST_PIN);
MFRC522 mfrc522_4(SS_PIN_4, RST_PIN);
NfcAdapter nfc_1 = NfcAdapter(&mfrc522_1);
NfcAdapter nfc_2 = NfcAdapter(&mfrc522_2);
NfcAdapter nfc_3 = NfcAdapter(&mfrc522_3);
NfcAdapter nfc_4 = NfcAdapter(&mfrc522_4);

bool initWiFi() {
  // looking for stored preference
  preferences.begin("nfc-bobine", false);
  ssid = preferences.getString("ssid","");
  pass = preferences.getString("pass","");
  ip = preferences.getString("ip","");
  gateway =  preferences.getString("gateway","");

  if(ssid=="" || ip==""){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());


  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

void setup() {
  Serial.begin(115200);
  
  initLittleFS();

  if(initWiFi()) {
    // setup Web Server
    Serial.println("WiFi init!");
    def_pages_ws();
    delay(3000);
  }
  else {
    // setup Access Point
    Serial.println("Setting AP (Access Point)");
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    def_pages_ap();
  }
  server.begin();
  SPI.begin();    
  mfrc522_1.PCD_Init(); 
  mfrc522_2.PCD_Init();
  delay(1000);
  nfc_1.begin();
  nfc_2.begin();
}

void loop() {
}

