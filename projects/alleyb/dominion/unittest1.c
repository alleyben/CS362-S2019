#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "councilRoomEffect"

int main() {

  int newCards = 0;
  int discarded = 1;
  int addBuys = 0;
  int shuffledCards = 0;
  int handpos = 0, choice1 = 0;
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

  addBuys = 1;
  newCards = 4;
  choice1 = 1;

	councilRoomEffect(thisPlayer, &testGame, handpos);

  printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("number buys = %d, expected = %d\n", testGame.numBuys, game.numBuys + addBuys);
  assert(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded);
  assert(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testGame.numBuys == game.numBuys + addBuys);



	// ----------- TEST 2 --------------

	printf("TEST 2: other players' effect: draw one card\n");

  // copy the game state to a test case
  memcpy(&testGame, &game, sizeof(struct gameState));

  newCards = 1;
  discarded = 0;

  councilRoomEffect(thisPlayer, &testGame, handpos);
  
	// cycle through each player to test number of cards in hand
	for (thisPlayer = 1; thisPlayer < game.numPlayers; thisPlayer++) {

    printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
    assert(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded);
    assert(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);

	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}
