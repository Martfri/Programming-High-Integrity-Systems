/**
 * @file voters.h
 * @brief Implementation of the voting algorithms.
 *
 * @note 
 */
#ifndef VOTERS_H
#define VOTERS_H
#include <stdint.h>

#include "sensors.h"

/**
 * @brief runs the implementation A of first stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param bestValue: pointer to a variable to hold best value from all the readings
 * @return returnType_en E_OK in case the best value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_A(sensor_t sensorReadings[], int32_t* bestValue);

/**
 * @brief runs the implementation of second stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param votedValue_B: pointer to a variable that holds the voted value 
 * @return returnType_en E_OK in case the voted value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_B(sensor_t sensorReadings[], int32_t *votedValue_B);

/**
 * @brief
 *
 * @param
 * @return
 */
returnType_en runStage2Voter(bool distanceIsSafe_A, bool distanceIsSafe_B, bool* enterSafeState);
#endif