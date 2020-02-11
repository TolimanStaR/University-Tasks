#ifndef LOVUSHKAJOKERA_CASINO_H
#define LOVUSHKAJOKERA_CASINO_H

int *input();

int max(int a, int b);

struct Deck createDeck(int numberOfCards);

void handOutDeck(struct Deck deck, int numberOfPlayers);

struct Deck shuffle(struct Deck deck, int numberOfCards, int gameId);

void game(int numberOfPlayers, int numberOfCards, struct Deck deck);

// int lovushkaJokera();

#endif
