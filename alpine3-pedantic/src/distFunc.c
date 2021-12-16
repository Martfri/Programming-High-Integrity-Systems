#include "distFunc.h"

#include "stdLib.h"
#include "voters.h"

/**
 * @brief converts a value of current in a distance.
 *
 * @param currentValue: value of the current to convert in (10*mA)
 * @return uint8_t computed distance in (10*m)
 */
uint8_t computeDistance_A(uint8_t currentValue) {
#ifdef DEBUG
    printf("Voted Current A: %d (10*mA)\n", currentValue);
#endif

    /* 10cm precision loss. Ex: 0.38m is truncated to 0.30m*/
    uint8_t distance = SENSOR_SCALED_TRANSFER_FUNC(currentValue);

#ifdef DEBUG
    // printf("Computed distance A: %d (10*m)\n", distance);
#endif
    return distance;
}

returnType_en computeDistance_B() {
    return 0;
}

/**
 * @brief Compares the distance with the safe distance.
 *
 * @param distance: value of the distance in (10*m)
 * @return true if 
 */
bool isDistanceSafe(uint8_t distance) {
    bool safe = false;

    if (distance < MIN_SAFE_DISTANCE) {
        safe = false;
    } else {
        safe = true;
    }

    return safe;
}

/**
 * @brief runs the implementation A of the current to distance conversion algorithm
 *
 * @param sensorReadings: Array of sensor readings
 * @param distance: pointer to a variable to hold the converted distance value
 * @return returnType_en E_OK in case the distance value was computed sucessfuly, else E_NOT_OK
 */
returnType_en evaluateDistance_BlockA(sensor_t sensorReadings[], bool* distanceIsSafe_A) {
    uint8_t votedValue = 0;
    uint8_t distance = 0;
    returnType_en retVal;

    retVal = runVoter_A(sensorReadings, &votedValue);

    if (E_OK == retVal) {
        /*TODO evaluate computed value*/
        distance = computeDistance_A(votedValue);
        *distanceIsSafe_A = isDistanceSafe(distance);

        retVal = E_OK;

#ifdef DEBUG
        printf("BlockA Computed distance: %.2f m\n", ((float)distance) / 10.0);
        printf("Distance is Safe A: %s\n\n", *distanceIsSafe_A ? "TRUE" : "FALSE");
#endif

    } else {
        printf("Sensors did not provide reliable readings\n\n");
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
returnType_en evaluateDistance_BlockB(sensor_t sensorReadings[]) {
    runVoter_B(sensorReadings);
    computeDistance_B();
    return 0;
}