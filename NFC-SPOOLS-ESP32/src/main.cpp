#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <LittleFS.h>
#include <Preferences.h>
#include <MFRC522.h>
#include <NfcAdapter.h>
#include <Preferences.h>
#include <ArduinoJson.h>

#define SS_PIN_1 4 // ESP32 pin GPIO4
#define SS_PIN_2 5  // ESP32 pin GPIO5 
#define SS_PIN_3 6 // ESP32 pin GPIO4
#define SS_PIN_4 7  // ESP32 pin GPIO5
#define MAX_SENSORS 4 //max number of sensors 
#define RST_PIN 27 // ESP32 pin GPIO27 
const byte readersNum = 2;
byte SS_Pins[readersNum] = {SS_PIN_1, SS_PIN_2};//, SS_PIN_3, SS_PIN_4};
// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";
String ssid;
String pass;
String ip;
String gateway;
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
//MFRC522 mfrc522_3(SS_PIN_3, RST_PIN);
//MFRC522 mfrc522_4(SS_PIN_4, RST_PIN);
NfcAdapter nfc_1 = NfcAdapter(&mfrc522_1);
NfcAdapter nfc_2 = NfcAdapter(&mfrc522_2);
String parser(int);
bool tag_read(int);
bool tag_write();
void tag_erase();
void tag_clear();
void tag_format();

void initLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

// Read File from LittleFS
void readPref(){
  ssid = preferences.getString("ssid", "");
  pass = preferences.getString("pass", "");
  ip = preferences.getString("ip","");
  gateway = preferences.getString("gateway","");
}

void writePref(const char * pref, const char * message){
  preferences.putString(pref,message);
  Serial.print("Preference :");
  Serial.print(pref);
  Serial.println(" setted!");
}

bool initWiFi() {
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

String processor(const String& var) {
  if(var == "UID"){
    Serial.print("UID : ");
    Serial.println(uid_str);
    return uid_str;
  }
  if(var == "SEN"){
    if (functionCalled == "READ 1"){
      Serial.println("1");
      return "1";
    } 
     if (functionCalled == "READ 2"){
      Serial.println("2");
      return "2";
    } 
  }
  if(var == "MAT"){
    Serial.println(mat_type);
    return mat_type;
  }
  if(var == "COL"){
    Serial.println(mat_color);
    return mat_color;
  }
  if(var == "LEN"){
    Serial.println(spool_lenght);
    return spool_lenght;
  }
  if(var == "WEI"){
    Serial.println(spool_weigth);
    return spool_weigth;
  }
  if(var == "TBED"){
    Serial.println(temp_bed);
    return temp_bed;
  }
  if(var == "TEXT"){
    Serial.println(temp_ext);
    return temp_ext;
  }
  if(var == "TFLB"){
    Serial.println(t_fl_b);
    return t_fl_b;
  }
  if(var == "TFLE"){
    Serial.println(t_fl_e);
    return t_fl_e;
  }
  return String();
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void setup() {
  Serial.begin(115200);
  preferences.begin("nfc-bobine", false);
  initLittleFS();
  ssid = preferences.getString("ssid","");
  pass = preferences.getString("pass","");
  ip = preferences.getString("ip","");
  gateway =  preferences.getString("gateway","");
  Serial.println(ip);

  if(initWiFi()) {

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      int paramsNr = request->params();
    Serial.println(paramsNr);

    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      if (p->name() == "function"){
        function = p->value();
        Serial.print("Param name: ");
        Serial.println(function);
      }
      if (p->name() == "sensor_n"){
        sensor_n = p->value();
        Serial.print("Param name: ");
        Serial.println(sensor_n);
      }
      if (function == "read"){
        tag_read(sensor_n.toInt());
      }
      if (function == "write"){
        //tag_read(sensor_n.toInt());
      }
      if (function == "clear"){
        //tag_read(sensor_n.toInt());
      }
      if (function == "erase"){
        //tag_read(sensor_n.toInt());
      }
      if (function == "format"){
        //tag_read(sensor_n.toInt());
      }
    }
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });
    server.serveStatic("/", LittleFS, "/").setDefaultFile("/index.html");
    // Route JSON request
    server.on("/json2", HTTP_GET, [](AsyncWebServerRequest *request){
      //tag_read(2);
      String response = parser(2);
      request->send(200, "application/json", response);
    });
    server.onNotFound(notFound);
  }
  else {
    Serial.println("Setting AP (Access Point)");
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", LittleFS, "/").setDefaultFile("/wifmanager.html");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            writePref("ssid",ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            writePref("pass",pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            writePref("ip", ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            writePref("gateway",gateway.c_str());
          }
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
      delay(3000);
      ESP.restart();
    });
  }
  AsyncElegantOTA.begin(&server);
  server.begin();
  SPI.begin();    
  mfrc522_1.PCD_Init(); 
  mfrc522_2.PCD_Init();
  //mfrc522_1.PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);
  //mfrc522_2.PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);
  nfc_1.begin();
  nfc_2.begin();
}

void loop() {
}

String parser(int sensor){
  StaticJsonDocument<300> data;
      data["Sensor"] = 2;
      data["UID"] = uid_str;
      data["Material"] = mat_type ;
      data["Color"] = mat_color ;
      data["Lenght"] = spool_lenght ;
      data["Weigth"] = spool_weigth ;
      data["T_Bed"] = temp_bed ;
      data["T_Ext"] = temp_ext ;
      data["T_fl_Bed"] = t_fl_b ;
      data["T_fl_Ext"] = t_fl_e ;
      String response;
      serializeJson(data, response);
      return response;
}

bool tag_read(int sensor){
 
  if (sensor == 1){
    Serial.print("TAG.......");
    Serial.println(sensor);
    if (nfc_1.tagPresent()){
      NfcTag tag = nfc_1.read();
      Serial.print("UID: ");
      uid_str = tag.getUidString(); 
      uid_str.toCharArray(uid, uid_str.length() + 1);
      Serial.println(uid_str);
      if (tag.hasNdefMessage()){ 
        NdefMessage message = tag.getNdefMessage();
        int recordCount = message.getRecordCount();
        for (int i = 0; i < recordCount; i++){
          NdefRecord record = message.getRecord(i);
          int payloadLength = record.getPayloadLength();
          const byte *payload = record.getPayload();
          String tag_msg_str = "";
          for (int c = 3; c < payloadLength; c++) {
            tag_msg_str += (char)payload[c];
          }
          tag_msg_str.toCharArray(tag_msg, tag_msg_str.length() + 1);
          Serial.println(tag_msg_str);
          switch (i) {
            case 0:
              mat_type = tag_msg_str;
              break;
            case 1:
              mat_color = tag_msg_str;
              break;
            case 2:
              spool_lenght = tag_msg_str;
              break;
            case 3:
              spool_weigth = tag_msg_str;
              break;
            case 4:
              temp_bed = tag_msg_str; 
              break;
            case 5:
              temp_ext = tag_msg_str;
              break;
            case 6:
              t_fl_b = tag_msg_str;
              break;
            case 7:
              t_fl_e = tag_msg_str;
              break;
            default :
              break;
          }
        }
      }
    //nfc.haltTag();
    return true;
    }
  } 
  if (sensor == 2){
    Serial.print("TAG.......");
    Serial.println(sensor);
    if (nfc_2.tagPresent()){
      NfcTag tag = nfc_2.read();
      Serial.print("UID: ");
      uid_str = tag.getUidString(); 
      uid_str.toCharArray(uid, uid_str.length() + 1);
      Serial.println(uid_str);
      if (tag.hasNdefMessage()){ 
        NdefMessage message = tag.getNdefMessage();
        int recordCount = message.getRecordCount();
        for (int i = 0; i < recordCount; i++){
          NdefRecord record = message.getRecord(i);
          int payloadLength = record.getPayloadLength();
          const byte *payload = record.getPayload();
          String tag_msg_str = "";
          for (int c = 3; c < payloadLength; c++) {
            tag_msg_str += (char)payload[c];
          }
          tag_msg_str.toCharArray(tag_msg, tag_msg_str.length() + 1);
          Serial.println(tag_msg_str);
          switch (i) {
            case 0:
              mat_type = tag_msg_str;
              break;
            case 1:
              mat_color = tag_msg_str;
              break;
            case 2:
              spool_lenght = tag_msg_str;
              break;
            case 3:
              spool_weigth = tag_msg_str;
              break;
            case 4:
              temp_bed = tag_msg_str; 
              break;
            case 5:
              temp_ext = tag_msg_str;
              break;
            case 6:
              t_fl_b = tag_msg_str;
              break;
            case 7:
              t_fl_e = tag_msg_str;
              break;
            default :
              break;
          }
        }
      }
    return true;
    }
  } 
  return false;
}

bool tag_write(){
  return true;
}

void tag_format(){
}

void tag_clear(){
}

void tag_erase(){
}
