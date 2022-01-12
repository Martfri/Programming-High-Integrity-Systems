#include "voters.h"

//Warning 537: Repeated include file 'stdLib.h - Since stdLib has include guards, this is not a problem
#include "stdLib.h"  //lint !e537

/**
 * @brief checks if all sensors are operational
 *
 * @param sensorReadings: Array of sensor readings
 * @return bool true if all the sensors are operational, else false
 */
static bool allSensorsOperational(sensor_t const sensorReadings[]) {
    bool allOperational = false;
    uint8_t nrOfOperationalSensors = 0;

    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        if (SENSOR_OK == sensorReadings[sensorIdx].state) {
            nrOfOperationalSensors++;
        }
    }

    if (NR_OF_SENSORS == nrOfOperationalSensors) {
        allOperational = true;
    }

    return allOperational;
}

static uint8_t maxReading(const sensor_t sensorReadings[]) {
    uint8_t max = 0;
    for (int indx = 0; indx < NR_OF_SENSORS; indx++) {
        if (sensorReadings[indx].reading > max) {
            max = sensorReadings[indx].reading;
        }
    }
    return max;
}

/**
 * @brief runs the implementation A of first stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param bestValue: pointer to a variable to hold best value from all the readings
 * @return returnType_en E_OK in case the best value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_A(sensor_t const sensorReadings[], uint8_t* bestValue, int32_t* ptr_flowControl) {
    returnType_en retVal = E_NOT_OK;

    if (true == allSensorsOperational(sensorReadings) && maxReading(sensorReadings) <= 184) {
        uint8_t diff1 = (uint8_t)abs(sensorReadings[0].reading - sensorReadings[1].reading);
        uint8_t diff2 = (uint8_t)abs(sensorReadings[1].reading - sensorReadings[2].reading);
        uint8_t diff3 = (uint8_t)abs(sensorReadings[0].reading - sensorReadings[2].reading);

        if (SENSOR_ACCURACY >= diff1 && SENSOR_ACCURACY >= diff2 && SENSOR_ACCURACY >= diff3) {
            *bestValue = (sensorReadings[0].reading + sensorReadings[1].reading + sensorReadings[2].reading) / NR_OF_SENSORS;
            retVal = E_OK;
        } else {
#ifdef DEBUG
            (void)printf("Sensor threshold is greater than allowed.\n");
#endif
            /* If any diff is more than 2 means one of the sensors is faulty*/
            retVal = E_NOT_OK;
        }
    } else {
#ifdef DEBUG
        (void)printf("Not all the sensors are operational.\n");
#endif
        retVal = E_NOT_OK;
    }

    *ptr_flowControl = *ptr_flowControl + 1;
    return retVal;
}

/**
 * @brief runs the implementation B of first stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param bestValue: pointer to a variable to hold best value from all the readings
 * @return returnType_en E_OK in case the best value was computed sucessfuly, else E_NOT_OK
 */

returnType_en runVoter_B(sensor_t const sensorReadings[], int32_t* votedValue_B, int32_t* ptr_flowControl) {
    returnType_en retVal = E_NOT_OK;

    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        if (sensorReadings[sensorIdx].reading < OPERATIONAL_CURR_MIN)  //checks, if there is a sensor with current value below Operational_CURR_MIN
        {
            retVal = E_ERROR;
#ifdef DEBUG
            (void)printf("A sensor value is < OPERATIONAL_CURR_MIN.\n");
#endif
            break;
        } else if (sensorReadings[sensorIdx].reading > OPERATIONAL_CURR_MAX) {
            retVal = E_ERROR;
#ifdef DEBUG
            (void)printf("A sensor value is > OPERATIONAL_CURR_MAX.\n");
#endif
            break;
        }
    }

    if ((uint8_t)abs(sensorReadings[2].reading - sensorReadings[1].reading) <= SENSOR_ACCURACY &&
        (uint8_t)abs(sensorReadings[2].reading - sensorReadings[0].reading) <= SENSOR_ACCURACY &&
        (uint8_t)abs(sensorReadings[1].reading - sensorReadings[0].reading) <= SENSOR_ACCURACY) {
#ifdef DEBUG
        {
            (void)printf("Sensor values in range and tolerance.\n");
        }
#endif
        if (sensorReadings[0].reading <= OPERATIONAL_CURR_SAFE && sensorReadings[1].reading <= OPERATIONAL_CURR_SAFE && sensorReadings[2].reading <= OPERATIONAL_CURR_SAFE) {
            *votedValue_B = (sensorReadings[0].reading + sensorReadings[1].reading + sensorReadings[2].reading) / NR_OF_SENSORS;
            retVal = E_OK;
        } else {
            *votedValue_B = noValue;
            retVal = E_NOT_OK;
        }
    }

    else {
#ifdef DEBUG
        (void)printf("Sensor values are not within SENSOR_ACCURACY.\n");
#endif
        *votedValue_B = noValue;
        retVal = E_NOT_OK;
    }

    *ptr_flowControl = *ptr_flowControl + 1;
    return retVal;
}

/**
 * @brief
 *
 * @param
 * @return
 */
returnType_en runStage2Voter(bool distanceIsSafe_A, bool distanceIsSafe_B, bool* enterSafeState, int32_t* ptr_flowControl) {
    /* Warning 514: Unusual use of a Boolean expression: for boolean variables "||" must be used instead of bitwise operator "|" */
    // *enterSafeState = !distanceIsSafe_A | !distanceIsSafe_B;
    *enterSafeState = !distanceIsSafe_A || !distanceIsSafe_B;

    *ptr_flowControl = *ptr_flowControl + 1;
    return E_OK;
}
