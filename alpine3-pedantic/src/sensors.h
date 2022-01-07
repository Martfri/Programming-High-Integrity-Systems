/**
 * @file sensors.h
 * @brief Implementation of simulated sensor driver.
 *
 * @note
 */
#ifndef SENSORS_H
#define SENSORS_H

#include "stdLib.h"

#define NR_OF_SENSORS 3
#define OPERATIONAL_CURR_MIN (4 * 10)   // in 10*mA
#define OPERATIONAL_CURR_MAX (20 * 10)  // in 10*mA
#define SENSOR_ACCURACY (0.2 * 10)      // in 10*mA

#define SensChar_Offset 250.0f      // Offset for calc. transferfct.
#define SensChar_MaxDist 200.0f     // Max. sensor distance
#define SensChar_DelCurrent 160.0f  // in 10*mA

// #define SENSOR_TRANSFER_FUNC(current) (-1.25 * current + 25)            // in mA to meters
#define SENSOR_SCALED_TRANSFER_FUNC(current) (-1.25 * current + 250.0)  // in 10*mA to 10*

#define MIN_SAFE_DISTANCE (2 * 10)  // in 10*m
#define MAX_UNSAFE_DISTANCE (2 * 10.0f)  

/**
 * @brief Sensor state enumeration
 */
typedef enum {
    SENSOR_NOT_OK = 0,
    SENSOR_OK
} sensorState_en;

/**
 * @brief Sensor structure definition
 */
typedef struct sensor_t {
    sensorState_en state;
    uint8_t reading;
} sensor_t;

/**
 * @brief Loops through all the sensor and fills the array of readings with
 * the most updated sensor readings
 *
 * @param sockfd: socket descriptor
 * @param sensorReadings: Array of sensor readings
 * @return E_OK = 0
 */
returnType_en readSensors(int sockfd, sensor_t sensorReadings[]);

// /**
//  * @brief Loops through all the sensor and fills the array of readings with
//  * the sensor readings. In case a fault sensor is detected,
//  * its state is set to SENSOR_NOT_OK and the reading to 0.
//  *
//  * @param sensorMsg: Array of sensor values
//  * @param sensorReadings: Array of sensor readings
//  */

//it needs to be here for the shared object to do testing. 
static void evaluateSensors(uint8_t const sensorMsg[], sensor_t sensorReadings[]);

#endif
