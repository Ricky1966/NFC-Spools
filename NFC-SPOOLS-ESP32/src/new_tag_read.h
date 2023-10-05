#ifndef _TAG_READ_H
#define _TAG_READ_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>

#define MAX_SENSORS 4 //max number of sensors 

void loader(int,String);
bool tag_read(int);

#endif