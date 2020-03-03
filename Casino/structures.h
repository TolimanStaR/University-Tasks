#ifndef CASINO_STRUCTURES_H
#define CASINO_STRUCTURES_H

typedef struct Card {
    unsigned int id:             6;

    /*

    2 ^ 6 - Достаточно для 52 (36 либо 54 в зависимости от игры)
          уникальных карт.

    Остальные поля в структурах - аналогично;

    */

} Card;

typedef struct Deck {
    unsigned int size:           6;
    unsigned int typeOfGame:     3;
    Card *stack;
} Deck;

typedef struct Hand {
    unsigned int cardsForPlayer:          4;
    Card *stack;
} Hand;

typedef struct Table {
    unsigned int numberOfPlayers:         6;
    int TypeOfGame;
    Hand *difichento;
} Table;


#endif
