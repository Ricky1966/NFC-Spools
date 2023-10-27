/**
 * @brief Spool class
 * 
 * @author Ricky1966
 * @author simonegallina
 * 
 * @version 2.0
 */

#ifndef _SPOOL_H
#define _SPOOL_H

#include <Arduino.h>
#include <MFRC522.h>
#include <NfcAdapter.h>

/**
 * Spool
 * 
 * @brief Spool tag manager
 */
class Spool
{
    private:
        String uid_str;
        String mat_type;
        String mat_color;
        String spool_length;
        String spool_weight;
        String temp_bed;
        String temp_ext;
        String t_fl_b;
        String t_fl_e;
        uint8_t number;

    public:
        Spool();
        Spool(String uid_str);
        Spool(uint8_t);
        Spool(uint8_t, NfcAdapter*, uint8_t*, uint8_t);
        void loader(int, String, Spool *);
        //void init();
        void init(NfcAdapter*, uint8_t*, uint8_t);
        void setNumber(uint8_t);
        uint8_t getNumber();
        void setUid(String);
        String getUid();
        void setMatType(String);
        String getMatType();
        void setMatColor(String);
        String getMatColor();
        void setLength(String);
        String getLength();
        void setWeight(String);
        String getWeight();
        void setTempBed(String);
        String getTempBed();
        void setTempExtruder(String);
        String getTempExtruder();
        void setBedFirstLayer(String);
        String getBedFirstLayer();
        void setExtFirstLayer(String);
        String getExtFirstLayer();
        void printToSerial(Stream*);
};

#endif