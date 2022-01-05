/* Linter error description: https://www.kessler.de/prd/gimpel/pclint-meldungen.htm */
#include <arpa/inet.h>

#include "cli.h"
#include "distFunc.h"

//Warning 537: Repeated include file 'sensors.h - Since stdLib has include guards, this is not a problem
#include "sensors.h"  //lint !e537

//Warning 537: Repeated include file 'stdLib.h - Since stdLib has include guards, this is not a problem
#include "stdLib.h"  //lint !e537
#include "voters.h"

#define PORT 8080
#define IP "127.0.0.1"

int main() {
    returnType_en retVal;
    pthread_t cliThread;
    sensor_t sensorReadings[NR_OF_SENSORS];  // holds the value of the sensor readings * 10
    bool enterSafeState = true, distanceIsSafe_A = false, distanceIsSafe_B = false, rcvdExitCmd = false;
    int socket_desc;
    struct sockaddr_in server_addr;
    int32_t flowControl = 0;

#ifdef DEBUG
    (void)printf("Starting Program\n");

#endif

    // Create UDP socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0) {
        (void)printf("ERROR: Failed to create socket\n");
        return -1;
    }

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    // Bind to the set port and IP:
    /* sockaddr is a generic descriptor for any kind of socket operation, 
    whereas sockaddr_in is a struct specific to IP-based communication.  */
    if (bind(socket_desc, (struct sockaddr *)&server_addr, (unsigned int)sizeof(server_addr)) < 0) {  //lint !e740
        (void)printf("ERROR: Couldn't bind to the port\n");
        return -1;
    }

    /* Start keyboard listener thread */
    if (0 != pthread_create(&cliThread, (pthread_attr_t *)NULL, readCLI, (void *)&rcvdExitCmd)) {
        (void)printf("ERROR: Failed to create CLI thread, terminating program\n");
        exit(EXIT_FAILURE);
    }

    /* Main Loop */
    /*  Boolean argument to equal/not equal  -- A Boolean was used as an
      argument to == or !=.  For example:

              if( (a > b) == (c > d) ) ...

      tests to see if the inequalities are of the same value.  This
      could be an error as it is an unusual use of a Boolean (see
      Warnings 503 and 514) but it may also be deliberate since this is
      the only way to efficiently achieve equivalence or exclusive or.
      Because of this possible use, the construct is given a relatively
      mild 'informational' classification.  If the Boolean argument is
      cast to some type, this message is not given.
    */
    while (false == rcvdExitCmd) {  //lint !e731
        flowControl = 0;
        retVal = readSensors(socket_desc, sensorReadings);

        /* It is advised not to perform bitwise operations on enums because it is not possible to define if an enum is a signed or unsigned integer.
        In this case the enum is a signed integer, however this case is used to check if all the function returned E_OK which translates to 0b000.
        The actual signedness of the variable is not relevant */

        retVal |= evaluateDistance_BlockA(sensorReadings, &distanceIsSafe_A);  //lint !e655

        retVal |= evaluateDistance_BlockB(sensorReadings, &distanceIsSafe_B, &flowControl);  //lint !e655

        retVal |= runStage2Voter(distanceIsSafe_A, distanceIsSafe_B, &enterSafeState);  //lint !e655
#ifdef DEBUG
        (void)printf("flowControl count is:%i\n", flowControl);
#endif

        if (E_OK != retVal || flowControl != 1) {
            enterSafeState = true;
        }

        /* Display System Decision */
        // attention: use void in front of the
        (void)printf("Go To Safe State: %s\n\n", enterSafeState ? "TRUE" : "FALSE");
        (void)sleep(1);  // TODO check if it is needed
    }

    /* Wait For CLI thread to terminate */
    if (0 != pthread_join(cliThread, NULL)) {
        (void)printf("ERROR: Failed to wait for CLI thread to terminate\n");
    }

    // Close the socket:
    if (0 != close(socket_desc)) {
        (void)printf("ERROR: Failed to close socket\n");
    }

    (void)printf("Terminating program\n");
    return 0;
}
