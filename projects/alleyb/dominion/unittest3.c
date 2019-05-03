#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "smithyEffect"

int main() {

  int newCards = 0;
  int discarded = 1;
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
	printf("TEST 1: this player effects\n");

	// copy the game state to a test case
  memcpy(&testGame, &game, sizeof(struct gameState));

  newCards = 3;

	smithyEffect(thisPlayer, &testGame, handpos);


  printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
  assert(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded);
  assert(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}
