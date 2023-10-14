/**
 * @brief Spool class
 * 
 * Filesystem init long description.....
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */


#include "init_fs.h"

/**
 * 
 */
extern String ssid, pass, ip, gateway, n_sensors;
extern Preferences preferences;


/**
 * 
 */
void initLittleFS()
{
  if (!LittleFS.begin(true))
  {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
  preferences.begin("nfc-bobine", false);
}

/**
 * 
 */
void readPref()
{
  ssid = preferences.getString("ssid", "");
  pass = preferences.getString("pass", "");
  ip = preferences.getString("ip", "");
  gateway = preferences.getString("gateway", "");
  n_sensors = preferences.getString("n_sensors", "1");
}

/**
 * 
 */
void writePref(const char *pref, const char *message)
{
  preferences.putString(pref, message);
  Serial.print("Preference :");
  Serial.print(pref);
  Serial.println(" setted!");
}