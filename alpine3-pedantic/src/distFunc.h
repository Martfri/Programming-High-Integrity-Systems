/**
 * @file distFunc.h
 * @brief Implementation of the current to distance convertion algorithms.
 *
 * @note 
 */
#ifndef DIST_FUNC_H
#define DIST_FUNC_H

#include <stdint.h>

#include "sensors.h"

/**
 * @brief runs the implementation A of the current to distance conversion algorithm
 *
 * @param sensorReadings: Array of sensor readings
 * @param distance: pointer to a variable to hold the converted distance value
 * @return returnType_en E_OK in case the distance value was computed sucessfuly, else E_NOT_OK
 */
returnType_en computeDistance_BlockA(sensor_t sensorReadings[], uint32_t* distance);

/**
 * @brief
 *
 * @param
 * @return
 */
returnType_en computeDistance_BlockB(sensor_t sensorReadings[]);

#endif