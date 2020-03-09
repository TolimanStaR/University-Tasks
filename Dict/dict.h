#ifndef DICT_DICT_H
#define DICT_DICT_H

#include "structures.h"


void session();

int equal(const char string1[], const char string2[]);

int len(const char string[]);

int findDictionary(char *dictList[], char name[], int countOfDicts);

int getIndex(char *dictList[], char name[], int countOfDicts);

Dict *createDict(Dict dictSet, char name[], char *dictList[], int countOfDicts);

Dict *deleteDict(char name[], char *dictList[]);

Dict *shell(Dict *dictSet, int index);

void showDirectory(char *dictList[], int countOfDicts);

void FinishSession();

#endif
