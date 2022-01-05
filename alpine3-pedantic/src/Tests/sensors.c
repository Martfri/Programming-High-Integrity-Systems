#include "sensors.h"

#include <arpa/inet.h>
#include <sys/socket.h>

#include "stdLib.h"

#define PORT 8080
#define IP "127.0.0.1"

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
returnType_en readSensors(int sockfd, sensor_t sensorReadings[]) {
    uint8_t sensorMsg[3];
    struct sockaddr_in client_addr;
    int client_struct_length = sizeof(client_addr);
    memset(sensorMsg, '\0', sizeof(sensorMsg));

    if (recvfrom(sockfd, sensorMsg, sizeof(sensorMsg), 0, (struct sockaddr *)&client_addr, (void *)&client_struct_length) < 0) {
        printf("ERROR: Failed to receive reading\n");
        return E_NOT_OK;
    }

    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        uint8_t reading = sensorMsg[sensorIdx];

        if (OPERATIONAL_CURR_MIN <= reading && OPERATIONAL_CURR_MAX >= reading) {
            sensorReadings[sensorIdx].reading = reading;
            sensorReadings[sensorIdx].state = SENSOR_OK;
        } else {
            /* Sensor Fault check may be added here */
            sensorReadings[sensorIdx].reading = 0;
            sensorReadings[sensorIdx].state = SENSOR_NOT_OK;
        }
    }

#ifdef DEBUG
    printSensorReadings(sensorReadings);
#endif

    return E_OK;
}