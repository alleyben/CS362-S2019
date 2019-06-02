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
#include <time.h>

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

  srand(time(NULL));
  int discarded = 1;
  int numTreasureOld = 0, numTreasureNew = 0, addTreasure = 0;
  int cardCountOld = 0, cardCountNew = 0;
  int handpos = 0;
  int seed = 0;
  int numPlayers = 0;
  int thisPlayer = 0;

  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
  			sea_hag, tribute, smithy, council_room};

  struct gameState game, testGame;


  for (int i = 0; i < 10; i++){

    // randomize
    seed = rand()%1000;
    numPlayers = (rand()%3) + 2;
    thisPlayer = rand()%numPlayers;

  	// initialize a game state and player cards
  	initializeGame(numPlayers, k, seed, &game);

  	printf("----------------- Test %d for Card %s ----------------\n", i+1, TESTCARD);

  // make sure there are two cards minus discard card in hand
  	// ----------- TEST 1  --------------
  	printf("TEST 1: have two more treasure cards in your hand\n");

    // make sure there are two extra treasure cards

    addTreasure = 2;
    // randomize
    handpos = rand()%5;
    game.hand[thisPlayer][handpos] = adventurer;

  	// copy the game state to a test case
  	memcpy(&testGame, &game, sizeof(struct gameState));

  	// adventurerEffect(thisPlayer, &testGame, handpos);
    // choice 1, 2, and 3 and bonus == 0
    cardEffect(adventurer, 0, 0, 0, &testGame, handpos, 0);

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



  }
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
