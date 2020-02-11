struct Card {
    char front[20];
    char id[20];
};


struct Deck {
    int numberOfCards;
    struct Card *stack;
};

struct Player {
    unsigned int playerId;
    struct Card *cardSet;
};