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

#ifndef _SPOOL_H
#define _SPOOL_H

#include <Arduino.h>

class Spool
{
    private:
        String uid_str, mat_type, mat_color, spool_lenght, spool_weigth, temp_bed, temp_ext, t_fl_b, t_fl_e;

    public:
        Spool();
        Spool(String uid_str);
        String get_spool_uid();
        void put_mat_type(String mat_type);
        String get_mat_type();
        void put_mat_color(String mat_color);
        String get_mat_color();
        void put_lenght(String spool_lenght);
        String get_lenght();
        void put_weigth(String spool_weigth);
        String get_weigth();
        void put_temp_bed(String temp_bed);
        String get_temp_bed();
        void put_temp_extruder(String temp_ext);
        String get_temp_extruder();
        void put_bed_first_layer(String t_fl_b);
        String get_bed_first_layer();
        void put_ext_first_layer(String t_fl_e);
        String get_ext_first_layer();
};

#endif