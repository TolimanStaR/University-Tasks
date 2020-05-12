#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

int main() {
    char *path;
    path = (char *) calloc(512, sizeof(char));

    long long answer = 0;
    int n;

    puts("Enter the current path -> ");
    gets(path);

    puts("Enter the size of file in bytes ->");
    scanf("%d", &n);


    strcat(path, "\\*");

    depthFirstSearch(path, n, answer);

    printf("%s - %lld", path, answer);

    return 0;
}

#pragma clang diagnostic pop
