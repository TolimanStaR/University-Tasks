#ifndef TREEMASTER_HEADER_H
#define TREEMASTER_HEADER_H

typedef struct Node {
    char data[512];
    struct Node *brother;
    struct Node *child;
} Node;

void depthFirstSearch(char* path, char* target);

char *getNextPath(char *path, char *dirName);

void writeDirectoryFullName(char *path);

#endif
