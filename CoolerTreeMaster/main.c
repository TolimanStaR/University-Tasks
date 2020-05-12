#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"


int main() {
    char *path;
    path = (char *) calloc(512, sizeof(char));

    long long answer = 0;

    puts("Enter the current path -> ");
    gets(path);


    strcat(path, "\\*");

    answer = depthFirstSearch(path, answer);

    path[strlen(path) - 1] = '\0';

    printf("%s - %lld", path, answer);

    return 0;
}
