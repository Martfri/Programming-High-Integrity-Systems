#include "cli.h"
#include "distFunc.h"
#include "sensors.h"
#include "stdLib.h"
#include "voters.h"

int main() {
    returnType_en retVal;
    pthread_t cliThread;
    sensor_t sensorReadings[NR_OF_SENSORS];  // holds the value of the sensor readings * 10
    bool enterSafeState = true, distanceIsSafe_A = false, distanceIsSafe_B = false, rcvdExitCmd = false;

#ifdef DEBUG
    printf("Starting Program\n");
#endif

    /* Start keyboard listener thread */
    if (0 != pthread_create(&cliThread, (pthread_attr_t *)NULL, readCLI, (void *)&rcvdExitCmd)) {
        printf("Error: Failed to create CLI thread, terminating program\n");
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
        printf("\nGo To Safe State: %s\n", enterSafeState ? "TRUE" : "FALSE");
        sleep(1);
    }

    /* Wait For CLI thread to terminate */
    if (0 != pthread_join(cliThread, NULL)) {
        printf("Error: Failed to wait for CLI thread to terminate\n");
    }

    printf("Terminating program\n");
    return 0;
}