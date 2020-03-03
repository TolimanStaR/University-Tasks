#include <stdio.h>
#include <stdlib.h>
#include "casino.h"
#include "structures.h"


int main(int argc, char *argv[]) {
     int players, cards;
     scanf("%d%d", &players, &cards);
     struct Deck deck;
     deck = create(cards, deck);

     int iden = 1;

     if (cards == 54) {
          LovushkaJokera();
          exit(0);
     }

     game(players, cards, deck, iden);

     return 0;
}
