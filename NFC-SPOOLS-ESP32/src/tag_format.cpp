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
extern char uid[30], tag_msg[100];
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;
extern Spool spool[];

/**
 * tag_format
 * @brief   tag formatter function
 */
bool tag_format()
{
    return true;
}