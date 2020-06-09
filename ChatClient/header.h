#ifndef CHATCLIENT_HEADER_H
#define CHATCLIENT_HEADER_H

#define MESSAGE_LENGTH 500

enum retCode {
    OK,
    ERROR,
};

typedef struct Args {
    int socket;
} Args;

void *serverMessagesReceiver(void *argsSet);

void *serverMessagesSender(void *argsSet);

int pthreadError(int code);

#endif
