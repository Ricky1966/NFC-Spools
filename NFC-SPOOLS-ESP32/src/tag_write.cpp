/**
 * @brief Tag Write
 * 
 * Tag Write function long description.....
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#include "tag_write.h"
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
extern char uid[30], tag_msg[100];
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;
extern Spool spool[];


/**
 * tag_write
 * @brief write new values into a tag
 * 
 * @param sensor    sensor  number of sensor 
 */
bool tag_write(int sensor)
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
            NdefMessage message = NdefMessage();
            message.addTextRecord("ABS");
            message.addTextRecord("#FFFFFF");
            message.addTextRecord("300000");
            message.addTextRecord("900");
            message.addTextRecord("90");
            message.addTextRecord("245");
            message.addTextRecord("80");
            message.addTextRecord("235");
            boolean success = active_nfc->write(message);
            if (success)
            {
                Serial.println("Success. Try reading this tag with your phone.");
                delay(3000);
                return true;
            }
            else
            {
                Serial.println("Write failed");
                delay(3000);
                return false;
            }
        }
    }
    return false;
}