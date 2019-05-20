/*
Include the following lines in your makefile:
randomtestcard3: randomtestcard3.c dominion.o rngs.o
gcc -o randomtestcard1 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTFUNCTION "villageEffect"


int main() {

  int newCards = 0;
  int addActs = 0;
  int shuffledCards = 0;
  int handpos = 0;
  int seed = 0;
  int numPlayers = 0;
  int thisPlayer = 0;

	struct gameState game, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
			
	
	for (int i = 0; i < 10; i++) {
  	
  	seed = rand()%1000;
    numPlayers = (rand()%3) + 2;
    thisPlayer = rand()%numPlayers;
    
    initializeGame(numPlayers, k, seed, &game);
    
    handpos = rand()%5;
    game.hand[thisPlayer][handpos] = village;
  
  	printf("----------------- Test %d for Card %s ----------------\n", i+1, TESTFUNCTION);
  
  	// copy the game state to a test case
  	memcpy(&testGame, &game, sizeof(struct gameState));
  
    addActs = 2;
    newCards = 1;
  
  	villageEffect(thisPlayer, &testGame, handpos);
  	
  	// ----------- TEST 1  --------------
  	printf("TEST 1: hand count is +1\n");
    printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards);
    assertTrue(testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards);
    
    // ----------- TEST 2  --------------
  	printf("TEST 2: deck count is the same\n");
    printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);
    assertTrue(testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards);
    
    // ----------- TEST 3  --------------
  	printf("TEST 3: number of actions is +2\n");
  	printf("number actions = %d, expected = %d\n", testGame.numActions, game.numActions + addActs);
  	assertTrue(testGame.numActions == game.numActions + addActs);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);

	return 0;
}
