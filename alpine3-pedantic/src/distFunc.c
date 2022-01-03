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
    (void) printf("Voted Current A: %d (10*mA)\n", currentValue);
#endif

    /* 10cm precision loss. Ex: 0.38m is truncated to 0.30m*/
    uint8_t distance = SENSOR_SCALED_TRANSFER_FUNC(currentValue);

#ifdef DEBUG
    // printf("Computed distance A: %d (10*m)\n", distance);
#endif
    return distance;
}

float computeDistance_B(float votedValue_B) {
    // attention rmoe: use constants, macros
    float yOffset = SensChar_Offset;             // 25m

    float gradient = SensChar_MaxDist / SensChar_DelCurrent;  // 20m/16mA

    float distance_B = yOffset - ((float)(votedValue_B)*gradient);  //Transferfunction of sensor

    return distance_B;
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
 * @brief Checks the retval value and returns the state value
 *
 * @param retVal: enumerator of return Value
 * @return true if retVal ist E_NOT_OK or E_ERROR
 */
bool isDistanceSafe_B(returnType_en retVal) {
    bool safe = false;

    if (retVal != E_NOT_OK && retVal != E_ERROR) {
        safe = true;
    } else {
        safe = false;
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
        (void) printf("BlockA Computed distance: %.2f m\n", ((float)distance) / 10.0);
        (void) printf("Distance is Safe A: %s\n\n", *distanceIsSafe_A ? "TRUE" : "FALSE");
#endif

    } else {
        (void) printf("Sensors did not provide reliable readings\n\n");
        retVal = E_NOT_OK;
    }

    return retVal;
}

/**
 * @brief runs the implementation B of the current to distance conversion algorithm
 *
 * @param sensorReadings: Array of sensor readings
 * @param distance: pointer to a variable to hold the converted distance value
 * @return returnType_en E_OK in case the distance value was computed sucessfuly, else E_NOT_OK
 */

returnType_en evaluateDistance_BlockB(sensor_t sensorReadings[], bool* distanceIsSafe_B, int32_t *ptr_flowControl) {
    int32_t votedValue_B = 0;
    float distance_B = 0;
    returnType_en retVal;

    retVal = runVoter_B(sensorReadings, &votedValue_B, ptr_flowControl);

#ifdef DEBUG
    (void) printf("B_Voted Current is: %i (10*mA)\n", votedValue_B);
#endif

    distance_B = computeDistance_B(votedValue_B);

#ifdef DEBUG
    (void) printf("BlockB Computed distance: %.2f m\n", (float)(distance_B / 10));
#endif

    *distanceIsSafe_B = isDistanceSafe_B(retVal);

#ifdef DEBUG
    (void) printf("Distance is Safe: %s\n\n", *distanceIsSafe_B ? "TRUE" : "FALSE");
#endif

    return retVal;
}
