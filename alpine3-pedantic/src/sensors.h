/**
 * @file sensors.h
 * @brief Implementation of simulated sensor driver.
 *
 * @note 
 */
#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

#include "stdLib.h"

#define NR_OF_SENSORS 3
#define OPERATIONAL_CURR_MIN 4 * 10   // in 10*mA
#define OPERATIONAL_CURR_MAX 20 * 10  // in 10*mA
#define SENSOR_ACCURACY 0.2 * 10      // in 10*mA

#define SENSOR_TRANSFER_FUNC(current) (-1.25 * current + 25)          // in mA to meters
#define SENSOR_SCALED_TRANSFER_FUNC(current) (-1.25 * current + 250)  // in 10*mA to 10*m

#define MIN_SAFE_DISTANCE 2 * 10  // in 10*m

/**
 * @brief Sensor state enumeration
 */
typedef enum {
    SENSOR_NOT_OK = 0,
    SENSOR_OK,
} sensorState_en;

/**
 * @brief Sensor structure definition
 */
typedef struct sensor_t {
    sensorState_en state;
    uint32_t reading;
} sensor_t;

/**
 * @brief Loops through all the sensor and fills the array of readings with 
 * the most updated sensor readings
 *
 * @param sensorReadings: Array of sensor readings
 * @return E_OK = 0
 */
returnType_en readSensors(sensor_t sensorReadings[]);

#endif