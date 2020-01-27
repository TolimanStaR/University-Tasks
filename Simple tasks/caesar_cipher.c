#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define fo(i, n) for (int i = 0; i < n; ++i)
#define ll long long


char get_symbol(char sym, char operation, int shift) {

     char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz "; 
     unsigned int index = 0;

     for (unsigned int i = 0; i < strlen(alphabet); ++i) {                               
          if (sym == alphabet[i]) {
               index = i;
               break;
          }
     }

     switch (operation){                                                                   
          case '0':                                                                      
               return alphabet[(index + strlen(alphabet) -  shift % strlen(alphabet)) % strlen(alphabet)];
               break;
          case '1':
               return alphabet[(index + shift) % strlen(alphabet)];
               break;
          default:
               return 0;
     }
}


void solve(char *argv[]) {

     long shift = (int) argv[4];
     int symbol;

     FILE *input;
     FILE *output;
     input = fopen(argv[2], "r");
     output = fopen(argv[3], "w");

     while ((symbol = fgetc(input)) != EOF) {

          char sym_to_write = get_symbol((char) symbol, (char)argv[1][0], (int)(argv[4][0] - '0'));

          fputc((sym_to_write - '0' != 0 ? sym_to_write : '\n'), output);
     }
}


int main(int argc, char *argv[]) {

     if (argc != 5) {
          puts("Wrong number of command line args");
     } else {
          solve(argv);
     }

     return 0;
}
