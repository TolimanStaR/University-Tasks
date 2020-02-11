#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "structures.h"


char TypesOfFront[4][20] = {
        "Diamond",
        "Heart",
        "Club",
        "Spade",
};

char idList[13][20] = {
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
        "Ten",
        "Jack",
        "Queen",
        "King",
        "Ace",
};


int max(int a, int b) {
     return a > b ? a : b;
}


int input() {


     int data[2]; // Данные, которые потом возвращаются в main
     gets(data[0]);

//     while (1) {
//          puts("Please, enter the number of cards:");
//          scanf("%d", &*data[0]);
//          puts("Please, enter the number of players:");
//          scanf("%d", &*data[1]);
//
//          int correctValues[2] = {36, 52}; // При желании - можно добавить (Возможность расширения)
//
//          int isCorrect = 0;
//          for (int i = 0; i < 2; ++i) {
//               isCorrect = (*data[0] == correctValues[i] ? 1 : max(0, isCorrect));
//          }
//          puts("point passed");
//          if (*data[1] < 2 || *data[1] > 6) {
//               isCorrect = 0;
//          }
//          else {
//               isCorrect = 1;
//          }
//          if (isCorrect)
//               return *data;
//          else
//               continue; // Данные - некорректные. Попробуем снова получить их.
//     }
     return *data;
}


struct Deck createDeck(int numberOfCards) {
     struct Deck deck;
     deck.stack = (struct Card *) malloc(numberOfCards * sizeof(struct Card));

     for (int i = 0; i < 4; ++i) {
          for (unsigned j = (52 - numberOfCards) / 4; j < numberOfCards / 4; ++j) {
               for (int k = 0; TypesOfFront[i][k] != '\0'; ++k) {
                    deck.stack[i + i * j].front[k] = TypesOfFront[i][k];
               }
               for (int k = 0; idList[j][k] != '\0'; ++j) {
                    deck.stack[i + i * j].front[k] = idList[j][k];
               }
          }
     }

     return deck;
}


struct Deck shuffle(struct Deck deck, int numberOfCards, int gameId) {
     srand(gameId);
     int toShuffle;
     struct Card temp;
     for (int i = 0; i < 1000; ++i) {
          toShuffle = rand() % numberOfCards;
          temp = deck.stack[i % numberOfCards];
          deck.stack[i % numberOfCards] = deck.stack[toShuffle];
          deck.stack[toShuffle] = temp;
     }

     return deck;
}


void game(int numberOfPlayers, int numberOfCards, struct Deck deck) {
     int countOfCardsForEachPlayer = numberOfCards / numberOfPlayers;
     struct Player *playerList;
     playerList = (struct Player *) malloc(numberOfPlayers * sizeof(struct Player));

     for (unsigned int id = 0; id < numberOfPlayers; ++id) {
          playerList[id].playerId = id;
          playerList[id].cardSet = (struct Card *) malloc(countOfCardsForEachPlayer * sizeof(struct Card));
     }

     for (int k = 0; k < countOfCardsForEachPlayer * numberOfPlayers; ++k) {
          playerList[k % numberOfPlayers].cardSet[k / numberOfPlayers] = deck.stack[k];
     }

     for (unsigned int id = 0; id < numberOfPlayers; ++id) {

          printf("У игрока под номером %d есть карты:\n", id + 1);

          for (unsigned int card = 0; card < countOfCardsForEachPlayer; ++card) {
               printf("%s - %s\n", playerList[id].cardSet[card].front, playerList[id].cardSet[card].id);
          }
     }
}
