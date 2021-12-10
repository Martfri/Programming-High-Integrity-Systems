#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *readCLI(void *_exitCmd) {
    bool *exitCmd = (bool *)_exitCmd;
    char line[50];
    int length = 0;

    printf("CLI thread started\n");

    while (false == *exitCmd) {
        length = 0;
        while ((line[length] = getchar()) != '\n') {
            length++;
            if (length >= 49)
                break;
        }
        line[length] = '\0';

        if ((line[0] == 'q') && (strlen(line) == 1)) {
            *exitCmd = true;
            printf("Stopped by user\n");
        }
    }
    printf("CLI thread terminating\n");
    return NULL;
}

int main() {
    pthread_t cliThread;
    bool exitCmd = false;

    printf("Starting Program\n");

    /* Start keyboard listener thread */
    if (0 != pthread_create(&cliThread, (pthread_attr_t *)NULL, readCLI, (void *)&exitCmd)) {
        printf("Error: Failed to create CLI thread, terminating program\n");
        exit(EXIT_FAILURE);
    }

    while (false == exitCmd) {
        sleep(1);
    }

    if (0 != pthread_join(cliThread, NULL)) {
        printf("Error: Failed to wait for CLI thread to terminate\n");
    }

    printf("Terminating Program\n");
    return 0;
}