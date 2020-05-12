#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"


int main() {

    char *path;
    path = (char *) calloc(512, sizeof(char));
    char *target;
    target = (char *) calloc(64, sizeof(char));

    puts("Enter the current path -> ");
    gets(path);

    puts("Enter the name of target file -> ");
    gets(target);

    strcat(path, "\\*");

    depthFirstSearch(path, target);

    return 0;
}
