#include <arpa/inet.h>
#include <sys/socket.h>

#include "sensors.h"
#include "stdLib.h"

#define PORT 8080
#define IP "127.0.0.1"

/* compile with gcc -o txProgram txStub.c*/
int main_1() {
    // int main() {
    // int socket_desc;
    // struct sockaddr_in server_addr;
    // uint8_t client_message[3];
    // int server_struct_length = sizeof(server_addr);
    // memset(client_message, '\0', sizeof(client_message));
    // printf("Running Sender Thread\n");

    // // Create socket:
    // socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // if (socket_desc < 0) {
    //     printf("ERROR: Failed to create socket\n");
    // } else {
    //     server_addr.sin_family = AF_INET;
    //     server_addr.sin_port = htons(PORT);
    //     server_addr.sin_addr.s_addr = inet_addr(IP);

    //     while (1) {
    //         int8_t reading[3];

    //         for (int i = 0; i < 3; i++) {
    //             reading[i] = (rand() % (OPERATIONAL_CURR_MAX - 196 + 1)) + 196;
    //         }

    //         memcpy(client_message, reading, sizeof(reading));

    //         // Send the message to server:
    //         if (sendto(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr *)&server_addr, server_struct_length) < 0) {
    //             printf("ERROR: Unable to send sensor values\n");
    //         }
    //     }
    // }

    // // Close the socket:
    // close(socket_desc);
    // printf("Terminating Sender Thread\n");
    return 0;
}