/**
 * @brief Spool class
 * 
 * FileSystem init long description.....
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#ifndef _INIT_FS_H
#define _INIT_FS_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>
#include <Preferences.h>

void initLittleFS();
void readPref();
void writePref(const char *, const char *);
#endif