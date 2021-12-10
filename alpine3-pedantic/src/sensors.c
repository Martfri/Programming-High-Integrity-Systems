#include "sensors.h"

#include "stdLib.h"

int32_t getSensorReading(uint8_t sensorIdx) {
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
    // float reading_f = (rand() % (20 - 18 + 1)) + 18;
    // int32_t reading = (int32_t)(reading_f * 10.0);

    int32_t reading = (rand() % (200 - 198 + 1)) + 198;
    // reading = E_ERROR; in case of failure to read value return -1
    return reading;
}

void printSensorReadings(sensor_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        printf("Sensor %d: %d\n", sensorIdx, sensorReadings[sensorIdx].reading);
    }
}

int8_t readSensors(sensor_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        sensorReadings[sensorIdx].reading = getSensorReading(sensorIdx);
    }

    printSensorReadings(sensorReadings);

    return 0;
}