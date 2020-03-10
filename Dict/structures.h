#ifndef DICT_STRUCTURES_H
#define DICT_STRUCTURES_H


typedef union value {
    long long integer;
    double real_number;
    char string[100];
} Value;

typedef struct Element {
    char key[30];
    char type;
    Value value;
} Element;

typedef struct Dict {
    Element *dictionary;
    long long realSize;
    long long actualSize;
    long long maxSize;
    char name[100];
} Dict;

#endif
