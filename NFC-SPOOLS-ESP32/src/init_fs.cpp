/**
 * @brief Filesystem
 * 
 * FileSystem initializationof filesystem and read/write preference
 * 
 * @author Ricky1966
 * @author simonegallina (supervisor)
 * 
 * @version 1.0
 */


#include "init_fs.h"

/**
 * External variables 
 */
extern String ssid, pass, ip, gateway, n_sensors;
extern Preferences preferences;


/**
 * initLittleFS
 * @brief initialization of Filesystem
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
 * readPref
 * @brief read stored preferences
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
 * writePref
 * @brief write preferences passed by setup.html
 * 
 * @param const char  *pref     pointer to preference name
 * @param const char  *message  pointer to preference value
 */
void writePref(const char *pref, const char *message)
{
  preferences.putString(pref, message);
  Serial.print("Preference :");
  Serial.print(pref);
  Serial.println(" setted!");
}