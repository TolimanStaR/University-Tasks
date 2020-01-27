//
// Created by Даниил on 27.01.2020.
//

#ifndef CAESAR_CAESAR_H
#define CAESAR_CAESAR_H

char *encodeText(char *argv[], const char *data, int shift, int sizeofFile);

char *decodeText(char *argv[], const char *data, int shift, int sizeofFile);

int getIndex(char symbol);

#endif //CAESAR_CAESAR_H
