#ifndef CHATSERVER_DATA_H
#define CHATSERVER_DATA_H

#include<sys/socket.h>
#include<arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define MAX_USERS 128
#define MAX_CHATS 64
#define MAX_GROUPS 32


enum userStatus {
    Online,
    Busy,
    Offline,
};


typedef struct User {
    pthread_t thread;
    int userID;
    char username[30];
    char password[30];
    int socket;
    int status;
} User;


typedef struct Message {
    char messageText[200];
    long int sendTime;
    int ownerID;
} Message;


typedef struct Chat {
    User firstUser;
    User seconduser;
} Chat;


typedef struct Group {
    User *userList;
    User groupOwner;
} Group;


int usersCount;
User a[MAX_USERS];


#endif
