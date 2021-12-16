#include "voters.h"

#include "stdLib.h"

/**
 * @brief checks if all sensors are operational
 *
 * @param sensorReadings: Array of sensor readings
 * @return bool true if all the sensors are operational, else false
 */
bool allSensorsOperational(sensor_t sensorReadings[]) {
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

/**
 * @brief runs the implementation A of first stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param bestValue: pointer to a variable to hold best value from all the readings
 * @return returnType_en E_OK in case the best value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_A(sensor_t sensorReadings[], int32_t* bestValue) {
    returnType_en retVal = E_NOT_OK;

    if (true == allSensorsOperational(sensorReadings)) {
        uint32_t diff1 = abs(sensorReadings[0].reading - sensorReadings[1].reading);
        uint32_t diff2 = abs(sensorReadings[1].reading - sensorReadings[2].reading);

        if (SENSOR_ACCURACY >= diff1 || SENSOR_ACCURACY >= diff2) {
            if (diff1 < diff2) {
#ifdef DEBUG
                /*  S1--S2-----S3 */
                printf("Case 1\n");
#endif
                *bestValue = (sensorReadings[0].reading + sensorReadings[1].reading) / (NR_OF_SENSORS - 1);
            } else if (diff2 < diff1) {
#ifdef DEBUG
                /*  S1-----S2--S3 */
                printf("Case 2\n");
#endif
                *bestValue = (sensorReadings[1].reading + sensorReadings[2].reading) / (NR_OF_SENSORS - 1);
            } else {
#ifdef DEBUG
                /*  S1--S2--S3 */
                printf("Case 3\n");
#endif
                *bestValue = (sensorReadings[0].reading + sensorReadings[1].reading + sensorReadings[2].reading) / NR_OF_SENSORS;
            }
            retVal = E_OK;
        } else {
            printf("Sensor threshold is greater than allowed.\n");
            /* If any diff is more than 2 means one of the sensors is faulty*/
            retVal = E_NOT_OK;
        }
    } else {
        printf("Not all the sensors are operational.\n");
        retVal = E_NOT_OK;
    }

    return retVal;
}

/**
 * @brief
 *
 * @param
 * @return
 */
returnType_en runVoter_B(sensor_t sensorReadings[], int32_t* votedValue_B) {
    returnType_en retVal = E_NOT_OK;
   // bool opCondition = allSensorsOperational(sensorReadings);

//attention rmoe: replace it by cheking the state. This thing is done in sensors.c
    for(int sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++)
    {
        if(sensorReadings[sensorIdx].reading < OPERATIONAL_CURR_MIN) //checks, if there is a sensor with current value below Operational_CURR_MIN
        {
            sensorIdx = NR_OF_SENSORS;
            retVal = E_ERROR;

            printf("A sensor value is < OPERATIONAL_CURR_MIN.\n");
        }
        else
        {
            ;
        }
    }

    if(sensorReadings[0].reading > OPERATIONAL_CURR_MAX || sensorReadings[1].reading > OPERATIONAL_CURR_MAX || sensorReadings[2].reading > OPERATIONAL_CURR_MAX)
    {
        retVal = E_ERROR;
        printf("A sensor value is > OPERATIONAL_CURR_MAX.\n");
    }
    else 
    {   //attention rmoe: 
        if(abs(sensorReadings[2].reading - sensorReadings[1].reading) <= SENSOR_ACCURACY &&
           abs(sensorReadings[2].reading - sensorReadings[0].reading) <= SENSOR_ACCURACY &&
           abs(sensorReadings[1].reading - sensorReadings[0].reading) <= SENSOR_ACCURACY
        )
        {
#ifdef DEBUG
            {
             printf("Sensor values in range and tolerance.\n");
            }      
#endif
            *votedValue_B = (sensorReadings[0].reading + sensorReadings[1].reading + sensorReadings[2].reading) / NR_OF_SENSORS;
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
            printf("Sensor values are not within SENSOR_ACCURACY.\n");
        }
    }

    return retVal;
}

/**
 * @brief
 *
 * @param
 * @return
 */
returnType_en runStage2Voter(bool distanceIsSafe_A, bool distanceIsSafe_B, bool* enterSafeState) {
    *enterSafeState = !distanceIsSafe_A;
    return E_OK;
}