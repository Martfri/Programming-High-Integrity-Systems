#include "voters.h"

#include "stdLib.h"

/**
 * @brief runs the implementation A of first stage voter
 *
 * @param sensorReadings: Array of sensor readings
 * @param bestValue: pointer to a variable to hold best value from all the readings
 * @return returnType_en E_OK in case the best value was computed sucessfuly, else E_NOT_OK
 */
returnType_en runVoter_A(sensor_t sensorReadings[], int32_t *bestValue) {
    returnType_en retVal = E_NOT_OK;

    int32_t reading_s1 = sensorReadings[0].reading;
    int32_t reading_s2 = sensorReadings[1].reading;
    int32_t reading_s3 = sensorReadings[2].reading;

    int32_t diff1 = reading_s1 - reading_s2;
    int32_t diff2 = reading_s2 - reading_s3;

    if (2 > diff1 || 2 > diff2) {
        if (diff1 < diff2) {
            *bestValue = (reading_s1 + reading_s2) / (NR_OF_SENSORS - 1);
        } else if (diff2 < diff1) {
            *bestValue = (reading_s2 + reading_s3) / (NR_OF_SENSORS - 1);
        } else {
            *bestValue = (reading_s1 + reading_s2 + reading_s3) / NR_OF_SENSORS;
        }
        retVal = E_OK;
    } else {
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
returnType_en runVoter_B(sensor_t sensorReadings[]) {
    return 0;
}

/**
 * @brief
 *
 * @param
 * @return
 */
returnType_en runStage2Voter() {
    return 0;
}