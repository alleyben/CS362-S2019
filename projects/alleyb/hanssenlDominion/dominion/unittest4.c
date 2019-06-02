#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "villageEffect"

int main() {

  int newCards = 0;
  int addActs = 0;
  int shuffledCards = 0;
  int handpos = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	// ----------- TEST 1  --------------
	printf("TEST 1\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

  addActs = 2;
  newCards = 1;

	// villageEffect(thisPlayer, &testGame, handpos);
  // choice 1, 2, and 3 and bonus == 0
  cardEffect(village, 0, 0, 0, &testGame, handpos, 0);


  printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards);
  assertTrue(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards);
  printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
  assertTrue(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("number actions = %d, expected = %d\n", testGame.numActions, game.numActions + addActs);
	assertTrue(testGame.numActions == game.numActions + addActs);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}
