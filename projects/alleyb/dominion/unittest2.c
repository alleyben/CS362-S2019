#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "remodelEffect"

int main() {

  int newCards = 0;
  int discarded = 1;
  int shuffledCards = 0;
  int handpos = 0, choice1 = 0, choice2 = 0, r = 0, i = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int trashedCard = 0;

	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

// trash a card, test each choice
// new card
// card is <= cost of old card + 2
// choice1 for trash card
// choice2 for new card

	// ----------- TEST 1  --------------
	printf("TEST 1: this player effects\n");

  newCards = 1;
  discarded = 1;
  choice1 = 1;
  choice2 = 2;

  for (choice1 = 0; choice1 < game.handCount[thisPlayer]; choice1++) {
		for (choice2 = adventurer; choice2 < treasure_map; choice2++) {

      game.hand[thisPlayer][0] = steward;
      game.hand[thisPlayer][1] = copper;
      game.hand[thisPlayer][2] = duchy;
      game.hand[thisPlayer][3] = estate;
      game.hand[thisPlayer][4] = feast;

      // don't buy a card you trashed
      if (game.hand[thisPlayer][choice1] == choice2) {
        continue;
      }

      trashedCard = game.hand[thisPlayer][choice1];

    	// copy the game state to a test case
    	memcpy(&testGame, &game, sizeof(struct gameState));

      r = remodelEffect(thisPlayer, &testGame, handpos, choice1, choice2);

      printf("expected choice1 cost +2 <= choice 2 cost: %d +2 <= %d\n",
          getCost(trashedCard), getCost(choice2));

      // make sure new card costs no more than 2 more than old card
      if ((getCost(testGame.hand[thisPlayer][choice1]) + 2) <= getCost(choice2)) {
        assert(r == 0);
      }

    }
    // make sure old card is trashed
    for (i = 0; i < game.handCount[thisPlayer]; i++) {
      assert(testGame.hand[thisPlayer][i] != trashedCard);
    }
  }

  printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
  assert(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded);
  assert(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}
