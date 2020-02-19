#ifndef FSPARAMETER_H_
#define FSPARAMETER_H_


/**
   Structure for saved settings in the config json file
*/
struct settings {

  /// settings parameters
  int interval_time;
  int Enable;
  char api_key[32];
  char field1[15];
  char field2[15];
  char field3[15];
  char field4[15];
  
};

void spiffs_init(void);
void writeFSParameters(void);
int  readFSParameters(void);

#endif
