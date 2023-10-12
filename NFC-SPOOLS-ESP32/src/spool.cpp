#include "spool.h"

Spool::Spool(String uid_str)
{
    this->uid_str = uid_str;
}

void Spool::put_mat_type(String mat_type)
{
    this->mat_type = mat_type;
}
String Spool::get_mat_type()
{
    return this->mat_type;
}
void Spool::put_mat_color(String mat_color)
{
    this->mat_color = mat_color;
}
String Spool::get_mat_color()
{
    return this->mat_color;
}
void Spool::put_lenght(String spool_lenght)
{
    this->spool_lenght = spool_lenght;
}
String Spool::get_lenght()
{
    return this->spool_lenght;
}
void Spool::put_weigth(String spool_weigth)
{
    this->spool_weigth = spool_weigth;
}
String Spool::get_weigth()
{
    return this->spool_weigth;
}
void Spool::put_temp_bed(String temp_bed)
{
    this->temp_bed = temp_bed;
}
String Spool::get_temp_bed()
{
    return this->temp_bed;
}
void Spool::put_temp_extruder(String temp_ext)
{
    this->temp_ext = temp_ext;
}
String Spool::get_temp_extruder()
{
    return this->temp_ext;
}
void Spool::put_bed_first_layer(String t_fl_b)
{
    this->t_fl_b = t_fl_b;
}
String Spool::get_bed_first_layer()
{
    return this->t_fl_b;
}
void Spool::put_ext_first_layer(String t_fl_e)
{
    this->t_fl_e = t_fl_e;
}
String Spool::get_ext_first_layer()
{
    return this->t_fl_e;
}