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

#include "tag_read.h"
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
 * loader
 * @brief Set data to a tag
 * 
 * @param int     i           Data type
 * @param String  tag_msg_str Contains message read from tag 
 * @param Spool*  spool       Active spool
 */
void loader(int i, String tag_msg_str, Spool* spool)
{
  switch (i)
  {
  case 0:
    mat_type = tag_msg_str;
    spool->put_mat_type(tag_msg_str);
    break;

  case 1:
    mat_color = tag_msg_str;
    spool->put_mat_color(tag_msg_str);
    break;

  case 2:
    spool_lenght = tag_msg_str;
    spool->put_lenght(tag_msg_str);
    break;

  case 3:
    spool_weigth = tag_msg_str;
    spool->put_weigth(tag_msg_str);
    break;

  case 4:
    temp_bed = tag_msg_str;
    spool->put_temp_bed(tag_msg_str);
    break;

  case 5:
    temp_ext = tag_msg_str;
    spool->put_temp_extruder(tag_msg_str);
    break;

  case 6:
    t_fl_b = tag_msg_str;
    spool->put_bed_first_layer(tag_msg_str);
    break;

  case 7:
    t_fl_e = tag_msg_str;
    spool->put_ext_first_layer(tag_msg_str);
    break;

  default:
    break;
  }
}


/**
 * tag_read
 * @brief Extracts data from tag
 * 
 * @param   int sensor  Sensor number
 * 
 * @return  bool        Operation exit code
 */
bool tag_read(int sensor)
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
      break;
    default:
      break;
    }

    if (active_nfc->tagPresent())
    {
      NfcTag tag = active_nfc->read();
      uid_str = tag.getUidString();
      uid_str.toCharArray(uid, uid_str.length() + 1);
      Spool spool1 = Spool(uid_str);
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
          loader(i, tag_msg_str, &spool1);
        }
      }
      Serial.print("Oggetto");
      Serial.println("");
      Serial.println(spool1.get_lenght());
      Serial.println(spool1.get_weigth());
      return true;
    }
  }
  return false;
}


/**
 * tag_read_init
 * 
 * @brief Initializes spools for reading
 * 
 * @param int sensor    Number of available sensors
 * @param Spool*  spool Available spools array
 */
bool tag_read_init(int sensor, Spool* spool)
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
      Serial.println("Sensore 0");
      break;
    case 1:
      digitalWrite(SS_PIN_1, HIGH);
      digitalWrite(SS_PIN_2, LOW);
      digitalWrite(SS_PIN_3, HIGH);
      active_nfc = &nfc_2;
      Serial.println("Sensore 1");
      break;
    case 2:
      digitalWrite(SS_PIN_1, HIGH);
      digitalWrite(SS_PIN_2, HIGH);
      digitalWrite(SS_PIN_3, LOW);
      active_nfc = &nfc_3;
      Serial.println("Sensore 2");
      break;
    default:
      break;
    }

    if (active_nfc->tagPresent())
    {
      NfcTag tag = active_nfc->read();
      uid_str = tag.getUidString();
      spool[sensor] = Spool(uid_str);
      Serial.println(uid_str);
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
          Serial.println(tag_msg_str);
          loader(i, tag_msg_str, spool);
        }
      }
      Serial.println("Oggetto creato");
      Serial.println(spool->get_spool_uid());
      Serial.println(spool->get_mat_type());
      Serial.println(spool->get_mat_color());
      return true;
    }
  }
  
  return false;
}