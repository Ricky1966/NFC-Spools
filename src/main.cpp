/**
 * @brief Main class
 *
 * Main long description.....
 *
 * @author Ricky1966
 * @author simonegallina (supervisor)
 *
 * @version 2.0
 */

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

#include "Spool.h"

#include "tag_read.h"
/* ************************************* temporary disabled ************************/
/*#include "tag_clean.h"
#include "tag_erase.h"
#include "tag_format.h"
#include "tag_write.h"
#include "parser_json.h"
#include "init_fs.h"
#include "def_pages.h"*/


#define RST_PIN 27  // ESP32 pin GPIO27
#define SENSORS_NUMBER 3

const char *PARAM_INPUT_1 = "ssid";
const char *PARAM_INPUT_2 = "pass";
const char *PARAM_INPUT_3 = "ip";
const char *PARAM_INPUT_4 = "gateway";
const char *PARAM_INPUT_5 = "n_sensors";

uint8_t SS_PINs[SENSORS_NUMBER] = { 4,  // ESP32 pin GPIO4
                                    5,  // ESP32 pin GPIO5
                                    15 // ESP32 pin GPI15
                                    };

String ssid;
String pass;
String ip;
String gateway;
String n_sensors;

unsigned long previousMillis = 0;
const long interval = 10000;

String functionCalled;

char uid[30];
String uid_str;
char tag_msg[100];
String tag_msg_str;
char wrt_msg[30];
String wrt_msg_str;
String mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;
String function, sensor_n;

/**
 *
 */
AsyncWebServer server(80);
Preferences preferences;
IPAddress localIP;
IPAddress localGateway;
IPAddress subnet(255, 255, 0, 0);

MFRC522* MFRCs[SENSORS_NUMBER];
NfcAdapter* NFCs[SENSORS_NUMBER];
Spool *spools[SENSORS_NUMBER];


/**
 * initWifi
 *
 * @brief Initializes WiFi connection
 * 
 * @return  bool    True on success, false otherwise
 */
bool initWiFi()
{
    preferences.begin("nfc-bobine", false);
    ssid = preferences.getString("ssid", "");
    pass = preferences.getString("pass", "");

    ip = preferences.getString("ip", "");
    gateway = preferences.getString("gateway", "");

    if (ssid == "" || ip == "")
    {
        Serial.println("Undefined SSID or IP address.");
        return false;
    }

    WiFi.mode(WIFI_STA);
    localIP.fromString(ip.c_str());
    localGateway.fromString(gateway.c_str());

    if (!WiFi.config(localIP, localGateway, subnet))
    {
        Serial.println("STA Failed to configure");
        return false;
    }
    WiFi.begin(ssid.c_str(), pass.c_str());
    Serial.println("Connecting to WiFi...");

    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    while (WiFi.status() != WL_CONNECTED)
    {
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            Serial.println("Failed to connect.");
            return false;
        }
    }

    Serial.println(WiFi.localIP());
    return true;
}


/**
 * setup
 *
 * @brief General setup
 */
void setup()
{
    Serial.begin(115200);

    /* ************************************* temporary disabled ************************/
    //initLittleFS();

    if (initWiFi())
    {
        // setup Web Server
        Serial.println("WiFi init!");
        /* ************************************* temporary disabled ************************/
        //def_pages_ws();
        delay(3000);
    }
    else
    {
        // setup Access Point
        Serial.println("Setting AP (Access Point)");
        WiFi.softAP("ESP-WIFI-MANAGER", NULL);

        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        /* ************************************* temporary disabled ************************/
        //def_pages_ap();
    }

    server.begin();
    SPI.begin();

    delay(1000);

    
    /**
     * Sensors setup
     */
    for (uint8_t i = 0; i < SENSORS_NUMBER; i++)
    {
        MFRCs[i] = new MFRC522(SS_PINs[i], RST_PIN);
        NFCs[i] = new NfcAdapter(MFRCs[i]);
        MFRCs[i]->PCD_Init();
        spools[i] = new Spool(i);
        tag_read_init(spools[i], NFCs[i], SS_PINs, SENSORS_NUMBER);
        spools[i]->printToSerial(&Serial);
    }
}


/**
 * loop
 *
 * @brief Runtime Loop
 */
void loop()
{
}
