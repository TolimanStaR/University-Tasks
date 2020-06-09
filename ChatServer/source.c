#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


#include "data.h"

int userAuthorisation(int socket) {

    char clientMessage[MESSAGE_LENGTH] = {0};
    char serverMessage[MESSAGE_LENGTH] = {0};
    int read_size;

    strcpy(serverMessage, "What's up, Anonymous user! \n"
                          "Please register to use Polygram social network! \n"
                          "To login, enter /login \n"
                          "To register, enter /reg");

    write(socket, serverMessage, strlen(serverMessage));

    if ((read_size = recv(socket, clientMessage, MESSAGE_LENGTH, 0)) < 1)
        return -1;

    clientMessage[read_size - 1] = '\0';

    if (!strcmp(userCommand[0], clientMessage)) {

        int existFlag = 0;

        char userName[100] = {0};
        char password[100] = {0};

        EnterUserName:

        strcpy(serverMessage, "Enter your username (3 - 30 ascii characters) >>> ");
        write(socket, serverMessage, strlen(serverMessage));
        read_size = recv(socket, userName, 31, 0);
        userName[read_size - 1] = '\0';

        if (read_size < 4) {
            strcpy(serverMessage, "Nickname is too short. Try again >>> ");
            write(socket, serverMessage, strlen(serverMessage));
            goto EnterUserName;
        }

        for (unsigned int userIndex = 0; userIndex < usersCount; ++userIndex) {
            if (strcpy(userName, usersList[userIndex].username))
                existFlag = 1;
        }

        if (existFlag) {
            strcpy(serverMessage, "That nickname exist. Try another.");
            write(socket, serverMessage, strlen(serverMessage));
            goto EnterUserName;
        }

        EnterPassword:

        strcpy(serverMessage, "Enter your password (3 - 30 ascii characters) >>> ");
        write(socket, serverMessage, strlen(serverMessage));
        read_size = recv(socket, password, 31, 0);
        password[read_size - 1] = '\0';

        if (read_size < 4) {
            strcpy(serverMessage, "Password is too short. Try again >>> ");
            write(socket, serverMessage, strlen(serverMessage));
            goto EnterPassword;
        }

        User newUser;
        strcpy(newUser.username, userName);
        strcpy(newUser.password, password);
        newUser.userID = usersCount;
        usersList[usersCount] = newUser;
        usersCount++;

        strcpy(serverMessage, "Successful registration!");
        write(socket, serverMessage, strlen(serverMessage));

        return 0;
    }

    if (!strcmp(userCommand[1], clientMessage)) {
        char username[31] = {0};
        char password[31] = {0};
        int read_size;

        strcpy(serverMessage, "Enter your username >>> ");
        write(socket, serverMessage, strlen(serverMessage));
        read_size = recv(socket, username, 31, 0);
        username[read_size - 1] = '\0';
    }

    return 0;
}


void *connection_handler(void *socket_desc) {
    int sock = *(int *) socket_desc;
    int read_size, authorisationCode;
    char client_message[MESSAGE_LENGTH];

    authorisationCode = userAuthorisation(sock);

    if (authorisationCode != 0)
        return (void *) -1;


    while ((read_size = recv(sock, client_message, MESSAGE_LENGTH, 0)) > 0) {

        // write(sock, client_message, read_size);
        printf("client message is (%d sym) >>> %s", read_size, client_message);


        for (int i = 0; i < MESSAGE_LENGTH; ++i)
            client_message[i] = '\0';
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    ConnectionEnd:
    // Free the socket pointer
    free(socket_desc);

    return 0;
}
