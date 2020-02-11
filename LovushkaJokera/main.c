#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "casino.h"
#include "structures.h"

int main() {
     int numberOfCards;
     int numberOfPlayers;

     int *data = input();
     numberOfCards = data[0];
     numberOfPlayers = data[1];


     struct Deck deck = createDeck(numberOfCards);




     return 0;
}