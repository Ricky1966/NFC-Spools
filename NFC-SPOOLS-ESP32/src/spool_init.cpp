/**
 * @brief Web Server
 *
 * Web Server pages definition.....
 *
 * @author Ricky1966
 * @author simonegallina (supervisor)
 *
 * @version 1.0
 */

#include "spool.h"
#include "spool_init.h"

bool spool_print(int sensor, Spool *spool)
{
    Serial.println("Sensore");
    Serial.println(spool->get_spool_uid());
    Serial.println(spool->get_mat_type());
    Serial.println(spool->get_mat_color());
    Serial.println(spool->get_lenght());
    Serial.println(spool->get_weigth());
    Serial.println(spool->get_temp_bed());
    Serial.println(spool->get_temp_extruder());
    Serial.println(spool->get_bed_first_layer());
    Serial.println(spool->get_ext_first_layer());
    return true;
}
