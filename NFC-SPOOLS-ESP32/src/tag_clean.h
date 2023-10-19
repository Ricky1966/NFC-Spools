/**
 * @brief Tag Clear 
 * 
 * Tag Clear function clean tag to zero
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#ifndef _TAG_CLEAR_H
#define _TAG_CLEAR_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>

#define SS_PIN_1 4    // ESP32 pin GPIO4
#define SS_PIN_2 5    // ESP32 pin GPIO5
#define SS_PIN_3 15   // ESP32 pin GPIO2
#define MAX_SENSORS 3 // max number of sensors

bool tag_clean(int);

#endif