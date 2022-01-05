#include "sensors.h"

#include <arpa/inet.h>

//Warning 537: Repeated include file 'stdLib.h - Since stdLib has include guards, this is not a problem
#include "stdLib.h"  //lint !e537

#ifdef DEBUG
/**
 * @brief Prints to the console the current readings of all the sensors
 *
 * @param sensorReadings: Array of sensor readings
 */
static void printSensorReadings(sensor_t const sensorReadings[]) {
    for (uint8_t sensorIdx = 0; sensorIdx < NR_OF_SENSORS; sensorIdx++) {
        (void)printf("Sensor %d: %d\n", sensorIdx, sensorReadings[sensorIdx].reading);
    }
}
#endif

/**
 * @brief Loops through all the sensor and fills the array of readings with
 * the sensor readings. In case a fault sensor is detected,
 * its state is set to SENSOR_NOT_OK and the reading to 0.
 *
 * @param sensorMsg: Array of sensor values
 * @param sensorReadings: Array of sensor readings
 */
static void evaluateSensors(uint8_t const sensorMsg[], sensor_t sensorReadings[]) {
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

    if (sensorMsg != memset(sensorMsg, '\0', sizeof(sensorMsg))) {
        (void)printf("Memset Failed to Reset SensorMsg \n");
    }

    /* sockaddr is a generic descriptor for any kind of socket operation, 
    whereas sockaddr_in is a struct specific to IP-based communication.  */
    if (recvfrom(sockfd, sensorMsg, sizeof(sensorMsg), 0, (struct sockaddr *)&client_addr, (void *)&client_struct_length) < 0) {  //lint !e740
        (void)printf("ERROR: Failed to receive reading\n");
        return E_NOT_OK;
    } else {
#ifdef DEBUG
        (void)printf("sensor message: %d %d %d \n", sensorMsg[0], sensorMsg[1], sensorMsg[2]);
#endif
    }

    evaluateSensors(sensorMsg, sensorReadings);

#ifdef DEBUG
    printSensorReadings(sensorReadings);
#endif

    return E_OK;
}
