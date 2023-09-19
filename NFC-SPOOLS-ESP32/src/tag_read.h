#ifndef _TAG_READ_H
#define _TAG_READ_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>

bool tag_read(int);
void loader(int,String);

#endif
