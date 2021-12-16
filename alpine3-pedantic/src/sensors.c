#include "sensors.h"

#include "stdLib.h"

/**
 * @brief Returns the output value from a simulated sensor.
 * Selects the right file to read according to the sensor index
 * and reads and returns the written value * 10 to avoid floating point values
 *
 * @param sensorIdx: sensor index
 * @return sensor reading in (10*m)
 */
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

    int32_t reading = (rand() % (OPERATIONAL_CURR_MAX - 196 + 1)) + 196;
    // reading = E_ERROR; in case of failure to read value return -1
    return reading;
}

/**
 * @brief Prints to the console the current readings of all the sensors
 *
 * @param sensorReadings: Array of sensor readings
 */
void printSensorReadings(sensor_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        printf("Sensor %d: %d\n", sensorIdx, sensorReadings[sensorIdx].reading);
    }
}

/**
 * @brief Loops through all the sensor and fills the array of readings with 
 * the most updated sensor readings. In case a fault sensor is detected,
 * its state is set to SENSOR_NOT_OK and the reading to 0.
 *
 * @param sensorReadings: Array of sensor readings
 * @return E_OK = 0
 */
returnType_en readSensors(sensor_t sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        uint32_t reading = getSensorReading(sensorIdx);

        if (OPERATIONAL_CURR_MIN <= reading && OPERATIONAL_CURR_MAX >= reading) {
            sensorReadings[sensorIdx].reading = reading;
            sensorReadings[sensorIdx].state = SENSOR_OK;
        } else {
            /* Fault check may be added here */
            sensorReadings[sensorIdx].reading = 0;
            sensorReadings[sensorIdx].state = SENSOR_NOT_OK;
        }
    }

#ifdef DEBUG
    printSensorReadings(sensorReadings);
#endif

    return E_OK;
}