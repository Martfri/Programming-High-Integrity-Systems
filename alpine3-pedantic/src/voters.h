/**
 * @file voters.h
 * @brief Implementation of the voting algorithms.
 *
 * @note
 */
#ifndef VOTERS_H
#define VOTERS_H

#define noValue 200

//Warning 537: Repeated include file 'sensors.h - Since stdLib has include guards, this is not a problem
#include "sensors.h"  //lint !e537

/**
 * @brief runs the implementation A of first stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param bestValue: pointer to a variable to hold best value from all the readings
 * @return returnType_en E_OK in case the best value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_A(sensor_t const sensorReadings[], uint8_t* bestValue, int32_t *ptr_flowControl);

/**
 * @brief runs the implementation of second stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param votedValue_B: pointer to a variable that holds the voted value
 * @return returnType_en E_OK in case the voted value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_B(sensor_t const sensorReadings[], int32_t* votedValue_B, int32_t* ptr_flowControl);

/**
 * @brief
 *
 * @param distanceIsSafe_A boolean with Voter A decision
 * @param distanceIsSafe_B boolean with Voter B decision
 * @param enterSafeState result of the stage 2 voter
 * @return E_OK in case of success, otherwise E_NOT_OK
 */
returnType_en runStage2Voter(bool distanceIsSafe_A, bool distanceIsSafe_B, bool* enterSafeState, int32_t *ptr_flowControl);
#endif
