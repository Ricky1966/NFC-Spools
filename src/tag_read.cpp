/**
 * @brief Tag Read
 *
 * Tag Read function allows you to read tag data
 *
 * @author Ricky1966
 * @author simonegallina (supervisor)
 *
 * @version 2.0
 */

#include "tag_read.h"

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
 * loader
 * 
 * @brief Set data to a tag
 *
 * @param int     i           Data type
 * @param String  tag_msg_str Contains message read from tag
 * @param Spool*  spool       Active spool
 */
void loader(int i, String tag_msg_str, Spool *spool)
{
    switch (i)
    {
    case 0:
        spool->setMatType(tag_msg_str);
        break;

    case 1:
        spool->setMatColor(tag_msg_str);
        break;

    case 2:
        spool->setLength(tag_msg_str);
        break;

    case 3:
        spool->setWeight(tag_msg_str);
        break;

    case 4:
        spool->setTempBed(tag_msg_str);
        break;

    case 5:
        spool->setTempExtruder(tag_msg_str);
        break;

    case 6:
        spool->setBedFirstLayer(tag_msg_str);
        break;

    case 7:
        spool->setExtFirstLayer(tag_msg_str);
        break;

    default:
        break;
    }
}


/**
 * tag_read
 * 
 * @brief Extracts data from tag
 *
 * @param   Spool*      spool       Spool object
 * @param   NfcAdapter* active_nfc  Active NFC Adapter
 * @param   uint8_t*    pin_list    Array of th SS pins
 * @param   uint8_t     sens_num    Total number of sensors
 *
 * @return  bool        True on success, false otherwise
 */
bool tag_read(Spool* spool, NfcAdapter* active_nfc, uint8_t* pin_list, uint8_t sens_num)
{
    /**
     * Disable all the RFID readers setting to HIGH each Slave Select pin
     */
    for (uint8_t i = 0; i < sens_num; i++)
    {
        digitalWrite(pin_list[i], HIGH);
    }

    /* Activate only the requested RFID reader */
    digitalWrite(pin_list[spool->getNumber()], LOW);



    if (active_nfc->tagPresent())
    {
        NfcTag tag = active_nfc->read();
        uid_str = tag.getUidString();
        uid_str.toCharArray(uid, uid_str.length() + 1);

        if (tag.hasNdefMessage())
        {
            NdefMessage message = tag.getNdefMessage();
            int recordCount = message.getRecordCount();
            for (int i = 0; i < recordCount; i++)
            {
                NdefRecord record = message.getRecord(i);
                int payloadLength = record.getPayloadLength();
                const byte *payload = record.getPayload();
                String tag_msg_str = "";
                for (int c = 3; c < payloadLength; c++)
                {
                    tag_msg_str += (char)payload[c];
                }
                tag_msg_str.toCharArray(tag_msg, tag_msg_str.length() + 1);
                loader(i, tag_msg_str, spool);
            }
        }
        //Serial.print("Oggetto");
        //Serial.println("");
        //Serial.println(spool->getLength());
        //Serial.println(spool->getWeight());
        return true;
    }

    return false;
}


/**
 * tag_read_init
 *
 * @brief Initializes spools for reading
 *
 * @param   Spool*      spool       Spool object
 * @param   NfcAdapter* active_nfc  Active NFC Adapter
 * @param   uint8_t*    pin_list    Array of th SS pins
 * @param   uint8_t     sens_num    Total number of sensors
 *
 * @return  bool        True on success, false otherwise
 */
bool tag_read_init(Spool* spool, NfcAdapter* active_nfc, uint8_t* pin_list, uint8_t sens_num)
{
    /**
     * Disable all the RFID readers setting to HIGH each Slave Select pin
     */
    for (uint8_t i = 0; i < sens_num; i++)
    {
        digitalWrite(pin_list[i], HIGH);
    }

    /* Activate only the requested RFID reader */
    digitalWrite(pin_list[spool->getNumber()], LOW);

    Serial.print("Sensore ");
    Serial.println(spool->getNumber());

    if (active_nfc->tagPresent())
    {
        NfcTag tag = active_nfc->read();
        uid_str = tag.getUidString();
        Serial.println(uid_str);
        spool->setUid(uid_str);
        //uid_str.toCharArray(uid, uid_str.length() + 1);

        if (tag.hasNdefMessage())
        {
            NdefMessage message = tag.getNdefMessage();
            int recordCount = message.getRecordCount();
            for (int i = 0; i < recordCount; i++)
            {
                NdefRecord record = message.getRecord(i);
                int payloadLength = record.getPayloadLength();
                const byte *payload = record.getPayload();
                String tag_msg_str = "";
        
                for (int c = 3; c < payloadLength; c++)
                {
                    tag_msg_str += (char)payload[c];
                }
        
                tag_msg_str.toCharArray(tag_msg, tag_msg_str.length() + 1);
                loader(i, tag_msg_str, spool);
            }
        }

        Serial.println("Oggetto creato");
        Serial.println(spool->getUid());
        Serial.println(spool->getMatType());
        Serial.println(spool->getMatColor());
        return true;
    }

    return false;
}
