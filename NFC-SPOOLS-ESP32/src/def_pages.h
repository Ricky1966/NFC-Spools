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

#include "def_pages.h"
#include "init_fs.h"
//#include "tag_read.h"
#include "new_tag_read.h"
#include "parser_json.h"

void def_pages_ap();
void def_pages_ws();
void notFound(AsyncWebServerRequest *);
String processor(const String&);
void handleUpdate(AsyncWebServerRequest *request);
void handleDoUpdate(AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final);
void printProgress(size_t , size_t );
#endif