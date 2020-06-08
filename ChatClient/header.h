#ifndef CHATCLIENT_HEADER_H
#define CHATCLIENT_HEADER_H

typedef struct Args {
    int socket;
} args;

void serverMessagesReceiver(void *argsSet);

#endif
