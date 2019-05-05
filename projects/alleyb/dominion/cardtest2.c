/*
Include the following lines in your makefile:
cardtest1: cardtest1.c dominion.o rngs.o
gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {

  int newCards = 3;
  int discarded = 1;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	// ----------- TEST 1  --------------
	printf("TEST 1: get 3 extra cards\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testGame, handpos, &bonus);

	printf("number of cards = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] + newCards);
	assertTrue(testGame.handCount == game.deckCount + newCards);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
