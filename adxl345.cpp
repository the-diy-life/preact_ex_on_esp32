#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include "adxl345.h"
//#include "SensorsReading.h"
#include "main.h"

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

float acc_x = 1340;   // ADXL345 Accelerometer X value
float acc_y = 3453;   // ADXL345 Accelerometer Y value
float acc_z = 1230;   // ADXL345 Accelerometer Z value

/*
 * Display sensor information.
*/
void displayADXLSensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  DEBUG_PRINTLN("------------------------------------");
  DEBUG_PRINT  ("Sensor:       "); DEBUG_PRINTLN(sensor.name);
  DEBUG_PRINT  ("Driver Ver:   "); DEBUG_PRINTLN(sensor.version);
  DEBUG_PRINT  ("Unique ID:    "); DEBUG_PRINTLN(sensor.sensor_id);
  DEBUG_PRINT  ("Max Value:    "); DEBUG_PRINT(sensor.max_value); DEBUG_PRINTLN(" m/s^2");
  DEBUG_PRINT  ("Min Value:    "); DEBUG_PRINT(sensor.min_value); DEBUG_PRINTLN(" m/s^2");
  DEBUG_PRINT  ("Resolution:   "); DEBUG_PRINT(sensor.resolution); DEBUG_PRINTLN(" m/s^2");
  DEBUG_PRINTLN("------------------------------------");
  DEBUG_PRINTLN("");
  delay(500);
}

/*
 * Get sensor data rate and display it.
*/
void displayDataRate(void)
{
  DEBUG_PRINT  ("Data Rate:    ");

  switch (accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      DEBUG_PRINT  ("3200 ");
      break;
    case ADXL345_DATARATE_1600_HZ:
      DEBUG_PRINT  ("1600 ");
      break;
    case ADXL345_DATARATE_800_HZ:
      DEBUG_PRINT  ("800 ");
      break;
    case ADXL345_DATARATE_400_HZ:
      DEBUG_PRINT  ("400 ");
      break;
    case ADXL345_DATARATE_200_HZ:
      DEBUG_PRINT  ("200 ");
      break;
    case ADXL345_DATARATE_100_HZ:
      DEBUG_PRINT  ("100 ");
      break;
    case ADXL345_DATARATE_50_HZ:
      DEBUG_PRINT  ("50 ");
      break;
    case ADXL345_DATARATE_25_HZ:
      DEBUG_PRINT  ("25 ");
      break;
    case ADXL345_DATARATE_12_5_HZ:
      DEBUG_PRINT  ("12.5 ");
      break;
    case ADXL345_DATARATE_6_25HZ:
      DEBUG_PRINT  ("6.25 ");
      break;
    case ADXL345_DATARATE_3_13_HZ:
      DEBUG_PRINT  ("3.13 ");
      break;
    case ADXL345_DATARATE_1_56_HZ:
      DEBUG_PRINT  ("1.56 ");
      break;
    case ADXL345_DATARATE_0_78_HZ:
      DEBUG_PRINT  ("0.78 ");
      break;
    case ADXL345_DATARATE_0_39_HZ:
      DEBUG_PRINT  ("0.39 ");
      break;
    case ADXL345_DATARATE_0_20_HZ:
      DEBUG_PRINT  ("0.20 ");
      break;
    case ADXL345_DATARATE_0_10_HZ:
      DEBUG_PRINT  ("0.10 ");
      break;
    default:
      DEBUG_PRINT  ("???? ");
      break;
  }
  DEBUG_PRINTLN(" Hz");
}

/*
 * get sensor range and display it.
*/
void displayRange(void)
{
  DEBUG_PRINT  ("Range:         +/- ");

  switch (accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      DEBUG_PRINT  ("16 ");
      break;
    case ADXL345_RANGE_8_G:
      DEBUG_PRINT  ("8 ");
      break;
    case ADXL345_RANGE_4_G:
      DEBUG_PRINT  ("4 ");
      break;
    case ADXL345_RANGE_2_G:
      DEBUG_PRINT  ("2 ");
      break;
    default:
      DEBUG_PRINT  ("?? ");
      break;
  }
  DEBUG_PRINTLN(" g");
}

/*
 * start sensor and call it's functions.
*/
void adxl345_init(void) {
  /* Initialise the sensor */
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    DEBUG_PRINTLN("Ooops, no ADXL345 detected ... Check your wiring!");
  }
  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);

  /* Display some basic information on this sensor */
  displayADXLSensorDetails();

  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  DEBUG_PRINTLN("");
}

/*
 * Read the sensor X, Y, and Z acceleration
*/
void read_acceleration(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);
 
  
  /* Display the results (acceleration is measured in m/s^2) */
  DEBUG_PRINT("X: "); DEBUG_PRINT(event.acceleration.x); DEBUG_PRINT("  ");
  DEBUG_PRINT("Y: "); DEBUG_PRINT(event.acceleration.y); DEBUG_PRINT("  ");
  DEBUG_PRINT("Z: "); DEBUG_PRINT(event.acceleration.z); DEBUG_PRINT("  "); DEBUG_PRINTLN("m/s^2 ");
  #ifdef DEBUG
  delay(1000);
  #endif

  acc_x = event.acceleration.x;
  acc_y = event.acceleration.y;
  acc_z = event.acceleration.z; 
  
}
