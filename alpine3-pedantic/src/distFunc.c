#include "distFunc.h"

#include "stdLib.h"
#include "voters.h"

uint32_t computeDistance_A(int32_t currentValue) {
    // Sensor characteristic equation
    // distance = -1.25 * current + 25
    // Sensor characteristic equation with scaled current
    // distance = -1.25 * current + 250

    // printf("\ncurrentValue: %d\n", currentValue);
    uint32_t distance = (-1.25 * currentValue + 250);
    // printf("Computed distance: %d (m*10)\n\n", distance);
    return distance;
}

returnType_en computeDistance_B() {
    return 0;
}

returnType_en computeDistance_BlockA(sensor_t sensorReadings[], uint32_t* distance) {
    int32_t votedValue = 0;
    returnType_en retVal;
    retVal = runVoter_A(sensorReadings, &votedValue);
    if (E_OK == retVal) {
        /*TODO evaluate computed value*/
        *distance = computeDistance_A(votedValue);
        retVal = E_OK;
    } else {
        printf("Sensors did not provide reliable readings\n");
        retVal = E_NOT_OK;
    }

    return retVal;
}

returnType_en computeDistance_BlockB(sensor_t sensorReadings[]) {
    runVoter_B(sensorReadings);
    computeDistance_B();
    return 0;
}