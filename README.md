# ESP32 Preact Example
----
## Description
> This project is an example for add preact website on ESP32 as a webserver.

## Hardware
1. esp32
2. LM35 Temperature sensor.
3. ADXL345 Accelerometer sensor.

## External Libraries

### ArduinoJson
We are using andruino json library by Benoît Blanchon to create and read the configration file in the SPIFFS, Benoît Blanchon thank you. To install ArduinoJson [library](https://github.com/bblanchon/ArduinoJson).

### ESPAsyncWebServer
Async HTTP and WebSocket Server for ESP8266 Arduino
To install ESPAsyncWebServer [library](https://github.com/me-no-dev/ESPAsyncWebServer#espasyncwebserver).

### Adafruit_ADXL345_U
Unified driver for the ADXL345 Accelerometer. It is based on Adafruit's Unified Sensor Library (https://github.com/adafruit/Adafruit_Sensor).
The Adafruit Unified Sensor Library provides a common interface and data type for any supported sensor. It defines some basic information about the sensor (sensor limits, etc.), and returns standard SI units of a specific type and scale for each supported sensor type.
You can use the data right away because it's already converted to SI units that you understand and can compare, rather than meaningless values like 0..1023.
To install Adafruit_ADXL345_U [library](https://github.com/adafruit/Adafruit_ADXL345).

## Wiring

### LM35 Temprature sensor
GND         GND
3.3V        VCC
Pin 34      Output

### I2C sensor ADXL345
GND         GND
3.3V        VCC
pin 21      (SDA)
pin 22      (SCL)

## How It Works
The LM35 sensor is reading analog value, and send it as json text in webserver request. The ADXL345 is reading acceleration, and send it too as json. 
In the client side by preact it convert the analog raw vale to temprature reading, and display the acceleration in visualize way. When online send the reading to thingspeak website by the configration that display in settings page, which listed below:
1-  interval_time
2-  Enable
3-  api_key
4-  field1
5-  field2
6-  field3
7-  field4
