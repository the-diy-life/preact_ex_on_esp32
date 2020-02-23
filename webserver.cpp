#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "webserver.h"
#include "main.h"
#include "fsparameter.h"

extern struct settings system_settings;
extern int RawValue;
extern float acc_x;   // ADXL345 Accelerometer X value
extern float acc_y;   // ADXL345 Accelerometer Y value
extern float acc_z;   // ADXL345 Accelerometer Z value
int order = 1;

/*
  for server if not found page
  @param *request AsyncWebServerRequest
*/
void notFound(AsyncWebServerRequest *request) {

  request->send(404, "text/plain", "Not found");
}

/**
   handle /getTempReading route. this route fills the analog sensor page by raw value
*/
void get_temp_reading(AsyncWebServerRequest *request) {
  
  char json[50];

  snprintf(json, 50, "{\"rawvalue\": %d }", RawValue);

  DEBUG_PRINTLN("\n Sending Temprature reading");
  DEBUG_PRINTLN(json);
  // send the json
//  request->send(200, "text/json", json);
  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", json);
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

/**
   handle /getAccReading route. this route fills the Accelerometer page by x, y, and z values   
*/
void get_acc_reading(AsyncWebServerRequest *request) {

  char Accelerometer[50];

  sprintf(Accelerometer, "\"X: %.2f Y: %.2f Z: %.2f\"", acc_x, acc_y, acc_z);
  DEBUG_PRINT("Acceleration String: ");
  DEBUG_PRINT(Accelerometer);

  char json[100];

  snprintf(json, 100, "{\"X\": %.2f ,\"Y\": %.2f , \"Z\": %.2f }", acc_x, acc_y, acc_z);

  DEBUG_PRINTLN("\n Sending Accelerometer reading");
  DEBUG_PRINTLN(json);
  // send the json
//  request->send(200, "text/json", json);
  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", json);
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

/**
   handle /getSettings route this route fill the settings page form with the previous
   initialized values. useful so that the user will not re-fill everything when needs to change single parameter.
   response example {"IT":"30s", "E":"Enable","AK":"2d23rf56hi", "field1":"temperatureC","field2":"x", "field3":"x", "field4":"x" }
   "IT" stands for interval time, "E" stands for Enable, and "AK" stands for api key
*/
void get_settings(AsyncWebServerRequest *request) {
  char json[500] = {0};

  snprintf(json, 500, "{\"IT\": %d ,\"E\": %d,\"AK\": \"%s\", \"field1\": \"%s\",\"field2\": \"%s\", \"field3\": \"%s\",\"field4\": \"%s\"}",
           system_settings.interval_time, system_settings.Enable, system_settings.api_key,
           system_settings.field1, system_settings.field2, system_settings.field3, system_settings.field4);
  // send the json
//  request->send(200, "text/json", json);
  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", json);
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);

  DEBUG_PRINTLN("\n Sending get_settings");
  DEBUG_PRINTLN(json);
}

/**
   /set_settings route. this handles the submit button for the form on the settings.htm webpage.
   current parameters handled "IT" stands for interval time, "E" stands for Enable, "AK" stands for api key,
   "field1" ,"field2", "field3" ,"field4".
   Then save the parameters to the json config file.
*/
void set_settings(AsyncWebServerRequest *request) {

  DEBUG_PRINT("Settings...");
  String retFileName = "/index.htm";
  int paramsNr = request->params();
  DEBUG_PRINT("paramsNr: ");
  DEBUG_PRINTLNDEC(paramsNr);
  String val;

  if (paramsNr >= 1)
  {
    for (int i = 0; i < paramsNr - 1; i++) {
      AsyncWebParameter* p = request->getParam(i);

      DEBUG_PRINTLN("In response arg is: " );
      if (p->name() == "submit") {

        DEBUG_PRINT("submit arg:\t");
        DEBUG_PRINTLN(p->value());
      }
      if (p->name() == "IT") {
        DEBUG_PRINT("User entered IT:\t");
        // p->value().toInt(system_settings.interval_time);
        val = p->value();
        DEBUG_PRINT(p->value());
        system_settings.interval_time = val.toInt();

        DEBUG_PRINTLN(system_settings.interval_time);
      }
      if (p->name() == "E") {
        DEBUG_PRINT("User entered E:\t");
        // p->value().toUInt(system_settings.Enable);
        val = p->value();
        DEBUG_PRINT(p->value());
        system_settings.Enable = val.toInt();
        DEBUG_PRINTLN(system_settings.Enable);
      }
      if (p->name() == "AK") { // TW4UGOTYNXY8WIOX
        DEBUG_PRINT("User entered AK:\t");
        DEBUG_PRINT(p->value());
        p->value().toCharArray(system_settings.api_key, 50);
        DEBUG_PRINTLN(system_settings.api_key);
      }
      if (p->name() == "field1") {
        DEBUG_PRINT("User entered:\t");
        p->value().toCharArray(system_settings.field1, 50);
        DEBUG_PRINTLN(system_settings.field1);
      }
      if (p->name() == "field2") {
        DEBUG_PRINT("User entered:\t");
        p->value().toCharArray(system_settings.field2, 50);
        DEBUG_PRINTLN(system_settings.field2);
      }
      if (p->name() == "field3") {
        DEBUG_PRINT("User entered:\t");
        p->value().toCharArray(system_settings.field3, 50);
        DEBUG_PRINTLN(system_settings.field3);
      }
      if (p->name() == "field4") {
        DEBUG_PRINT("User entered:\t");
        p->value().toCharArray(system_settings.field4, 50);
        DEBUG_PRINTLN(system_settings.field4);
      }
    }
    writeFSParameters();
//    return request->send(SPIFFS, "/success.htm", "text/html");
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
    }
  }


  /**
   /getOrder route. this handles the order comes from website to turn on/off led connected to the controller.
   current parameters handled "order"
*/
void get_order(AsyncWebServerRequest *request) {

  DEBUG_PRINT("Order...");
  String retFileName = "/index.htm";
  int paramsNr = request->params();
  String val;

  DEBUG_PRINT("paramsNr: ");
  DEBUG_PRINTLNDEC(paramsNr);

  if (paramsNr >= 1) {
    for (int i = 0; i <= paramsNr - 1; i++) {
      AsyncWebParameter* p = request->getParam(i);

      DEBUG_PRINTLN("In response arg is: ");
      if (p->name() == "submit") {
        DEBUG_PRINT("submit arg:\t");
        DEBUG_PRINTLN(p->value());
      }
      if (p->name() == "order") {
        DEBUG_PRINT("User entered:\t");
        val = p->value();
        order = val.toInt();
        // p->value().toInt(order, 50);
        DEBUG_PRINTLN(order);
      }   
    }
//    return request->send(SPIFFS, "/success.htm", "text/html");
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  }
}