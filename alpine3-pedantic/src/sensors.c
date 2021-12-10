#include "sensors.h"

#include "stdLib.h"

int8_t getSensorReading(uint8_t sensorIdx) {
    switch (sensorIdx) {
        case 0:
            /* select right file */
            break;
        case 1:
            /* select right file */
            break;
        case 2:
            /* select right file */
            break;
        default:
            printf("Error: Invalid Sensor Index\n");
            break;
    }

    /* open file */

    /* read value */

    /* close file */
    int32_t reading = 20;
    // reading = E_ERROR; in case of failure to read value return -1
    return reading;
}

void printSensorReadings(int32_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        printf("Sensor %d: %d\n", sensorIdx, sensorReadings[sensorIdx]);
    }
}

int8_t readSensors(int32_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        sensorReadings[sensorIdx] = getSensorReading(sensorIdx);
    }

    printSensorReadings(sensorReadings);

    return 0;
}