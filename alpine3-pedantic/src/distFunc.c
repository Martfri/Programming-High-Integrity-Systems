#include "distFunc.h"

//Warning 537: Repeated include file 'stdLib.h - Since stdLib has include guards, this is not a problem
#include "stdLib.h"  //lint !e537

//Warning 537: Repeated include file 'voters.h - Since stdLib has include guards, this is not a problem
#include "voters.h"  //lint !e537

/**
 * @brief converts a value of current in a distance.
 *
 * @param currentValue: value of the current to convert in (10*mA)
 * @return uint8_t computed distance in (10*m)
 */
static uint8_t computeDistance_A(uint8_t currentValue) {

    /* 10cm precision loss. Ex: 0.38m is truncated to 0.30m*/
    uint8_t distance = (uint8_t)SENSOR_SCALED_TRANSFER_FUNC(currentValue);

#ifdef DEBUG
    // printf("Computed distance A: %d (10*m)\n", distance);
#endif
    return distance;
}

static float computeDistance_B(int32_t votedValue_B) {
    // attention rmoe: use constants, macros
    float yOffset = SensChar_Offset;  // 25m

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
static bool isDistanceSafe(uint8_t distance) {
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
 * @param distance_B: float of distance value
 * @return true if retVal ist E_NOT_OK or E_ERROR
 */
static bool isDistanceSafe_B(float distance_B) {
    bool safe = false;

    if (MAX_UNSAFE_DISTANCE < distance_B  &&  MAX_OPERATIONAL_DISTANCE > distance_B  ) {
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
returnType_en evaluateDistance_BlockA(sensor_t const sensorReadings[], bool* distanceIsSafe_A, int32_t* ptr_flowControl) {
    uint8_t votedValue = 0;
    uint8_t distance = 0;
    returnType_en retVal;

    retVal = runVoter_A(sensorReadings, &votedValue, ptr_flowControl);

    if (E_OK == retVal) {
        /*TODO evaluate computed value*/
        distance = computeDistance_A(votedValue);
        *distanceIsSafe_A = isDistanceSafe(distance);

        retVal = E_OK;

#ifdef DEBUG
        (void)printf("Voted Current A: %i (10*mA)\n", votedValue);
        (void)printf("Computed Distance A: %.2f m\n", ((float)distance) / SENSOR_SCALER);
        (void)printf("Distance is Safe A: %s\n\n", *distanceIsSafe_A ? "TRUE" : "FALSE");
#endif

    } else {
        (void)printf("Sensors did not provide reliable readings\n\n");
        retVal = E_NOT_OK;
    }

    *ptr_flowControl = *ptr_flowControl + 1;
    return retVal;
}

/**
 * @brief runs the implementation B of the current to distance conversion algorithm
 *
 * @param sensorReadings: Array of sensor readings
 * @param distance: pointer to a variable to hold the converted distance value
 * @return returnType_en E_OK in case the distance value was computed sucessfuly, else E_NOT_OK
 */

returnType_en evaluateDistance_BlockB(sensor_t const sensorReadings[], bool* distanceIsSafe_B, int32_t* ptr_flowControl) {
    int32_t votedValue_B = 0;
    returnType_en retVal;

    retVal = runVoter_B(sensorReadings, &votedValue_B, ptr_flowControl);

    float distance_B = computeDistance_B(votedValue_B);

    *distanceIsSafe_B = isDistanceSafe_B(distance_B);

#ifdef DEBUG
    (void)printf("Voted Current B: %i (10*mA)\n", votedValue_B);
    (void)printf("Block Computed Distance B: %.2f m\n", (float)(distance_B / SENSOR_SCALER));
    (void)printf("Distance is Safe B: %s\n\n", *distanceIsSafe_B ? "TRUE" : "FALSE");
#endif

    *ptr_flowControl = *ptr_flowControl + 1;

    return retVal;
}
