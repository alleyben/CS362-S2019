/*
Include the following lines in your makefile:
randomtestcard2: randomtestcard2.c dominion.o rngs.o
gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"


int main() {
  srand(time(NULL));
  
  int newCards = 3;
  int discarded = 1;
  int handpos = 0;
  int seed = 0;
  int numPlayers = 0;
  int thisPlayer = 0;
  int cardCountOld = 0;
  int cardCountNew = 0;

	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	for (int i = 0; i < 10; i++) {
	  
	  seed = rand()%1000;
    numPlayers = (rand()%3) + 2;
    thisPlayer = rand()%numPlayers;
    
    initializeGame(numPlayers, k, seed, &game);
    
    handpos = rand()%5;
    game.hand[thisPlayer][handpos] = smithy;

  	printf("----------------- Test %d for Card %s ----------------\n", i+1, TESTCARD);
  
  
  	// ----------- TEST 1  --------------
  	
  	printf("TEST 1: have 3 extra cards in hand\n");
  
  	// copy the game state to a test case
  	memcpy(&testGame, &game, sizeof(struct gameState));
  	
  	smithyEffect(thisPlayer, &testGame, handpos);
  	
  	cardCountOld = game.handCount[thisPlayer] + newCards - discarded;
  	cardCountNew = testGame.handCount[thisPlayer];

  	printf("number of cards = %d, expected = %d\n", cardCountNew, cardCountOld);
  	assertTrue(cardCountNew == cardCountOld);
  	
  	
  	// ----------- TEST 2 --------------
  	
  	printf("TEST 2: same number of total cards in player deck\n");
  
    // make sure there are same number of total cards
    cardCountOld = game.deckCount[thisPlayer] + game.handCount[thisPlayer] + game.discardCount[thisPlayer];
    cardCountNew = testGame.deckCount[thisPlayer] + testGame.handCount[thisPlayer] + testGame.discardCount[thisPlayer];
  
    printf("number of cards total (%d); expected (%d)\n", cardCountOld, cardCountNew);
    assertTrue(cardCountOld == cardCountNew);
	}
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
