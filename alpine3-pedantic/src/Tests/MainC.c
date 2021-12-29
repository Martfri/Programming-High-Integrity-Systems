#include <arpa/inet.h>
#include <string.h>


#include "distFunc.h"
#include "sensors.h"
#include "stdLib.h"
#include "voters.h"

int test(){
    
}

int main(int argc, char *argv[]) {
    returnType_en retVal;
    char sensorReadings[] = [float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3])];
    bool enterSafeState = true, distanceIsSafe_A = false, distanceIsSafe_B = false, rcvdExitCmd = false;
    int32_t flowControl = 0;

#ifdef DEBUG
    printf("Starting Program\n");


    /* Main Loop */
    while (false == rcvdExitCmd) {
        flowControl = 0;
        
        retVal = evaluateDistance_BlockA(sensorReadings, &distanceIsSafe_A);

        retVal |= evaluateDistance_BlockB(sensorReadings, &distanceIsSafe_B, &flowControl);

        retVal |= runStage2Voter(distanceIsSafe_A, distanceIsSafe_B, &enterSafeState);
        printf("flowControl count is:%i\n", flowControl);
        

        if (E_OK != retVal || flowControl != 1) {
            enterSafeState = true;
        }

        /* Display System Decision */
        // attention: use void in front of the 
        printf("\nGo To Safe State: %s\n\n", enterSafeState ? "TRUE" : "FALSE");
        sleep(1);
    }


    printf("Terminating program\n");
    return 0;
}