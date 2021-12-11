#include "distFunc.h"

#include "stdLib.h"
#include "voters.h"

/**
 * @brief converts a value of current in a distance.
 *
 * @param currentValue: value of the current to convert in (10*mA)
 * @return uint32_t computed distance in (10*m)
 */
uint32_t computeDistance_A(int32_t currentValue) {
    // Sensor characteristic equation
    // distance = -1.25 * current + 25
    // Sensor characteristic equation with scaled current
    // distance = -1.25 * current + 250

#ifdef DEBUG
    printf("\ncurrentValue: %d\n", currentValue);
#endif

    uint32_t distance = (-1.25 * currentValue + 250);

#ifdef DEBUG
    printf("Computed distance: %d (m*10)\n\n", distance);
#endif
    return distance;
}

returnType_en computeDistance_B() {
    return 0;
}

/**
 * @brief runs the implementation A of the current to distance conversion algorithm
 *
 * @param sensorReadings: Array of sensor readings
 * @param distance: pointer to a variable to hold the converted distance value
 * @return returnType_en E_OK in case the distance value was computed sucessfuly, else E_NOT_OK
 */
returnType_en computeDistance_BlockA(sensor_t sensorReadings[], uint32_t* distance) {
    int32_t votedValue = 0;
    returnType_en retVal;

    retVal = runVoter_A(sensorReadings, &votedValue);

    if (E_OK == retVal) {
        /*TODO evaluate computed value*/
        *distance = computeDistance_A(votedValue);
        retVal = E_OK;

#ifdef DEBUG
        printf("BlockA Computed distance: %.2f m\n\n", ((float)*distance) / 10.0);
#endif

    } else {
        printf("Sensors did not provide reliable readings\n");
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
returnType_en computeDistance_BlockB(sensor_t sensorReadings[]) {
    runVoter_B(sensorReadings);
    computeDistance_B();
    return 0;
}