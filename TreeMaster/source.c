#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <stdio.h>


char *getNextPath(char *path, char *dirName) {
    char *newPath = (char *) calloc(512, sizeof(char));
    strcpy(newPath, path);
    newPath[strlen(newPath) - 1] = '\0';
    strcat(newPath, dirName);
    strcat(newPath, "\\*");
    return newPath;
}


void writeDirectoryFullName(char *path) {
    char *newPath = (char *) calloc(512, sizeof(char));
    strcpy(newPath, path);
    newPath[strlen(newPath) - 1] = '\n';
    FILE *output = fopen("output_for_dir.txt", "a");
    fprintf(output, "%s", newPath);
}


void depthFirstSearch(char *path, char *target) {
    struct _finddata_t file;
    intptr_t header = _findfirst(path, &file);

    if (!header) return;

    while (_findnext(header, &file) == 0) {
        char *temp = (char *) file.name;
        if (!strcmp(temp, target)) {
            writeDirectoryFullName(path);
        }

        if ((file.attrib & _A_SUBDIR) && (strcmp(file.name, "..\0"))) {
            depthFirstSearch(getNextPath(path, file.name), target);
        }
    }
}
