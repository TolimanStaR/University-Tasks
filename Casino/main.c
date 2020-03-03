#include <stdio.h>

#include "casino.h"

int main() {

     int numberOfPlayers;
     int typeOfGame;

     puts(
             "\n"
             "Please enter the number of players and type of game:\n"
             "\n"
             "  Number of players must be at least 2;\n"
             "  Type of game must be one of the next integers:\n"
             "\n"
             "    0 - Holdem;\n"
             "    1 - Fool;\n"
             "    2 - Twenty one;"
             "\n"
     );

     scanf("%d%d", &numberOfPlayers, &typeOfGame);

     exceptionKiller(numberOfPlayers, typeOfGame);

     caseInTheCasino(numberOfPlayers, typeOfGame);

     return 0;
}
