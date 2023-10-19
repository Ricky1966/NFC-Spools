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

#include "tag_format.h"
#include "spool.h"

/**
 * External variables
 */
extern MFRC522 mfrc522_1;
extern MFRC522 mfrc522_2;
extern MFRC522 mfrc522_3;
extern NfcAdapter nfc_1;
extern NfcAdapter nfc_2;
extern NfcAdapter nfc_3;
extern Spool spool[];

/**
 * tag_format
 * @brief   tag formatter function
 */
bool tag_format(int sensor)
{

    NfcAdapter *active_nfc;

    if ((sensor >= 0) && (sensor <= MAX_SENSORS))
    {
        switch (sensor)
        {
        case 0:
            digitalWrite(SS_PIN_1, LOW);
            digitalWrite(SS_PIN_2, HIGH);
            digitalWrite(SS_PIN_3, HIGH);
            active_nfc = &nfc_1;
            break;
        case 1:
            digitalWrite(SS_PIN_1, HIGH);
            digitalWrite(SS_PIN_2, LOW);
            digitalWrite(SS_PIN_3, HIGH);
            active_nfc = &nfc_2;
            break;
        case 2:
            digitalWrite(SS_PIN_1, HIGH);
            digitalWrite(SS_PIN_2, HIGH);
            digitalWrite(SS_PIN_3, LOW);
            active_nfc = &nfc_3;
            Serial.println("Write Sensore 3");
            break;
        default:
            break;
        }

        Serial.println("\nPlace a formatted Mifare Classic NFC tag on the reader.");

        if (active_nfc->tagPresent())
        {
            boolean success = active_nfc->format();
            if (success)
            {
                Serial.println("Format Success.");
                delay(3000);
                return true;
            }
            else
            {
                Serial.println("Format failed");
                delay(3000);
                return false;
            }
        }
    }
    return false;
}