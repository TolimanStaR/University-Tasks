#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

#define size_of_each_string 200

void solve(char *argv[]);

int max(int a, int b) {
     if (a >= b) return a;
     return b;
}

int scan(char *argv[]) {

     char word[150];
     long long answer = 0;
     char *array = (char *) malloc(size_of_each_string * sizeof(char));

     gets(word);
     unsigned int length = strlen(word);

     for (unsigned int i = 0; i < length; ++i) {

          char sym = word[i];

          if (isupper(sym)) {
               word[i] = (char) tolower(sym);
          }
     }

     FILE *input = fopen(argv[1], "r");

     while(!feof(input)) {
          if (fgets(array, size_of_each_string, input) != NULL) {

               for (unsigned int i = 0; i < max(0, (int)(strlen(array) - length)); ++i) {
                    if (tolower(array[i]) == word[0]) {
                         int counter = 0;
                         unsigned int flag = i;
                         for (unsigned int k = 0; k < length; ++k) {
                              if (tolower(array[flag]) == word[k]) {
                                   ++counter;
                              }
                              ++flag;
                         }
                         counter == (long long)length ? ++answer : answer;
                    }

               }
          }
     }
     
     fclose(input);

     printf("Answer is %lld\n", answer);

     solve(argv);
     return 0;
}

void solve(char *argv[]) {

     char todo[100];
     gets(todo);

     if (strlen(todo) == 1 && (int) (*todo - '0') > -1 && (int) (*todo - '0') < 2) {
          (int) (*todo - '0') == 1 ? scan(argv) : exit(0);
     } else {
          puts("Wrong format of input data. Try again.\n");
          solve(argv);
     }
}

int main(int argc, char *argv[]) {

     argc == 2 ? solve(argv) : puts("Wrong size of input arguments.\n");

     return 0;
}
