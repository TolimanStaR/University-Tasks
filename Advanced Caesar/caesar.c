//
// Created by Даниил on 27.01.2020.
//

#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "caesar.h"


char dictionary[] = "0123456789"
                    "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ \n";


int getIndex(char symbol) {

     int index = -1;

     while (dictionary[++index] != symbol);

     return index;
}


char *encodeText(char *argv[], const char *data, int shift, int sizeofFile) {

     char *encodedData = (char *) malloc(sizeofFile * sizeof(char));
     unsigned int powerOfDictionary = strlen(dictionary);
     char symbol;
     int index;

     for (unsigned int i = 0; i < sizeofFile; ++i) {
          symbol = data[i];
          index = getIndex(symbol);

          symbol = dictionary[
                  (index + (shift % powerOfDictionary) + powerOfDictionary) % powerOfDictionary
          ];

          encodedData[i] = symbol;

     }

     return encodedData;
}


char *decodeText(char *argv[], const char *data, int shift, int sizeofFile) {
     return encodeText(argv, data, -shift, sizeofFile);
}
