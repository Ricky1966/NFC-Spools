/**
 * @brief Spool class
 * 
 * Tag Read function long description.....
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#ifndef _TAG_READ_H
#define _TAG_READ_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>
#include "spool.h"

#define SS_PIN_1 4    // ESP32 pin GPIO4
#define SS_PIN_2 5    // ESP32 pin GPIO5
#define SS_PIN_3 15   // ESP32 pin GPIO2
#define MAX_SENSORS 3 // max number of sensors

//void loader(int, String);
void loader(int, String, Spool*);
bool tag_read(int);
bool tag_read_init(int, Spool*);
#endif