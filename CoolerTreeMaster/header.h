#ifndef COOLERTREEMASTER_HEADER_H
#define COOLERTREEMASTER_HEADER_H

typedef struct Node {
    char data[512];
    struct Node *brother;
    struct Node *child;
} Node;

long long depthFirstSearch(char *path, long long answer);

char *getNextPath(char *path, char *dirName);

#endif
