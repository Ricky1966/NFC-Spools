#ifndef _TAG_READ_H
#define _TAG_READ_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>

void loader(int,String);
bool tag_read(int);

#endif