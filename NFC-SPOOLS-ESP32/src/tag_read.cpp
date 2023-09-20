#include "tag_read.h"
/*
#define SS_PIN_1 4    // ESP32 pin GPIO4
#define SS_PIN_2 5    // ESP32 pin GPIO5 
#define SS_PIN_3 6    // ESP32 pin GPIO4
#define SS_PIN_4 7    // ESP32 pin GPIO5
#define MAX_SENSORS 4 //max number of sensors 
#define RST_PIN 27    // ESP32 pin GPIO27
*/
extern MFRC522 mfrc522_1;//(SS_PIN_1, RST_PIN);
extern MFRC522 mfrc522_2;//(SS_PIN_2, RST_PIN);

extern NfcAdapter nfc_1;// = NfcAdapter(&mfrc522_1);
extern NfcAdapter nfc_2;//= NfcAdapter(&mfrc522_2);

extern char uid[30], tag_msg[100];
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;
bool tag_read(int sensor){
 
  if (sensor == 1){
    //Serial.print("TAG.......");
    //Serial.print("Sensore :");
    ///Serial.println(sensor);
    if (nfc_1.tagPresent()){
      NfcTag tag = nfc_1.read();
      //Serial.print("UID: ");
      uid_str = tag.getUidString(); 
      uid_str.toCharArray(uid, uid_str.length() + 1);
      //Serial.println(uid_str);
      if (tag.hasNdefMessage()){ 
        NdefMessage message = tag.getNdefMessage();
        int recordCount = message.getRecordCount();
        for (int i = 0; i < recordCount; i++){
          NdefRecord record = message.getRecord(i);
          int payloadLength = record.getPayloadLength();
          const byte *payload = record.getPayload();
          String tag_msg_str = "";
          for (int c = 3; c < payloadLength; c++) {
            tag_msg_str += (char)payload[c];
          }
          tag_msg_str.toCharArray(tag_msg, tag_msg_str.length() + 1);
          //Serial.println(tag_msg_str);
          loader(i,tag_msg_str);
        }
      }
    return true;
    }
  } 
  if (sensor == 2){
    //Serial.print("TAG.......");
    //Serial.print("Sensore :");
    //Serial.println(sensor);
    if (nfc_2.tagPresent()){
      NfcTag tag = nfc_2.read();
      //Serial.print("UID: ");
      uid_str = tag.getUidString(); 
      uid_str.toCharArray(uid, uid_str.length() + 1);
      //Serial.println(uid_str);
      if (tag.hasNdefMessage()){ 
        NdefMessage message = tag.getNdefMessage();
        int recordCount = message.getRecordCount();
        for (int i = 0; i < recordCount; i++){
          NdefRecord record = message.getRecord(i);
          int payloadLength = record.getPayloadLength();
          const byte *payload = record.getPayload();
          String tag_msg_str = "";
          for (int c = 3; c < payloadLength; c++) {
            tag_msg_str += (char)payload[c];
          }
          tag_msg_str.toCharArray(tag_msg, tag_msg_str.length() + 1);
          //Serial.println(tag_msg_str);
          loader(i,tag_msg_str);
        }
      }
    return true;
    }
  } 
  return false;
}

void loader(int i ,String tag_msg_str){
  switch (i) {
    case 0:
      mat_type = tag_msg_str;
      break;
    case 1:
      mat_color = tag_msg_str;
      break;
    case 2:
      spool_lenght = tag_msg_str;
      break;
    case 3:
      spool_weigth = tag_msg_str;
      break;
    case 4:
      temp_bed = tag_msg_str; 
      break;
    case 5:
      temp_ext = tag_msg_str;
      break;
    case 6:
      t_fl_b = tag_msg_str;
      break;
    case 7:
      t_fl_e = tag_msg_str;
      break;
    default :
      break;
  }
}