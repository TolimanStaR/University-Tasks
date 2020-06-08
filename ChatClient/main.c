#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "header.h"


int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    int user_msg_len;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("185.255.132.221");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected to server\n");

    pthread_t receiving_thread;


    while (1) {
        printf("Enter message : ");
        gets(message);

        //Send some data
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if ((user_msg_len = recv(sock, server_reply, 2000, 0)) < 0) {
            puts("recv failed");
            break;
        }
//        int re_len;
//        while ((re_len = recv(sock, server_reply, 2000, 0)) > 0) {
//            puts(server_reply);
//            printf(" (symbols: %d)\n", re_len);
//            puts("\n");
//        }

        server_reply[user_msg_len] = '\0';
        puts("Server reply : ");
        puts(server_reply);
    }

    pclose((int *) &sock);
    return 0;
}
