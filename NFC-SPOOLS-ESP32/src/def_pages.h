/**
 * @brief Spool class
 * 
 * Web Server pages definition.....
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#ifndef _DEF_PAGES_H
#define _DEF_PAGES_H

/**
 * 
 */
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <Update.h>
#include "init_fs.h"
#include "tag_read.h"
#include "tag_write.h"
#include "tag_clean.h"
#include "tag_erase.h"
#include "tag_format.h"
#include "parser_json.h"

/**
 * 
 */
void def_pages_ap();

/**
 * 
 */
void def_pages_ws();

/**
 * 
 */
void notFound(AsyncWebServerRequest *);

/**
 * 
 */
String processor(const String &);

#endif