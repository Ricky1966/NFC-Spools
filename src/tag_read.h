/**
 * @brief   Tag Read function allows you to read tag data
 *
 * @author Ricky1966
 * @author simonegallina
 * 
 * @version 2.0
 */

#ifndef _TAG_READ_H
#define _TAG_READ_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>
#include "Spool.h"

// void loader(int, String);
void loader(int, String, Spool *);
bool tag_read(Spool*, NfcAdapter*, uint8_t*, uint8_t);
bool tag_read_init(Spool*, NfcAdapter*, uint8_t*, uint8_t);

#endif