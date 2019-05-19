/*
Include the following lines in your makefile:
randomtestcard1: randomtestcard1.c dominion.o rngs.o
gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int getTreasureCount(int thisPlayer, struct gameState* game) {
  int i, currentCard = 0, numTreasure = 0;
  for (i = 0; i < game->handCount[thisPlayer]; i++) {
    currentCard = game->hand[thisPlayer][i];
    if( currentCard == copper || currentCard == silver || currentCard == gold ) {
      numTreasure++;
    }
  }
  return numTreasure;
}

int main() {

  int newCards = 0;
  int discarded = 1;
  int numTreasureOld = 0, numTreasureNew = 0, addTreasure = 0;
  int cardCountOld = 0, cardCountNew = 0;
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

// make sure there are two cards minus discard card in hand
	// ----------- TEST 1  --------------
	printf("TEST 1: have two more treasure cards in your hand\n");

  // make sure there are two extra treasure cards

  addTreasure = 2;
  newCards = 2;
  game.hand[thisPlayer][0] = adventurer;
  game.hand[thisPlayer][1] = copper;
  game.hand[thisPlayer][2] = duchy;
  game.hand[thisPlayer][3] = estate;
  game.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

  // find number of treasure cards in hand
  numTreasureNew = getTreasureCount(thisPlayer, &testGame);

  numTreasureOld = getTreasureCount(thisPlayer, &game);


	printf("number treasure = %d, expected = %d\n", numTreasureNew, numTreasureOld + addTreasure);
	assertTrue(numTreasureNew == numTreasureOld + addTreasure);


	// ----------- TEST 2 --------------

	printf("TEST 2: same number of total cards\n");

  // make sure there are same number of total cards
  cardCountOld = game.deckCount[thisPlayer] + game.handCount[thisPlayer] + game.discardCount[thisPlayer];
  cardCountNew = testGame.deckCount[thisPlayer] + testGame.handCount[thisPlayer] + testGame.discardCount[thisPlayer];

  printf("number of cards total (%d); expected (%d)\n", cardCountOld, cardCountNew);
  assertTrue(cardCountOld == cardCountNew);

  // ----------- TEST 3 --------------

  printf("TEST 3: hand is +2 with number of treasure cards\n");

  // make sure hand is +2 with number of treasure cards - discarded card
  printf("number of cards in hand (%d); expected (%d)\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + addTreasure - discarded);
  assertTrue(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + addTreasure - discarded);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
