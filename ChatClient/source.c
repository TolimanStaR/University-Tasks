#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "header.h"


void *serverMessagesReceiver(void *argsSet) {
    Args *args = (Args *) argsSet;

    char serverReplyMessage[MESSAGE_LENGTH] = {0};
    int serverReplySize;

    while (1) {
        if ((serverReplySize = recv(args->socket, serverReplyMessage, MESSAGE_LENGTH, 0)) < 0) {
            puts("Recv failed!\n");
            break;
        }
        puts(serverReplyMessage);
        memset(serverReplyMessage, 0, MESSAGE_LENGTH);
    }

    return 0;
}

void *serverMessagesSender(void *argsSet) {
    Args *args = (Args *) argsSet;

    char serverSendMessage[MESSAGE_LENGTH] = {0};

    while (1) {
        fgets(serverSendMessage, MESSAGE_LENGTH, stdin);

        if (strlen(serverSendMessage) < 2) {
            puts("Too few symbols");
            continue;
        }

        if (send(args->socket, serverSendMessage, strlen(serverSendMessage), 0) < 0) {
            puts("Send failed");
            break;
        }
    }

}

int pthreadError(int code) {
    perror("connect failed. Error");
    return code;
}
