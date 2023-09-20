/*
// Questa è relativa all'inizializzazione del filesystem e la lettura e scrittura
// delle preference
*/
#include "init_fs.h"

extern String ssid, pass, ip, gateway;
extern Preferences preferences;

void initLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
  preferences.begin("nfc-bobine", false);
}

// Read File from LittleFS
void readPref(){
  ssid = preferences.getString("ssid", "");
  pass = preferences.getString("pass", "");
  ip = preferences.getString("ip","");
  gateway = preferences.getString("gateway","");
}

void writePref(const char * pref, const char * message){
  preferences.putString(pref,message);
  Serial.print("Preference :");
  Serial.print(pref);
  Serial.println(" setted!");
}