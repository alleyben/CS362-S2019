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

#define TESTCARD "salvager"

int main() {

  int newCards = 0;
  int discarded = 1;
  int addCoin = 0;
  int addBuys = 0;
  int shuffledCards = 0;
  int m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int removedCard;
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
	printf("TEST 1: get an extra buy\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

  choice1 = 1;
	cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	addBuys = 1;
	printf("number buys = %d, expected = %d\n", testGame.numBuys, game.numBuys + addBuys);
	assert(testGame.numBuys == game.numBuys + addBuys);


	// ----------- TEST 2 --------------

	printf("TEST 2: trash a card and get its cost in coins\n");

	// cycle through each card to get money for
	for (choice1 = 1; choice1 < game.handCount[thisPlayer]; choice1++) {

		game.hand[thisPlayer][0] = steward;
		game.hand[thisPlayer][1] = copper;
		game.hand[thisPlayer][2] = duchy;
		game.hand[thisPlayer][3] = estate;
		game.hand[thisPlayer][4] = feast;

		// copy the game state to a test case
		memcpy(&testGame, &game, sizeof(struct gameState));

    printf("starting money: (%d);", testGame.coins);
		printf("starting cards: ");
		for (m=0; m<testGame.handCount[thisPlayer]; m++) {
			printf("(%d)", testGame.hand[thisPlayer][m]);
		}
		printf("; ");

		removedCard = testGame.hand[thisPlayer][choice1];
    addCoin = getCost( handCard(choice1, &game) );

		cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

		printf("removed card: (%d); ", removedCard);
    printf("added coin: (%d);", addCoin );
		printf("ending cards: ");

		// tests that the removed cards are no longer in the player's hand
		for (m=0; m<testGame.handCount[thisPlayer]; m++) {
			printf("(%d)", testGame.hand[thisPlayer][m]);
			assert(testGame.hand[thisPlayer][m] != removedCard);
		}
		printf(", expected: ");
		for (m=1; m<game.handCount[thisPlayer]; m++) {
			if (game.hand[thisPlayer][m] != game.hand[thisPlayer][choice1]) {
				printf("(%d)", game.hand[thisPlayer][m]);
			}
		}
		printf("\n");

		// tests for the appropriate number of remaining cards
		newCards = 0;
		discarded = 2;

		if (choice1 == 1) {
			printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
			printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
		}

    printf("coins = %d, expected = %d\n", testGame.coins, game.coins + addCoin);

		assert(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded);
		assert(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);
  	assert(testGame.coins == game.coins + addCoin);

	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
