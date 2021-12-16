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
 * @param distanceIsSafe_A: pointer to a variable to signal if there is a threat nearby
 * @return returnType_en E_OK in case the distance value was computed sucessfuly, else E_NOT_OK
 */
returnType_en evaluateDistance_BlockA(sensor_t sensorReadings[], bool* distanceIsSafe_A);

/**
 * @brief
 *
 * @param sensorReadings: Array of sensor readings
 * @param distanceIsSafe_B: Pointer to a variable to signal if there is a threat nearby
 * @return returnType_en E_OK in case the distance value was computed sucessfully, ele E_NOT_OK
 */
returnType_en evaluateDistance_BlockB(sensor_t sensorReadings[], bool* distanceIsSafe_B);

#endif