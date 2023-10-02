/*
// Questa è la procedura per creare le pagine del server
// La funzione def_pages_ap() definisce la funzione chiamata quando non vengono
// trovate le chiavi di accesso alla rete wifi e permette di inserirle nella pagina e salvarle tra le 
// preferenze.
// La funzione def_pages_ws() si occupa di create le pagine del server per la gesione
// delle varie fasi di lettura e scrittura dei tag
// Infine la funzione processor() modifica le variabili della pagina index.html
// TODO :
// La pagina per la scrittura dei valori sul tag. 
*/

#include "def_pages.h"
#include "init_fs.h"
#include "tag_read.h"
#include "parser_json.h"

//AsyncWebServer server(80);
extern AsyncWebServer server;
extern String ssid, pass, ip, gateway, n_sensors;
extern const char* PARAM_INPUT_1 ;//= "ssid";
extern const char* PARAM_INPUT_2 ;//= "pass";
extern const char* PARAM_INPUT_3 ;//= "ip";
extern const char* PARAM_INPUT_4 ;//= "gateway";
extern const char* PARAM_INPUT_5 ;//= "n_sensors";
extern String mat_type,mat_color,spool_lenght,spool_weigth,temp_bed,temp_ext,t_fl_b,t_fl_e;
extern String function, functionCalled, uid_str, sensor_n;


void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void def_pages_ap()
{
  Serial.println("Sono qua");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/setup.html", "text/html");
  });
    
  server.serveStatic("/", LittleFS, "/").setDefaultFile("/setup.html");
    
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
        // HTTP POST gateway value
        if (p->name() == PARAM_INPUT_5) {
          n_sensors = p->value().c_str();
          Serial.print("Number of sensor(s) set to: ");
          Serial.println(n_sensors);
          writePref("n_sensors",n_sensors.c_str());
        }
      }
    }
    request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
      delay(3000);
      ESP.restart();
  });
}

void def_pages_ws()
{
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
    server.on("/json1", HTTP_GET, [](AsyncWebServerRequest *request){
      tag_read(1);
      String response = parser(1);
      request->send(200, "application/json", response);
    });
    server.on("/json2", HTTP_GET, [](AsyncWebServerRequest *request){
      tag_read(2);
      String response = parser(2);
      request->send(200, "application/json", response);
    });
    /*
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/my_ota.html", "text/html");
    });
    */
    server.onNotFound(notFound);
    server.on("/otaupdate", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS,"/otaupdate.html", "text/html");
  });

    server.on("/setup.html", HTTP_POST, [](AsyncWebServerRequest *request) {
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
        // HTTP POST gateway value
        if (p->name() == PARAM_INPUT_5) {
          n_sensors = p->value().c_str();
          Serial.print("Number of sensor(s) set to: ");
          Serial.println(n_sensors);
          writePref("n_sensors",n_sensors.c_str());
        }
      }
    }
  });
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