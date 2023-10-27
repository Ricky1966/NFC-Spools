/**
 * @brief Spool class
 * 
 * @author Ricky1966
 * @author simonegallina
 * 
 * @version 2.0
 */

#include "Spool.h"


/**
 * Spool
 * 
 * @brief   Constructor
 *
 */
Spool::Spool()
{
    init();
}


/**
 * Spool
 * 
 * @brief   Constructor
 * 
 * @param   String  uid     Spool tag UID string
 */
Spool::Spool(String uid)
{
    init();
    uid_str = uid;
}


/**
 * Spool
 * 
 * @brief   Constructor
 * 
 * @param   uint8_t     m       Spool number
 */
Spool::Spool(uint8_t m)
{
    init();
    number = m;
}

/**
 * Spool
 * 
 * @brief   Constructor
 * 
 * @param   uint8_t     m       Spool number
 */
Spool::Spool(uint8_t m, NfcAdapter* active_nfc, uint8_t* pin_list, uint8_t sens_num)
{
    active_nfc = active_nfc;
    pin_list = pin_list;
    sens_num = sens_num;
    init(active_nfc,pin_list,sens_num);
    number = m;
}


/**
 * setNumber
 * 
 * @brief   Set the spool number
 * 
 * @param   uint8_t     m       Spool number
 */
void Spool::setNumber(uint8_t m)
{
    number = m;
}


/**
 * getnumber
 * 
 * @brief   Returns the spool number
 * 
 * @return  uint8_t     Spool number
 */
uint8_t Spool::getNumber()
{
    return number;
}


/**
 * init
 * 
 * @brief   Initializes the object properties
 
void Spool::init()
{
    uid_str = "";
    mat_type = "";
    mat_color = "";
    spool_length = "";
    spool_weight = "";
    temp_bed = "";
    temp_ext = "";
    t_fl_b = "";
    t_fl_e = "";
}
*/


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
 * init
 *
 * @brief Initializes spools from tag reading
 *
 * @param   Spool*      spool       Spool object
 * @param   NfcAdapter* active_nfc  Active NFC Adapter
 * @param   uint8_t*    pin_list    Array of th SS pins
 * @param   uint8_t     sens_num    Total number of sensors
 *
 * @return  bool        True on success, false otherwise
 */
void init(Spool* spool, NfcAdapter* active_nfc, uint8_t* pin_list, uint8_t sens_num)
{
    char tag_msg[100];
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
        String uid_str = tag.getUidString();
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
    }
}

/**
 * setUid
 * 
 * @brief   UID string setter
 *
 * @param   String  uid     Spool tag UID String
 */
void Spool::setUid(String uid)
{
    uid_str = uid;
}


/**
 * getUid
 * 
 * @brief   Returns spool tag UID
 * 
 * @return  String  Spool tag UID
 */
String Spool::getUid()
{
    return uid_str;
}

/**
 * SetMatType
 * 
 * @brief   Set material type to spool tag
 * 
 * @param   String  mat_type    Material type
 */
void Spool::setMatType(String mat)
{
    mat_type = mat;
}


/**
 * getMatType
 * 
 * @brief   Returns material type from spool tag
 * 
 * @return  String      Spool material type
 */
String Spool::getMatType()
{
    return mat_type;
}


/**
 * setMatColor
 * 
 * @brief   Set spool material color
 * 
 * @param   String      color       Material color
 */
void Spool::setMatColor(String color)
{
    mat_color = color;
}


/**
 * getMatcolor
 * 
 * @brief   Returns the spool material color
 * 
 * @return  String      Material color
 */
String Spool::getMatColor()
{
    return mat_color;
}


/**
 * setLength
 * 
 * @brief   Set the spool length ********** remaining length o used length???? ******************
 * 
 * @param   String  length      ********** remaining length o used length???? ******************
 */
void Spool::setLength(String length)
{
    spool_length = length;
}


/**
 * getLength
 * 
 * @brief   Returns the spool length ********** remaining length o used length???? ******************
 * 
 * @return  String      ********** remaining length o used length???? ******************
 */
String Spool::getLength()
{
    return spool_length;
}


/**
 * setWeigth
 * 
 * @brief   Set the spool weight of material
 */
void Spool::setWeight(String weight)
{
    spool_weight = weight;
}

/**
 * getWeight
 * 
 * @brief   Returns spool material weight
 * 
 * @return  String      Spool material weight
 */
String Spool::getWeight()
{
    return spool_weight;
}


/**
 * setTempBed
 * 
 * @brief   Set bed temperature
 * 
 * @param   String  temp    Bed temperature
 */
void Spool::setTempBed(String temp)
{
    temp_bed = temp;
}


/**
 * getTempBed
 * 
 * @brief   Returns the bed temperature
 * 
 * @return  String      Bed temperature
 */
String Spool::getTempBed()
{
    return temp_bed;
}


/**
 * setTempExtruder
 * 
 * @brief   Set the extruder temperature
 * 
 * @param   String  temp    Extruder temperature
 */
void Spool::setTempExtruder(String temp)
{
    temp_ext = temp;
}


/**
 * getTempExtruder
 * 
 * @brief   Returns the extruder temperature
 * 
 * @return  String      Extruder temperature
 */
String Spool::getTempExtruder()
{
    return temp_ext;
}


/**
 * setBedFirstLayer
 * 
 * @brief   Set the ???????????????????????
 * 
 * @param   String      data        ?????????????????
 */
void Spool::setBedFirstLayer(String data)
{
    t_fl_b = data;
}


/**
 * getBedFirstLayer
 * 
 * @brief   Returns the ???????????????
 * 
 * @return  String      ?????????????
 */
String Spool::getBedFirstLayer()
{
    return t_fl_b;
}


/**
 * setExtFirstLayer
 * 
 * @brief   Set the ????????????
 * 
 * @param   String      data        ?????????????????
 */
void Spool::setExtFirstLayer(String data)
{
    t_fl_e = data;
}


/**
 * getExtFirstLayer
 * 
 * @brief   Returns ???????????????
 * 
 * @return  String      ??????????????
 */
String Spool::getExtFirstLayer()
{
    return t_fl_e;
}


/**
 * printToSerial
 * 
 * @brief   Output spool data to a stream
 * 
 * @param   Stream* out      output stream
 */
void Spool::printToSerial(Stream* out)
{
    if (out != NULL)
    {
        out->println("*** Sensor begin ***");
        out->print("Sensore :");
        out->println(number);
        out->println(getUid());
        out->println(getMatType());
        out->println(getMatColor());
        out->println(getLength());
        out->println(getWeight());
        out->println(getTempBed());
        out->println(getTempExtruder());
        out->println(getBedFirstLayer());
        out->println(getExtFirstLayer());
    }
}
