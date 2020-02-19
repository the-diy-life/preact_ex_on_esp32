
#include <WebServer.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h> // Load Wi-Fi library

#include "webserver.h"
#include "adxl345.h"
#include "main.h"
#include "fsparameter.h"

//const int analog_pin = 15;

int RawValue = 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer async_server(80);

/* Methods prototype */
void webserver_init(void);
void setup_wifi(void);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  spiffs_init();
  webserver_init();
}

void loop() {
  
  RawValue = analogRead(ANALOG_PIN);
  Voltage = (RawValue / 2048.0) * 3300; // 5000 to get millivots.
  tempC = Voltage * 0.1;
  tempF = (tempC * 1.8) + 32; // conver to F
  read_acceleration();  
}

/*
   initalise the server pages requests
*/
void webserver_init(void) {
  /*
    server handle requests
  */
  async_server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");

//  async_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send(200, "text/plain", "Hello, world");
//        });  
  // send the json string that came from fsparameters to the server
  async_server.on("/getSettings", HTTP_GET, get_settings);
  
  // Get the new data from server.
  async_server.on("/settings", HTTP_POST, set_settings);

  async_server.on("/getOrder", HTTP_POST, get_order);

  async_server.on("/getTempReading", HTTP_GET, get_temp_reading);

  async_server.on("/getAccReading", HTTP_GET, get_acc_reading);

  async_server.onNotFound(notFound);

  // Start server
  async_server.begin();
}

/**
  function to start the WiFi connection
*/
void setup_wifi()
{
  delay(10);
  /* We start by connecting to a WiFi network */
  Serial.println();
  Serial.print("Connecting ");


  //WiFi.begin(ssid, password);
  WiFi.begin("WE_B747A0", "k6518520");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

//  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
