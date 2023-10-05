#include "new_tag_read.h"

extern MFRC522 mfrc522_1;
extern MFRC522 mfrc522_2;
extern MFRC522 mfrc522_3;
extern MFRC522 mfrc522_4;

extern char uid[30], tag_msg[100];
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;

bool tag_read(int sensor){
    switch (sensor)
    {
    case 1 :
        NfcAdapter nfc = NfcAdapter(&mfrc522_1);
        /* code */
        break;
    case 2 :
        NfcAdapter nfc = NfcAdapter(&mfrc522_2);
        /* code */
        break;
    case 3 :
        NfcAdapter nfc = NfcAdapter(&mfrc522_3);
        /* code */
        break;
    case 4 :
        NfcAdapter nfc = NfcAdapter(&mfrc522_4);
        /* code */
        break;
    default:
        break;
    }
    if (nfc.tagPresent()){
      NfcTag tag = nfc.read();
      uid_str = tag.getUidString(); 
      uid_str.toCharArray(uid, uid_str.length() + 1);
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
          loader(i,tag_msg_str);
        }
      }
    return true;
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