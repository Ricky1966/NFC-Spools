/**
 * @brief JSon parser
 * 
 * JSon Parser definition for a JSon
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#include "parser_json.h"


/**
 * External variables 
 */
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;

/**
 * parser
 * @brief JSon parser for API
 * 
 * @param   int sensor  Sensor number
 *
 * @return  String	    Parsed data
 */
String parser(int sensor)
{
	String response;
	StaticJsonDocument<300> data;

    Serial.print("JSn called, sensor :");
    Serial.println(sensor);
    data["Spot"] = sensor;
    data["UID"] = uid_str;
    data["Material"] = mat_type;
    data["Color"] = mat_color;
    data["Lenght"] = spool_lenght;
    data["Weigth"] = spool_weigth;
    data["T_Bed"] = temp_bed;
    data["T_Ext"] = temp_ext;
    data["T_fl_Bed"] = t_fl_b;
    data["T_fl_Ext"] = t_fl_e;
    
    serializeJson(data, response);
    return response;
}
