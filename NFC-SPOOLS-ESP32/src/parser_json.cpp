/**
 * @brief Spool class
 * 
 * JSon Parser long description.....
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */

#include "parser_json.h"


/**
 * 
 */
extern String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;

/**
 * 
 */
String parser(int sensor)
{
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
  String response;
  serializeJson(data, response);
  return response;
}