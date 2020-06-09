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

    AuthenticationStart:

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
            if (!strcmp(userName, usersList[userIndex].username))
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
        newUser.socket = socket;

        usersList[usersCount] = newUser;
        usersCount++;

        strcpy(serverMessage, "Successful registration!");
        write(socket, serverMessage, strlen(serverMessage));

        return newUser.userID;
    } else if (!strcmp(userCommand[1], clientMessage)) {
        char username[31] = {0};
        char password[31] = {0};

        EnterUserNameLogin:

        strcpy(serverMessage, "Enter your username >>> ");
        write(socket, serverMessage, strlen(serverMessage));
        read_size = recv(socket, username, 31, 0);
        username[read_size - 1] = '\0';

        for (unsigned int userIndex = 0; userIndex < usersCount; ++userIndex) {
            if (!strcmp(username, usersList[userIndex].username)) {

                EnterPasswordLogin:

                strcpy(serverMessage, "Enter your password >>> ");
                write(socket, serverMessage, strlen(serverMessage));
                read_size = recv(socket, password, 31, 0);
                password[read_size - 1] = '\0';
                if (strcmp(password, usersList[userIndex].password) != 0) {
                    strcpy(serverMessage, "Passwords didn't match. ");
                    write(socket, serverMessage, strlen(serverMessage));
                    goto EnterPasswordLogin;
                } else {
                    strcpy(serverMessage, "You logged in!");
                    write(socket, serverMessage, strlen(serverMessage));
                    usersList[userIndex].status = Online;

                    return usersList[userIndex].userID;
                }
            }
        }

        strcpy(serverMessage, "This username doesn't exist.");
        write(socket, serverMessage, strlen(serverMessage));
        goto EnterUserNameLogin;
    } else goto AuthenticationStart;
}


void *connection_handler(void *socket_desc) {
    int sock = *(int *) socket_desc;
    int read_size, userID;

    char clientMessage[MESSAGE_LENGTH] = {0};
    char clientMessageCopy[MESSAGE_LENGTH] = {0};
    char serverMessage[MESSAGE_LENGTH + 100] = {0};
    char comma[100];

    userID = userAuthorisation(sock);

    if (userID == -1) {
        write(sock, "Something went wrong. Disconnect...", 50);
        return (void *) -1;
    }

    strcpy(serverMessage, "Now you are online \n"
                          "You can check users list -> /list \n"
                          "You can call any online user to chat with him -> /request <username> \n"
                          "If some one asks you for chat. You can /accept or /decline it");
    write(sock, serverMessage, strlen(serverMessage));


    while ((read_size = recv(sock, clientMessage, MESSAGE_LENGTH, 0)) > 0) {    // MAIN CYCLE
        printf("client message is (%d sym) >>> %s", read_size, clientMessage);

        strcpy(clientMessageCopy, clientMessage);

        if (usersList[userID].status == Online) { // catch commands
            clientMessage[read_size - 1] = '\0';
            char command[50];
            char friend[31];

            if (!strcmp(clientMessage, userCommand[2])) { //list of users
                for (unsigned int userIndex = 0; userIndex < usersCount; ++userIndex) {
                    char status[20];
                    strcpy(serverMessage, usersList[userIndex].username);
                    strcat(serverMessage, " - ");

                    switch (usersList[userIndex].status) {
                        case 0:
                            strcpy(status, "Online\n");
                            break;
                        case 1:
                            strcpy(status, "Busy\n");
                            break;
                        case 2:
                            strcpy(status, "Offline\n");
                            break;
                    }

                    strcat(serverMessage, status);
                    write(sock, serverMessage, strlen(serverMessage));
                }
                continue;
            }

            strcpy(command, strtok(clientMessage, " "));

            if (!strcmp(command, userCommand[3])) {
                strcpy(friend, strtok(NULL, " "));
                for (int userIndex = 0; userIndex < usersCount; ++userIndex) {
                    if (!strcmp(usersList[userIndex].username, friend)) {
                        if (strcmp(friend, usersList[userID].username) != 0) {

                            // TODO: add a message about status of requested user

                            strcpy(serverMessage, "You have requested user ");
                            strcat(serverMessage, friend);
                            strcat(serverMessage, " to chat");

                            write(sock, serverMessage, strlen(serverMessage));

                            strcpy(serverMessage, "User ");
                            strcat(serverMessage, usersList[userID].username);
                            strcat(serverMessage, " requests you to chat. Write /accept ");
                            strcat(serverMessage, usersList[userID].username);
                            strcat(serverMessage, " to accept or /decline ");
                            strcat(serverMessage, usersList[userID].username);
                            strcat(serverMessage, " to decline");

                            write(usersList[userIndex].socket, serverMessage, strlen(serverMessage));

                            break;
                        }
                    }
                }
            } else if (!strcmp(command, userCommand[4])) { // accept chat

                Chat newChat;
                strcpy(friend, strtok(NULL, " "));

                for (int userIndex = 0; userIndex < usersCount; ++userIndex) {
                    if (!strcmp(friend, usersList[userIndex].username)) {
                        newChat.firstUser = usersList[userID];
                        newChat.secondUser = usersList[userIndex];
                        newChat.chatID = chatsCount++;
                        newChat.firstSocket = usersList[userID].socket;
                        newChat.secondSocket = usersList[userIndex].socket;
                        usersList[userID].currentChatID = newChat.chatID;
                        usersList[userIndex].currentChatID = newChat.chatID;
                        usersList[userID].status = Busy;
                        usersList[userIndex].status = Busy;
                        chatsList[newChat.chatID] = newChat;

                        strcpy(serverMessage, "Now you are chatting with ");
                        strcat(serverMessage, newChat.secondUser.username);
                        strcat(serverMessage, "\nLeave chat with /leave");

                        write(newChat.firstSocket, serverMessage, strlen(serverMessage));

                        strcpy(serverMessage, "Now you are chatting with ");
                        strcat(serverMessage, newChat.firstUser.username);
                        strcat(serverMessage, "\nLeave chat with /leave chat");

                        write(newChat.secondSocket, serverMessage, strlen(serverMessage));

                        break;
                    }
                }
                continue;

            } else if (!strcmp(command, userCommand[5])) { // decline chat
                for (int userIndex = 0; userIndex < usersCount; ++userIndex) {
                    if (!strcmp(friend, usersList[userIndex].username)) {
                        strcpy(serverMessage, "User ");
                        strcat(serverMessage, usersList[userID].username);
                        strcat(serverMessage, " declined your request.");
                        write(usersList[userIndex].socket, serverMessage, strlen(serverMessage));
                        break;
                    }
                }
            }
        } else if (usersList[userID].status == Busy) { // user chats with somebody
            char command[30];
            strcpy(command, strtok(clientMessage, " "));

            if (!strcmp(command, userCommand[6])) { // leave chat
                Chat currentChat = chatsList[usersList[userID].currentChatID];
                usersList[currentChat.firstUser.userID].status = Online;
                usersList[currentChat.secondUser.userID].status = Online;
                usersList[currentChat.firstUser.userID].currentChatID = None;
                usersList[currentChat.secondUser.userID].currentChatID = None;
            } else { // it is message
                puts("chat");
                Chat currentChat = chatsList[usersList[userID].currentChatID];
                User Me = usersList[userID];
                User Friend;
                if (Me.socket == currentChat.firstSocket)  // friend - second
                    Friend = currentChat.secondUser;
                else
                    Friend = currentChat.firstUser;

                strcpy(serverMessage, Me.username);
                strcat(serverMessage, " : ");
                strcat(serverMessage, clientMessageCopy);

                write(Friend.socket, serverMessage, strlen(serverMessage));
            }
        }

        for (int i = 0; i < MESSAGE_LENGTH; ++i)
            clientMessage[i] = '\0';
    }

    if (read_size == 0) {
        puts("Client disconnected");
        usersList[userID].status = Offline;
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    ConnectionEnd:
    free(socket_desc);

    return 0;
}
