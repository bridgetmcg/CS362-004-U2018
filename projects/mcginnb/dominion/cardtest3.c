// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// This tests the "great hall" effect
// Name: Bridget McGinn
// CS362

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "greathall"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("TEST 1: test if the player gains a card in their hand\n");
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if ( testG.handCount[thisPlayer] == (G.handCount[thisPlayer] + newCards - discarded))
	{
		printf("TEST PASSED\n\n");
	}
	else 
	{
		printf("TEST FAILED\n\n");
	}

	printf("TEST 2: test if the player gains 1 action\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.numActions == G.numActions + 1)
	{
		printf("TEST PASSED\n");
	}
	else 
	{
		printf("TEST FAILED\n");
	}

	printf("\nTEST 3: Check that the nothing was changed in another player's hand. \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.handCount[1] == G.handCount[1] && testG.discardCount[1] == G.discardCount[1] && testG.deckCount[1] == G.deckCount[1])
	{
		printf("TEST PASSED no change in other player's hand\n");
	}
	else
	{
		printf("TEST FAILED change in other player's hand\n\n");

	}

	printf("\nTEST 4: Check that there were no changes in the player's coins or buys. \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (testG.coins == G.coins)
	{
		printf("TEST PASSED\n\n");
	}
	else 
	{
		printf("TEST FAILED\n\n");
	}

	return 0;
}



