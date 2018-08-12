// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// Purpose: This tests the village function
// Name: Bridget McGinn
// CS362

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int discard = 1;
    int m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
   
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("TEST 1: Check that the player has an additional 2 actions \n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("number with village: %d", testG.numActions);
	printf(";  number expected: %d\n", G.numActions + 2);
	if (testG.numActions == (G.numActions + 2))
	{
		printf("TEST PASSED - actions increased by 2 \n");
	}
	else
	{
		printf("TEST FAILED - actions not increased by 2\n");
	}
	
	printf("\nTEST 2: Check that the player's hand has an additional card\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (testG.handCount == (G.handCount + 1 - discard))
	{
		printf("TEST PASSED - hand count increased by 1\n");
	}
	else
	{
		printf("TEST FAILED - hand count not increased by 1\n");
	}

	printf("\nTEST 3: Check that the player's deck has one fewer cards\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (testG.deckCount == (G.deckCount - 1))
	{
		printf("TEST PASSED - deck count decreased by 1\n");
	}
	else
	{
		printf("TEST FAILED - deck count not decreased by 1\n");
	}

	printf("\nTEST 4: Check that the player's card came from their hand\n");	
	printf("Cards in deck before: ");
	for (m=0; m<G.deckCount[thisPlayer]; m++)
	{
		printf("%d", G.deck[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	printf("Cards in hand before: ");
	for (m=0; m<G.handCount[thisPlayer]; m++)
	{
		printf("%d", G.hand[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	printf("Cards in discard before: ");
	for (m=0; m<G.discardCount[thisPlayer]; m++)
	{
		printf("%d", G.discard[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Cards in deck after: ");
	for (m=0; m<testG.deckCount[thisPlayer]; m++)
	{
		printf("%d", testG.deck[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	printf("Cards in hand after: ");
	for (m=0; m<testG.handCount[thisPlayer]; m++)
	{
		printf("%d", testG.hand[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	printf("Cards in discard after: ");
	for (m=0; m<testG.discardCount[thisPlayer]; m++)
	{
		printf("%d", testG.discard[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");

	printf("Visually check that the cards are the same before and after\n");

	printf("\nTEST 5: Check that the nothing was changed in another player's hand. \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.handCount[1] == G.handCount[1] && testG.discardCount[1] == G.discardCount[1] && testG.deckCount[1] == G.deckCount[1])
	{
		printf("TEST PASSED no change in other player's hand\n\n");
	}
	else
	{
		printf("TEST FAILED change in other player's hand\n\n");

	}

	return 0;
}

