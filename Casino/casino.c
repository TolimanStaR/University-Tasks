#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>

#include "structures.h"
#include "data.h"

#define and &&
#define rep(x) for(int k = 0; k < x; ++k)


Deck createDeck(Deck deck) {

     // Покупка заряженной колоды в киоске.

     switch ((int) deck.typeOfGame) {
          case 0:
               for (unsigned int i = 0; i < deck.size; ++i)
                    deck.stack[i].id = i;
               break;
          case 1:
               for (unsigned int i = 0; i < deck.size; ++i)
                    deck.stack[i].id = i;
               break;
          case 2:
               for (unsigned int i = 16; i < 52; ++i)
                    deck.stack[i - 16].id = i;
               break;
          default:
               break;
     }

     return deck;

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"

Deck shuffleDeck(Deck deck) {

     int toShuffle;
     int shuffled;
     unsigned int temp;

     for (int i = 0; i < 1000; ++i) {
          toShuffle = rand() % (int) deck.size;
          shuffled = rand() % (int) deck.size;

          temp = deck.stack[toShuffle].id;
          deck.stack[toShuffle].id = deck.stack[shuffled].id;
          deck.stack[shuffled].id = temp;
     }

     return deck;

}

#pragma clang diagnostic pop

void exceptionKiller(int numberOfPlayers, int typeOfGame) {

     /*
     В нашем казино пока что только 54 места.
     Приносим извинения за неудобства.
     */

     if (numberOfPlayers > 1 and numberOfPlayers < 54 and typeOfGame > -1 and typeOfGame < 3)
          return;
     else {
          puts("Incorrect input data. Come in our casino later!\n");
          exit(0);
     }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"

void visualiseData(Table *casino, int usedTables) {

     // Код, на который лучше не смотреть (Выводит стол)

     _setmode(_fileno(stdout), _O_U16TEXT);
     setlocale(LC_CTYPE, "");


     for (int table = 0; table < usedTables; ++table) {


          int *playerName = (int *) calloc(casino[table].numberOfPlayers, sizeof(int));
          int players = 0;

          for (unsigned int i = 0; i < casino[table].numberOfPlayers; ++i) {
               playerName[i] = rand() % 100;
          }

          for (unsigned int k = 0; k < 20; ++k)
               wprintf(L"%lc", container[1]);
          wprintf(L"\n   Some statistics:\n   Table number %d:\n   Players here: %d\n", table + 1,
                  casino[table].numberOfPlayers);
          rep(20) wprintf(L"%lc", container[1]);
          wprintf(L"\n\n");
          rep(27) wprintf(L" ");
          rep(18) wprintf(L"%lc", container[0]);
          wprintf(L"\n");

          for (int players = 0; players < casino[table].numberOfPlayers; ++players) {

               wprintf(L"%s", casinoPlayers[playerName[players]]);
               for (int k = 0; k < 27 - wcslen(casinoPlayers[playerName[players]]); ++k)
                    wprintf(L" ");

               for (int k = 0; k < casino[table].difichento[players].cardsForPlayer; ++k) {
                    wprintf(L"%lc %s of %lc            %lc\n                           ",
                            container[0],
                            id[casino[table].difichento[players].stack[k].id % 13],
                            wClass[casino[table].difichento[players].stack[k].id / 13],
                            container[0]);

               }
               wprintf(L"%lc", container[0]);
               rep(23) wprintf(L" ");
               wprintf(L"%lc\n", container[0]);
          }
          rep(27) wprintf(L" ");
          rep(18) wprintf(L"%lc", container[0]);
          wprintf(L"\n\n");
     }
}

#pragma clang diagnostic pop

void caseInTheCasino(int numberOfPlayers, int typeOfGame) {

     long long usedMemory = 0; // В битах, разумеется

     usedMemory += 8 * 4 * 4; // int переменные;

     int cardsInTheDeck;
     int cardsForEachPlayer;
     int usedTables;

     switch (typeOfGame) {
          case 0:
               gameType = Fool;
               break;
          case 1:
               gameType = Holdem;
               break;
          case 2:
               gameType = TwentyOne;
               break;
          default:
               puts("Congratulations! You lose your money!\n");
               exit(0);
     }

     /*
     Рассчет того, сколько игроков посадить за каждый стол.
     Игроки рассаживаются жадно.
     Если игрок один за столом, то он просто сидит и размышляет о жизни.
     */

     int numberOfFreePlayers = numberOfPlayers;
     usedTables = 0;

     while (numberOfFreePlayers > 0) {
          ++usedTables;
          numberOfFreePlayers -= __min(9, numberOfFreePlayers);
     }

     int *playersForEachTable = (int *) calloc(usedTables, sizeof(int));
     usedMemory += 8 * sizeof(int) * usedTables;

     // Массив со всем состоянием заведения:

     Table *casino = (Table *) calloc(usedTables, sizeof(Table));
     usedMemory += 8 * sizeof(Table) * usedTables;

     // ********

     cardsInTheDeck = deckSizeForGame[gameType];
     cardsForEachPlayer = numberOfCardsForGame[gameType];
     numberOfFreePlayers = numberOfPlayers;

     for (int i = 0; i < usedTables; ++i) {
          playersForEachTable[i] = __min(numberOfFreePlayers, 9);
          numberOfFreePlayers -= playersForEachTable[i];
     }

     // Обработка каждого стола.

     for (int number = 0; number < usedTables; ++number) {

          /*
          Создание своей колоды для стола.
          Колода соответсвует типу игры.
          */

          Deck deck;
          deck.size = cardsInTheDeck;
          deck.typeOfGame = gameType;
          deck.stack = (Card *) calloc(cardsInTheDeck, sizeof(Card));
          usedMemory += 8 * sizeof(Card) * cardsInTheDeck;

          deck = createDeck(deck);

          /*
          "Да кто так колоду тасует?"
          "У вас дилер есть, чтобы это делать!"
          (c) Владелец казино
           */

          deck = shuffleDeck(deck);

          // Каждый стол - это набор игроков (их рук), у которых уже есть свои карты:

          casino[number].difichento = (Hand *) calloc(playersForEachTable[number], sizeof(Hand));
          casino[number].numberOfPlayers = playersForEachTable[number];
          usedMemory += 8 * sizeof(Hand) * playersForEachTable[number];

          // Раздача карт каждому игроку за столом:

          for (unsigned int i = 0; i < playersForEachTable[number]; ++i) {
               casino[number].difichento[i].cardsForPlayer = cardsForEachPlayer;
               casino[number].difichento[i].stack = (Card *) calloc(cardsForEachPlayer, sizeof(Card));
               usedMemory += 8 * sizeof(Card) * cardsForEachPlayer;
          }
          unsigned int card = 0;
          for (unsigned int i = 0; i < playersForEachTable[number]; ++i) {
               for (unsigned int k = 0; k < cardsForEachPlayer; ++k) {
                    casino[number].difichento[i].stack[k] = deck.stack[card++];
               }
          }
     }

     printf("\nMemory used in bits: %lld\n\n", usedMemory);

     visualiseData(casino, usedTables);

}
