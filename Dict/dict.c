#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#define and &&
#define or ||


int len(const char string[]) {

     // Подсчет длины строки.

     int j = -1;
     while (string[++j]);
     return j;
}

int equal(const char string1[], const char string2[]) {

     // Сравнение строк.

     int i = 0;
     while (string2[i] == string1[i]) {
          ++i;
     }
     return (--i >= len(string2));
}

int findDictionary(char *dictList[], char name[], int countOfDicts) {

     // Проверка на наличие словаря по названию.

     int flag = 0;
     for (int i = 0; i < countOfDicts; ++i) {
          if (equal(name, dictList[i])) {
               flag = 1;
          }
     }
     return flag;
}

int getIndex(char *dictList[], char name[], int countOfDicts) {

     // Поиск "местоположения" словаря.

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

     // Создание словаря.

     for (int i = 0; i < len(name); ++i) {
          dictList[countOfDicts - 1][i] = name[i];
          dictSet[countOfDicts - 1].name[i] = name[i];
     }

     dictSet[countOfDicts - 1].actualSize = 10;
     dictSet[countOfDicts - 1].maxSize = 100000;
     dictSet[countOfDicts - 1].dictionary = (Element *) calloc(dictSet->actualSize, sizeof(Element));
     dictSet[countOfDicts - 1].realSize = 0;

     return dictSet;
}

void showDirectory(Dict *dictSet, int countOfDicts) {

     // Распечатка существующих словарей.

     puts("(console) >>> Existing dictionaries:");
     for (int i = 0; i < countOfDicts; ++i) {
          printf("(console) >>> %d : %s\n", i + 1, dictSet[i].name);
     }
}

void showDict(Dict *dictSet, int index) {

     // Вывод определенного словаря полностью.

     if (dictSet[index].realSize > 0) {

          for (long long i = 0; i < dictSet[index].realSize; ++i) {
               if (!equal(dictSet[index].dictionary[i].key, "@deleted")) {
                    printf("%s : ", dictSet[index].dictionary[i].key);
                    switch (dictSet[index].dictionary[i].type) {
                         case 'i':
                              printf("%lld\n", dictSet[index].dictionary[i].value.integer);
                              break;
                         case 'd':
                              printf("%f\n", dictSet[index].dictionary[i].value.real_number);
                              break;
                         case 's':
                              printf("%s\n", dictSet[index].dictionary[i].value.string);
                              break;
                         default:
                              printf("<undefined>\n");
                              break;
                    }
               }
          }
     } else
          printf("(console: %s) >>> Dict is empty.\n", dictSet[index].name);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

Dict *append(Dict *dictSet, int index, const char key[], char typeOfValue, const char command[]) {

     // Добавление элемента в словарь.

     // Проверка на наличие ключа:

     for (long long i = 0; i < dictSet[index].realSize; ++i) {
          if (equal(key, dictSet[index].dictionary[i].key)) {
               printf("(console: %s) >>> Key already exist! Please choose other key.\n", dictSet[index].name);
               return dictSet;
          }
     }

     // *****

     // Добавление элемента. Если необходимо, выделяется память.

     if (dictSet[index].realSize + 1 < dictSet[index].actualSize) {
          memoryHasAllocated:
          {
               dictSet[index].realSize += 1;

               char pointer[] = "@deleted\0";

               for (int i = 0; i < len(key); ++i)
                    dictSet[index].dictionary[dictSet[index].realSize - 1].key[i] = key[i];

               dictSet[index].dictionary[dictSet[index].realSize - 1].type = typeOfValue;

               int lengthOfValue = 0;
               int iterator = 0;
               char *value;
               for (int i = len(command) - 1; command[i] != ' '; --i) lengthOfValue++;
               value = (char *) calloc(lengthOfValue + 1, sizeof(char));
               for (int i = len(command) - 1 - lengthOfValue; i < len(command); ++i)
                    value[iterator++] = command[i];
               switch (typeOfValue) {
                    case 'i':
                         dictSet[index].dictionary[dictSet[index].realSize - 1].value.integer = atoi(value);
                         break;
                    case 'd':
                         dictSet[index].dictionary[dictSet[index].realSize - 1].value.real_number = strtod(value, NULL);
                         break;
                    case 's':
                         for (int i = 0; i < len(value); ++i)
                              dictSet[index].dictionary[dictSet[index].realSize - 1].value.string[i] = value[i];
                         break;
                    default:
                         printf("(console: %s) >>> Invalid value\n", dictSet[index].name);
                         for (int i = 0; i < len(pointer) + 1; ++i)
                              dictSet[index].dictionary[dictSet[index].realSize - 1].key[i] = pointer[i];
                         break;
               }
          };
     } else {
          if (dictSet[index].actualSize * 2 < dictSet[index].maxSize) {
               dictSet = realloc(dictSet, dictSet[index].realSize * 2);
               dictSet[index].actualSize = dictSet[index].realSize * 2;
               goto memoryHasAllocated;
          } else
               printf("(console: %s) >>> Not enough memory!\n", dictSet[index].name);
     }

     // *****

     return dictSet;
}

Dict *removeElement(Dict *dictSet, int index, const char key[]) {

     // "Удаление" элемента. Формально его больше никак не получить.

     char pointer[] = "@deleted\0";

     for (long long i = 0; i < dictSet[index].realSize; ++i) {
          if (equal(dictSet[index].dictionary[i].key, key)) {
               for (int j = 0; j < len(pointer); ++j) dictSet[index].dictionary[i].key[j] = pointer[j];
          }
     }

     return dictSet;
}

#pragma clang diagnostic pop

void FinishSession() {
     puts("(console) >>> saving objects and exiting session...\n");
     exit(0);
}

Dict *shell(Dict *dictSet, int index) {

     // Интерактивное взаимодейсвие со словарем.

     char *command = (char *) calloc(100, sizeof(char));

     continueShell:
     {
          printf("(console: %s) >>>", dictSet[index].name);

          free(command);
          char *command = (char *) calloc(100, sizeof(char));
          gets(command);

          int cnt = 0;
          while (command[cnt] != ' ' and command[cnt++] != '\0');
          char *operator = (char *) calloc(cnt + 1, sizeof(char));
          for (int i = 0; i < cnt; ++i) operator[i] = command[i];

          if (equal(operator, "print")) {
               showDict(dictSet, index);
               goto continueShell;
          }

          if (equal(operator, "append")) {
               ++cnt;
               int keyLength = 0;
               char type;
               while (command[cnt + keyLength] != ' ') ++keyLength;
               char *key = (char *) calloc(keyLength + 1, sizeof(char));
               for (int i = cnt; i < cnt + keyLength; ++i) key[i - cnt] = command[i];
               type = command[cnt + keyLength + 1];
               dictSet = append(dictSet, index, key, type, command);

               goto continueShell;
          }

          if (equal(operator, "remove")) {
               char *key;
               int keyLength = 0;
               ++cnt;
               for (; command[cnt + keyLength++] != '\0';);
               key = (char *) calloc(keyLength + 1, sizeof(char));
               for (int i = cnt; i < len(command); ++i) key[i - cnt] = command[i];
               removeElement(dictSet, index, key);

               goto continueShell;
          }

          if (equal(operator, "exit()") or equal(operator, "quit()")) {
               printf("(console: %s) >>> Back to main session...\n", dictSet[index].name);
               return dictSet;
          }
     };

     return dictSet;
}

void session() {

     // Интерактивное взаимодействие со всей "библиотекой".

     puts(">>> Session has started.\n");

     int numberOfDictionaries = 0;

     // Хранение всех словарей.

     Dict *dictSet;
     char **dictList;
     dictSet = (Dict *) calloc(25, sizeof(Dict));
     dictList = (char **) calloc(10, sizeof(char *));
     for (int i = 0; i < 10; ++i) dictList[i] = (char *) calloc(100, sizeof(char));
     char *command = (char *) calloc(100, sizeof(char));

     continueSession:
     {
          printf("(console) >>>");
          // Получение команды от пользователя, находящегося в сессии.
          free(command);
          char *command = (char *) calloc(100, sizeof(char));
          gets(command);

          // Получение оператора действия.

          int cnt = 0;
          while (command[cnt] != ' ') ++cnt;
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

          if (equal(operator, "directory") or equal(operator, "dir")) {
               showDirectory(dictSet, numberOfDictionaries);
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
                    dictSet = shell(dictSet, index);
               } else {
                    printf("(console) >>> Dictionary not found.\n");
               }

               goto continueSession;
          }

          exit(0);
     }
}
