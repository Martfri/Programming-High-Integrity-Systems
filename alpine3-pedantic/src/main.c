#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#include "cli.h"
#include "distFunc.h"
#include "sensors.h"
#include "stdLib.h"
#include "voters.h"

#define PORT 8080
#define IP "127.0.0.1"

int main() {
    returnType_en retVal;
    pthread_t cliThread, txThread;
    sensor_t sensorReadings[NR_OF_SENSORS];  // holds the value of the sensor readings * 10
    bool enterSafeState = true, distanceIsSafe_A = false, distanceIsSafe_B = false, rcvdExitCmd = false;
    int socket_desc;
    struct sockaddr_in server_addr;

#ifdef DEBUG
    printf("Starting Program\n");
#endif

    // Create UDP socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0) {
        printf("ERROR: Failed to create socket\n");
        return -1;
    }

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    // Bind to the set port and IP:
    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("ERROR: Couldn't bind to the port\n");
        return -1;
    }

    /* Start keyboard listener thread */
    if (0 != pthread_create(&cliThread, (pthread_attr_t *)NULL, readCLI, (void *)&rcvdExitCmd)) {
        printf("ERROR: Failed to create CLI thread, terminating program\n");
        exit(EXIT_FAILURE);
    }

    /*Stub Sensor thread */
    if (0 != pthread_create(&txThread, (pthread_attr_t *)NULL, sensorMsgStub, (void *)&rcvdExitCmd)) {
        printf("ERROR: Failed to create CLI thread, terminating program\n");
        exit(EXIT_FAILURE);
    }

    /* Main Loop */
    while (false == rcvdExitCmd) {
        readSensors(sensorReadings);

        retVal = evaluateDistance_BlockA(sensorReadings, &distanceIsSafe_A);

        retVal |= evaluateDistance_BlockB(sensorReadings, &distanceIsSafe_B);

        retVal |= runStage2Voter(distanceIsSafe_A, distanceIsSafe_B, &enterSafeState);

        if (E_OK != retVal) {
            enterSafeState = true;
        }

        /* Display System Decision */
        printf("\nGo To Safe State: %s\n\n", enterSafeState ? "TRUE" : "FALSE");
        sleep(1);
    }

    /* Wait For CLI thread to terminate */
    if (0 != pthread_join(cliThread, NULL)) {
        printf("ERROR: Failed to wait for CLI thread to terminate\n");
    }

    /* Wait For tx thread to terminate */
    if (0 != pthread_join(txThread, NULL)) {
        printf("ERROR: Failed to wait for tx thread to terminate\n");
    }

    // Close the socket:
    close(socket_desc);

    printf("Terminating program\n");
    return 0;
}