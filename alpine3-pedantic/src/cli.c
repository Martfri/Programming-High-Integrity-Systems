#include "cli.h"

#include "stdLib.h"

/**
 * @brief reads from the console
 *
 * @param _rcvdExitCmd pointer to a variable that signals the program must terminate
 */
void *readCLI(void *_rcvdExitCmd) {
    bool *rcvdExitCmd = (bool *)_rcvdExitCmd;
    char line[50];
    int length = 0;

    while (false == *rcvdExitCmd) {
        length = 0;
        while ((line[length] = (char)getchar()) != '\n') {
            length++;
            if (length >= 49)
                break;
        }
        line[length] = '\0';

        if ((line[0] == 'q') && (strlen(line) == 1)) {
            *rcvdExitCmd = true;
            (void)printf("Stopped by user\n");
        }
    }

#ifdef DEBUG
    (void)printf("CLI thread terminating\n");
#endif

    return NULL;
}
