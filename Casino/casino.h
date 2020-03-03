#ifndef CASINO_CASINO_H
#define CASINO_CASINO_H

#include "structures.h"

Deck createDeck(Deck deck);

Deck shuffleDeck(Deck deck);

void exceptionKiller(int numberOfPlayers, int typeOfGame);

/*
 exceptionKiller - Проверка входных данных на корректность
*/

void caseInTheCasino(int numberOfPlayers, int typeOfGame);

void visualiseData(Table *casino, int UsedTables);

#endif
