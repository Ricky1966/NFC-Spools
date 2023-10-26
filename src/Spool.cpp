/**
 * @brief Spool class
 * 
 * @author Ricky1966
 * @author simonegallina
 * 
 * @version 2.0
 */

#include "Spool.h"


/**
 * Spool
 * 
 * @brief   Constructor
 *
 */
Spool::Spool()
{
    init();
}


/**
 * Spool
 * 
 * @brief   Constructor
 * 
 * @param   String  uid     Spool tag UID string
 */
Spool::Spool(String uid)
{
    init();
    uid_str = uid;
}


/**
 * Spool
 * 
 * @brief   Constructor
 * 
 * @param   uint8_t     m       Spool number
 */
Spool::Spool(uint8_t m)
{
    init();
    number = m;
}


/**
 * setNumber
 * 
 * @brief   Set the spool number
 * 
 * @param   uint8_t     m       Spool number
 */
void Spool::setNumber(uint8_t m)
{
    number = m;
}


/**
 * getnumber
 * 
 * @brief   Returns the spool number
 * 
 * @return  uint8_t     Spool number
 */
uint8_t Spool::getNumber()
{
    return number;
}


/**
 * init
 * 
 * @brief   Initializes the object properties
 */
void Spool::init()
{
    uid_str = "";
    mat_type = "";
    mat_color = "";
    spool_length = "";
    spool_weight = "";
    temp_bed = "";
    temp_ext = "";
    t_fl_b = "";
    t_fl_e = "";
}


/**
 * setUid
 * 
 * @brief   UID string setter
 *
 * @param   String  uid     Spool tag UID String
 */
void Spool::setUid(String uid)
{
    uid_str = uid;
}


/**
 * getUid
 * 
 * @brief   Returns spool tag UID
 * 
 * @return  String  Spool tag UID
 */
String Spool::getUid()
{
    return uid_str;
}

/**
 * SetMatType
 * 
 * @brief   Set material type to spool tag
 * 
 * @param   String  mat_type    Material type
 */
void Spool::setMatType(String mat)
{
    mat_type = mat;
}


/**
 * getMatType
 * 
 * @brief   Returns material type from spool tag
 * 
 * @return  String      Spool material type
 */
String Spool::getMatType()
{
    return mat_type;
}


/**
 * setMatColor
 * 
 * @brief   Set spool material color
 * 
 * @param   String      color       Material color
 */
void Spool::setMatColor(String color)
{
    mat_color = color;
}


/**
 * getMatcolor
 * 
 * @brief   Returns the spool material color
 * 
 * @return  String      Material color
 */
String Spool::getMatColor()
{
    return mat_color;
}


/**
 * setLength
 * 
 * @brief   Set the spool length ********** remaining length o used length???? ******************
 * 
 * @param   String  length      ********** remaining length o used length???? ******************
 */
void Spool::setLength(String length)
{
    spool_length = length;
}


/**
 * getLength
 * 
 * @brief   Returns the spool length ********** remaining length o used length???? ******************
 * 
 * @return  String      ********** remaining length o used length???? ******************
 */
String Spool::getLength()
{
    return spool_length;
}


/**
 * setWeigth
 * 
 * @brief   Set the spool weight of material
 */
void Spool::setWeight(String weight)
{
    spool_weight = weight;
}

/**
 * getWeight
 * 
 * @brief   Returns spool material weight
 * 
 * @return  String      Spool material weight
 */
String Spool::getWeight()
{
    return spool_weight;
}


/**
 * setTempBed
 * 
 * @brief   Set bed temperature
 * 
 * @param   String  temp    Bed temperature
 */
void Spool::setTempBed(String temp)
{
    temp_bed = temp;
}


/**
 * getTempBed
 * 
 * @brief   Returns the bed temperature
 * 
 * @return  String      Bed temperature
 */
String Spool::getTempBed()
{
    return temp_bed;
}


/**
 * setTempExtruder
 * 
 * @brief   Set the extruder temperature
 * 
 * @param   String  temp    Extruder temperature
 */
void Spool::setTempExtruder(String temp)
{
    temp_ext = temp;
}


/**
 * getTempExtruder
 * 
 * @brief   Returns the extruder temperature
 * 
 * @return  String      Extruder temperature
 */
String Spool::getTempExtruder()
{
    return temp_ext;
}


/**
 * setBedFirstLayer
 * 
 * @brief   Set the ???????????????????????
 * 
 * @param   String      data        ?????????????????
 */
void Spool::setBedFirstLayer(String data)
{
    t_fl_b = data;
}


/**
 * getBedFirstLayer
 * 
 * @brief   Returns the ???????????????
 * 
 * @return  String      ?????????????
 */
String Spool::getBedFirstLayer()
{
    return t_fl_b;
}


/**
 * setExtFirstLayer
 * 
 * @brief   Set the ????????????
 * 
 * @param   String      data        ?????????????????
 */
void Spool::setExtFirstLayer(String data)
{
    t_fl_e = data;
}


/**
 * getExtFirstLayer
 * 
 * @brief   Returns ???????????????
 * 
 * @return  String      ??????????????
 */
String Spool::getExtFirstLayer()
{
    return t_fl_e;
}


/**
 * printToSerial
 * 
 * @brief   Output spool data to a stream
 * 
 * @param   Stream* out      output stream
 */
void Spool::printToSerial(Stream* out)
{
    if (out != NULL)
    {
        out->println("*** Sensor begin ***");
        out->println("Sensore :" + number);
        out->println(getUid());
        out->println(getMatType());
        out->println(getMatColor());
        out->println(getLength());
        out->println(getWeight());
        out->println(getTempBed());
        out->println(getTempExtruder());
        out->println(getBedFirstLayer());
        out->println(getExtFirstLayer());
    }
}
