#ifndef WEBSERVER_H_
#define WEBSERVER_H_

void notFound(AsyncWebServerRequest *request);
void get_order(AsyncWebServerRequest *request);
void get_settings(AsyncWebServerRequest *request);
void set_settings(AsyncWebServerRequest *request);
void get_temp_reading(AsyncWebServerRequest *request);
void get_acc_reading(AsyncWebServerRequest *request);

#endif