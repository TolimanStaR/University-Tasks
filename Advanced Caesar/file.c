//
// Created by Даниил on 27.01.2020.
//

#include <stdio.h>
#include <stdlib.h>

#include "file.h"


int getSize(char *argv[]) {

     int sizeofFile = 0;
     FILE *input = fopen(argv[2], "rb");

     if (input != NULL) {

          fseek(input, 0, SEEK_END);
          sizeofFile = ftell(input);
          fseek(input, 0, SEEK_SET);

     }

     fclose(input);

     return sizeofFile;
}


char *readData(char *argv[]) {

     int sizeofFile = getSize(argv);
     char *data = (char *) malloc(sizeofFile * sizeof(char));

     FILE *input = fopen(argv[2], "r");
     int symbol;
     int flag = 0;

     while ((symbol = fgetc(input)) != EOF) {
          data[flag++] = (char) symbol;
     }

     fclose(input);
     return data;
}


void writeData(char *argv[], char data[], int sizeofFile) {

     FILE *output = fopen(argv[3], "w");

     int flag = 0;

     for(;flag < sizeofFile - 1; fputc(data[flag++], output));

     fclose(output);
}

