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

#define TESTCARD "great_hall"

int main() {

  int newCards = 0;
  int discarded = 1;
  int addAct = 0;
  int actTaken = 0;
  int shuffledCards = 0;
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
	printf("TEST 1: draw an extra card and get an extra action\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	addAct = 1;
  actTaken = 1;
	printf("number of actions = %d, expected = %d\n", testGame.numActions, game.numActions + addAct);
  printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);

  assert(testGame.numActions == game.numActions + addAct - actTaken);
  assert(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded);
  assert(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
