#include "cli.h"
#include "distFunc.h"
#include "sensors.h"
#include "stdLib.h"
#include "voters.h"

int main() {
    // returnType_en retVal;
    pthread_t cliThread;
    bool rcvdExitCmd = false;
    int32_t sensorReadings[NR_OF_SENSORS];

    printf("Starting Program\n");

    /* Start keyboard listener thread */
    if (0 != pthread_create(&cliThread, (pthread_attr_t *)NULL, readCLI, (void *)&rcvdExitCmd)) {
        printf("Error: Failed to create CLI thread, terminating program\n");
        exit(EXIT_FAILURE);
    }

    /* Main Loop */
    while (false == rcvdExitCmd) {
        readSensors(sensorReadings);

        computeDistance_BlockA(sensorReadings);

        computeDistance_BlockB(sensorReadings);

        runStage2Voter();

        /* Display System Decision */
        sleep(1);
    }

    /* Wait For CLI thread to terminate */
    if (0 != pthread_join(cliThread, NULL)) {
        printf("Error: Failed to wait for CLI thread to terminate\n");
    }

    printf("Terminating program\n");
    return 0;
}