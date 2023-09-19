#include "tag_format.h"

#define SS_PIN_1 4    // ESP32 pin GPIO4
#define SS_PIN_2 5    // ESP32 pin GPIO5 
#define SS_PIN_3 6    // ESP32 pin GPIO4
#define SS_PIN_4 7    // ESP32 pin GPIO5
#define MAX_SENSORS 4 //max number of sensors 
#define RST_PIN 27    // ESP32 pin GPIO27

extern MFRC522 mfrc522_1;//(SS_PIN_1, RST_PIN);
extern MFRC522 mfrc522_2;//(SS_PIN_2, RST_PIN);

extern NfcAdapter nfc_1;// = NfcAdapter(&mfrc522_1);
extern NfcAdapter nfc_2;//= NfcAdapter(&mfrc522_2);

extern char uid[30], tag_msg[100];
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;

bool tag_format(){
    return true;
}