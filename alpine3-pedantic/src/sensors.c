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

void *sensorMsgStub(void *_rcvdExitCmd) {
    bool *rcvdExitCmd = (bool *)_rcvdExitCmd;
    int socket_desc;
    struct sockaddr_in server_addr;
    uint8_t client_message[3];
    int server_struct_length = sizeof(server_addr);
    memset(client_message, '\0', sizeof(client_message));
    printf("Running Sender Thread\n");

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0) {
        printf("ERROR: Failed to create socket\n");
    } else {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = inet_addr(IP);

        while (false == *rcvdExitCmd) {
            int8_t reading[3];

            for (int i = 0; i < 3; i++) {
                reading[i] = (rand() % (OPERATIONAL_CURR_MAX - 196 + 1)) + 196;
            }

            memcpy(client_message, reading, sizeof(reading));

            // Send the message to server:
            if (sendto(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr *)&server_addr, server_struct_length) < 0) {
                printf("ERROR: Unable to send sensor values\n");
            }
        }
    }

    // Close the socket:
    close(socket_desc);
    printf("Terminating Sender Thread\n");

    return NULL;
}