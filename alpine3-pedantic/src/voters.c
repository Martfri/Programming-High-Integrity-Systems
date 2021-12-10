#include "voters.h"

#include "stdLib.h"

int8_t runVoter_A(sensor_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        int32_t reading = sensorReadings[sensorIdx].reading;
        if (20 >= reading || 200 < reading) {
            /* error handling for sensor error*/
        }
    }

    // int32_t reading_s1 = sensorReadings[0].reading;
    // int32_t reading_s2 = sensorReadings[1].reading;
    // int32_t reading_s3 = sensorReadings[2].reading;

    return 0;
}

int8_t runVoter_B(sensor_t sensorReadings[]) {
    return 0;
}

int8_t runStage2Voter() {
    return 0;
}