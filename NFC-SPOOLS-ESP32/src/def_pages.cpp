/**
 * @brief Web Server
 *
 * Web Server pages definition.....
 *
 * @author Ricky1966
 * @author simonegallina (supervisor)
 *
 * @version 1.0
 */

#include "def_pages.h"

/**
 * External variables
 */
extern AsyncWebServer server;
extern String ssid, pass, ip, gateway, n_sensors;
extern const char *PARAM_INPUT_1; //= "ssid";
extern const char *PARAM_INPUT_2; //= "pass";
extern const char *PARAM_INPUT_3; //= "ip";
extern const char *PARAM_INPUT_4; //= "gateway";
extern const char *PARAM_INPUT_5; //= "n_sensors";
extern String mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;
extern String function, functionCalled, uid_str, sensor_n;

/**
 * notFound
 * @brief send error page to client
 *
 * @param AsyncWebServerRequest *request  type of error and JSon answer
 */
void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

/**
 * def_pages_ap
 * @brief definition of Access Point page
 */
void def_pages_ap()
{
    Serial.println("Sono qua");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/setup.html", "text/html"); });

    server.serveStatic("/", LittleFS, "/").setDefaultFile("/setup.html");

    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
              {
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
      ESP.restart(); });
}

/**
 * def_pages_ws
 * @brief definition of Web Server pages
 */
void def_pages_ws()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    int paramsNr = request->params();
    Serial.println(paramsNr);

    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      if (p->name() == "function"){
        function = p->value();
      }
      if (p->name() == "sensor_n"){
        sensor_n = p->value();
        //Serial.print("SENSOR");
        //Serial.println(sensor_n);
      }
      if (function == "read"){
        tag_read(sensor_n.toInt());
      }
      if (function == "write"){
        tag_write(sensor_n.toInt());
      }
      if (function == "clear"){
        tag_clean(sensor_n.toInt());
      }
      if (function == "erase"){
        tag_erase(sensor_n.toInt());
      }
      if (function == "format"){
        tag_format(sensor_n.toInt());
      }
    }
    request->send(LittleFS, "/index.html", "text/html", false, processor); });
    server.serveStatic("/", LittleFS, "/").setDefaultFile("/index.html");
    // Route JSON request
    server.on("/jsonA", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      tag_read(0);
      String response = parser(0);
      request->send(200, "application/json", response); });
    server.on("/jsonB", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      tag_read(1);
      String response = parser(1);
      request->send(200, "application/json", response); });
    server.on("/jsonC", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      tag_read(2);
      String response = parser(2);
      request->send(200, "application/json", response); });
    server.onNotFound(notFound);

    server.on("/otaupdate", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/otaupdate.html", "text/html"); });

    server.on("/setup.html", HTTP_POST, [](AsyncWebServerRequest *request)
              {
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
    } });
}

/**
 * processor
 * @brief processing the variables to send to client for page
 * 			change PLACEHOLDER with html code
 * @param String  &var  refer to variable address
 * @return placeholder forindex.html %placeholder%
 */
String processor(const String &var)
{
    String placeholder = "";
    if (functionCalled == "READ 0")
    {
        placeholder += "<p class=\"state\">SLOT: A </p>";
    }
    else if (functionCalled == "READ 1")
    {
        placeholder += "<p class=\"state\">SLOT: B </p>";
    }
    else if (functionCalled == "READ 2")
    {
        placeholder += "<p class=\"state\">SLOT: C </p>";
    }
    placeholder += "<p class=\"state\">UID : ";
    placeholder += uid_str;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">Material: ";
    placeholder += mat_type;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">Color: ";
    placeholder += mat_color;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">Lenght: ";
    placeholder += spool_lenght;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">Weigth: ";
    placeholder += spool_weigth;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">T Bed: ";
    placeholder += temp_bed;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">T Extrude: ";
    placeholder += temp_ext;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">T First Layer Bed: ";
    placeholder += t_fl_b;
    placeholder += "</p>";
    placeholder += "<p class=\"state\">T First Layer Extrude: ";
    placeholder += t_fl_e;
    placeholder += "</p>";

    return placeholder;
}