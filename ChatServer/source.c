#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include <time.h>
#include <unistd.h>


#include "data.h"


void *connection_handler(void *socket_desc) {
    //Get the socket descriptor
    int sock = *(int *) socket_desc;
    int read_size;
    char *message, client_message[2000];

    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock, message, strlen(message));

    message = "Now type something and i shall repeat what you type \n";
    write(sock, message, strlen(message));

    //Receive a message from client
    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        //Send the message back to client
        write(sock, client_message, read_size);
        puts(client_message);
        printf("%d\n", read_size);
        printf("client socket number is >>> %d\n", sock);

        sleep(3);

        write(sock, "Surprise, Motherfucker!\n", 30);
        write(sock, "$", 0); // interrupt?

        for (int i = 0; i < 2000; ++i)
            client_message[i] = '\0';
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}

