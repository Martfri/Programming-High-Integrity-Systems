#include "distFunc.h"

#include "stdLib.h"
#include "voters.h"

int8_t computeDistance_A() {
    return 0;
}

int8_t computeDistance_B() {
    return 0;
}

int8_t computeDistance_BlockA(sensor_t sensorReadings[]) {
    runVoter_A(sensorReadings);
    computeDistance_A();
    return 0;
}

int8_t computeDistance_BlockB(sensor_t sensorReadings[]) {
    runVoter_B(sensorReadings);
    computeDistance_B();
    return 0;
}