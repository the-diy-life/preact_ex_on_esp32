#ifndef MAIN_H_
#define MAIN_H_

#define ANALOG_PIN                34 //  15

#define DEBUG


#ifdef DEBUG
#define DEBUG_PRINT(x)           Serial.print (x)
#define DEBUG_PRINTDEC(x)        Serial.print (x, DEC)
#define DEBUG_PRINTLN(x)         Serial.println (x)
#define DEBUG_PRINTLNDEC(x)      Serial.println (x, DEC)
#define DEBUG_PRINTF(x)          Serial.printf (x)
#define DEBUG_PRINTF3(x, y, z)   Serial.printf (x)
#define DEBUG_PRINTBIN(x)        Serial.print (x, BIN)
#define DEBUG_PRINTLNBIN(x)      Serial.println (x, BIN)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLNDEC(x)
#define DEBUG_PRINTF(x)
#define DEBUG_PRINTF3(x, y, z)
#define DEBUG_PRINTBIN(x)        
#define DEBUG_PRINTLNBIN(x)      
#endif

#endif
