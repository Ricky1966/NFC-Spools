/**
 * @brief Spool class
 *
 * Spool class long description.....
 *
 * @author Ricky1966
 * @author simonegallina (supervisor)
 *
 * @version 1.0
 */

#include "spool.h"

/**
 *
 */
Spool::Spool() {}

/**
 *
 */
Spool::Spool(String uid_str)
{
    this->uid_str = uid_str;
    Serial.println("Oggetto creato");
}

/**
 *
 */
void Spool::put_uid_str(String uid)
{
    this->uid_str = uid;
    Serial.println("Oggetto inserito");
}

/**
 *
 */
String Spool::get_spool_uid()
{
    return uid_str;
}

/**
 *
 */
void Spool::put_mat_type(String mat_type)
{
    this->mat_type = mat_type;
}

/**
 *
 */
String Spool::get_mat_type()
{
    return mat_type;
}

/**
 *
 */
void Spool::put_mat_color(String mat_color)
{
    this->mat_color = mat_color;
}

/**
 *
 */
String Spool::get_mat_color()
{
    return mat_color;
}

/**
 *
 */
void Spool::put_lenght(String spool_lenght)
{
    this->spool_lenght = spool_lenght;
}

/**
 *
 */
String Spool::get_lenght()
{
    return spool_lenght;
}

/**
 *
 */
void Spool::put_weigth(String spool_weigth)
{
    this->spool_weigth = spool_weigth;
}

/**
 *
 */
String Spool::get_weigth()
{
    return spool_weigth;
}

/**
 *
 */
void Spool::put_temp_bed(String temp_bed)
{
    this->temp_bed = temp_bed;
}

/**
 *
 */
String Spool::get_temp_bed()
{
    return temp_bed;
}

/**
 *
 */
void Spool::put_temp_extruder(String temp_ext)
{
    this->temp_ext = temp_ext;
}

/**
 *
 */
String Spool::get_temp_extruder()
{
    return temp_ext;
}

/**
 *
 */
void Spool::put_bed_first_layer(String t_fl_b)
{
    this->t_fl_b = t_fl_b;
}

/**
 *
 */
String Spool::get_bed_first_layer()
{
    return t_fl_b;
}

/**
 *
 */
void Spool::put_ext_first_layer(String t_fl_e)
{
    this->t_fl_e = t_fl_e;
}

/**
 *
 */
String Spool::get_ext_first_layer()
{
    return t_fl_e;
}