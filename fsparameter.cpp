
#include <WiFi.h> // Load Wi-Fi library
#include <FS.h>
#include "SPIFFS.h"
#include <string.h>
#include <WebServer.h>
#include "ArduinoJson.h"
#include <Arduino.h>
#include "main.h"
#include "fsparameter.h"

struct settings system_settings;
// check if config file exist
int conf_exist = 0;

void spiffs_init(){
  // start the flash file system
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount file system");
    return;
  }

  // list SPIFFS contents
  File root = SPIFFS.open("/");
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      DEBUG_PRINT("  DIR : ");
      DEBUG_PRINTLN(file.name());
    } else {
      DEBUG_PRINT("  FILE: ");
      DEBUG_PRINT(file.name());
      if (strcmp(file.name(), "/config.json") == 0)
      {
        conf_exist = 1;
        DEBUG_PRINT("\tconfig file exist");
      }
      DEBUG_PRINT("\tSIZE: ");
      DEBUG_PRINTLN(file.size());
    }
    file = root.openNextFile();
  }

  // check if configuration file exist and if true read settings structure from it else write to implement it
  if (conf_exist == 1)
  {
    readFSParameters();
  }
  else
  {
    DEBUG_PRINTLN("create and write to config file");
    writeFSParameters();
  }

}
/**
    write the SPIFFS parameters, for our case they are:
    interval_time
    Enable
    api_key
    field1
    field2
    field3
    field4
*/
void writeFSParameters(void) {

  //save the custom parameters to FS
  //if (shouldSaveConfig) {
  Serial.println("saving config");
  DynamicJsonDocument doc(1024);
  JsonObject json = doc.to<JsonObject>();

  json["interval_time"] = system_settings.interval_time;
  json["Enable"] = system_settings.Enable;
  json["api_key"] = system_settings.api_key;
  json["field1"] = system_settings.field1;
  json["field2"] = system_settings.field2;
  json["field3"] = system_settings.field3;
  json["field4"] = system_settings.field4;

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
//  serializeJson(json, Serial);
  serializeJson(json, configFile);
  configFile.close();

}

/**
    read the SPIFFS saved parameters, for our case they are \n
    interval_time
    Enable
    api_key
    field1
    field2
    field3
    field4    
    @return 0: no errors\n
            1: failed to read the parameters.
*/
int  readFSParameters(void) {
  //  read configuration from FS json
  Serial.println("mounting FS...");
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //  file exists, reading and loading
      DEBUG_PRINTLN("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        DEBUG_PRINTLN("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(1024);
        auto error = deserializeJson(json, buf.get());
        if (error) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(error.c_str());
            return 1;
        }
        serializeJson(json, Serial);
        DEBUG_PRINTLN("\nparsed json");

        if (json.containsKey("interval_time"))
          system_settings.interval_time = json["interval_time"];
          // snprintf(system_settings.interval_time, 10, atoi(json["interval_time"]));
        else
          Serial.println("failed to load json config");
        if (json.containsKey("Enable"))
          system_settings.Enable = json["Enable"];
        if (json.containsKey("api_key"))
          strcpy(system_settings.api_key, json["api_key"]);
        if (json.containsKey("field1"))
          strcpy(system_settings.field1, json["field1"]);
        if (json.containsKey("field2"))
          strcpy(system_settings.field2, json["field2"]);
        if (json.containsKey("field3"))
          strcpy(system_settings.field3, json["field3"]);
        if (json.containsKey("field4"))
          strcpy(system_settings.field4, json["field4"]);
       
        return 0;
      } else
        Serial.println("failed to open the file!");
    } else
      Serial.println("file doesn't exists!");
  } else {
    Serial.println("failed to mount FS");
  }
  return 1;
}
