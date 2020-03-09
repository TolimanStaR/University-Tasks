#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#define and &&
#define or ||


int len(const char string[]) {
     int j = -1;
     while (string[++j]);
     return j;
}

int equal(const char string1[], const char string2[]) {
     int i = 0;
     while (string2[i] == string1[i]) {
          ++i;
     }
     return (--i >= len(string2));
}

int findDictionary(char *dictList[], char name[], int countOfDicts) {
     int flag = 0;
     for (int i = 0; i < countOfDicts; ++i) {
          if (equal(name, dictList[i])) {
               flag = 1;
          }
     }
     return flag;
}

int getIndex(char *dictList[], char name[], int countOfDicts) {
     int index = 0;
     for (int i = 0; i < countOfDicts; ++i) {
          if (equal(name, dictList[i])) {
               index = i;
               break;
          }
     }
     return index;
}

Dict *createDict(Dict *dictSet, char name[], char *dictList[], int countOfDicts) {

     for (int i = 0; i < len(name); ++i) {
          dictList[countOfDicts - 1][i] = name[i];
          dictSet[countOfDicts - 1].name[i] = name[i];
     }

     dictSet[countOfDicts - 1].actualSize = 10;
     dictSet[countOfDicts - 1].maxSize = 100000;
     dictSet[countOfDicts - 1].dictionary = (Element *) calloc(dictSet->actualSize, sizeof(Element));

     return dictSet;
}

void showDirectory(char *dictList[], int countOfDicts) {
     puts("\n(console) >>> Existing dictionaries:");
     for (int i = 0; i < countOfDicts; ++i) {
          printf("(console) >>> %d: %s\n", i + 1, dictList[i]);
     }
}

void FinishSession() {
     puts("(console) >>> saving objects and exiting session...\n");
     exit(0);
}

Dict *shell(Dict *dictSet, int index) {
     printf("(console: %s) >>> ", dictSet[index].name);

     char *command = (char *) calloc(100, sizeof(char));
     int cnt = 0;
     while (command[cnt++] != ' ')

          return dictSet;
}

void session() {
     puts(">>> Session has started.\n");

     int numberOfDictionaries = 0;

     // Хранение всех словарей.

     Dict *dictSet;
     char **dictList;
     dictSet = (Dict *) calloc(10, sizeof(Dict));
     dictList = (char **) calloc(10, sizeof(char *));
     for (int i = 0; i < 10; ++i) dictList[i] = (char *) calloc(100, sizeof(char));
     char *command = (char *) calloc(100, sizeof(char));

     continueSession:
     {
          puts("(console) >>> ");
          // Получение команды от пользователя, находящегося в сессии.
          free(command);
          char *command = (char *) calloc(100, sizeof(char));
          gets(command);

          // Получение оператора действия.

          int cnt = -1;
          while (command[++cnt] != ' ');
          char *operator = (char *) calloc(cnt + 1, sizeof(char));
          for (int i = 0; i < cnt; ++i) operator[i] = command[i];

          if (equal(operator, "create")) {
               ++numberOfDictionaries;

               // Получение имени нового словаря.

               char *nameOfNewDict;
               while (command[++cnt] != '\0');
               nameOfNewDict = (char *) calloc(cnt - len(operator) + 1, sizeof(char));
               for (int i = 7; command[i] != '\0'; ++i) nameOfNewDict[i - 7] = command[i];

               // Создание словаря для дальнейшего использования.

               dictSet = createDict(dictSet, nameOfNewDict, dictList, numberOfDictionaries);
               goto continueSession;
          }

          if (equal(operator, "directory")) {
               showDirectory(dictList, numberOfDictionaries);
               goto continueSession;
          }

          if (equal(operator, "exit()")) {
               FinishSession();
          }

          if (equal(operator, "shell")) {

               // Получение имени словаря, с которым пользователь хочет взаимодействовать

               char *nameOfDict;
               while (command[++cnt] != '\0');
               nameOfDict = (char *) calloc(cnt - len(operator) + 1, sizeof(char));
               for (int i = 6; command[i] != '\0'; ++i) nameOfDict[i - 6] = command[i];

               // Если словарь существует, запускается интерактивное взаимодействие с этим словарем.

               if (findDictionary(dictList, nameOfDict, numberOfDictionaries)) {
                    int index = getIndex(dictList, nameOfDict, numberOfDictionaries);
                    shell(dictSet, index);
               } else {
                    puts("(console) >>> Dictionary not found.");
               }

               goto continueSession;
          }


          // test
          printf("%d\n", equal(operator, "print"));

          printf("%s", operator);
          exit(0);
     }
}
