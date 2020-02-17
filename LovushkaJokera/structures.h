struct Card {
    char class[8];
    char id[6];
};

struct Deck {
    struct Card *stack;
};

