#include <stdlib.h>

struct Deck create(int cards, struct Deck deck);

struct Deck shuffle(int cards, struct Deck deck, int iden);

void game(int players, int cards, struct Deck deck, int iden);

void LovushkaJokera();
