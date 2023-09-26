#ifndef _DEF_PAGES_H
#define _DEF_PAGES_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <Update.h>

void def_pages_ap();
void def_pages_ws();
void notFound(AsyncWebServerRequest *);
String processor(const String&);
#endif