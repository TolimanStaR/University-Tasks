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


long long depthFirstSearch(char *path, int limit, long long answer) {
    struct _finddata_t file;
    intptr_t header = _findfirst(path, &file);

    if (!header) return 0;

    while (_findnext(header, &file) == 0) {

        if (file.size >= limit) {
            ++answer;
        }

        if ((file.attrib & _A_SUBDIR) && (strcmp(file.name, "..\0"))) {
            answer += depthFirstSearch(getNextPath(path, file.name), limit, 0);
        }
    }
    return answer;
}
