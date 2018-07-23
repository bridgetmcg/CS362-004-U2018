// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// This tests the "smithy" effect
// Name: Bridget McGinn
// CS362

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discard = 1;
    int shuffledCards = 0;

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

	printf("TEST 1: test if the hand count increases by 3 and if the deck count decreases by 3\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discard);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (testG.handCount[thisPlayer] == (G.handCount[thisPlayer] + newCards - discard))
	{
		printf("TEST PASSED\n");
	}
	else 
	{
		printf("TEST FAILED\n");
	}

	printf("\nTEST 2: Check that the nothing was changed in another player's hand. \n");

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

	printf("\nTEST 3: Check that the two cards came from the player's deck and the other cards were discarded. \n");

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
	printf("\n\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Cards in deck after:");
	for (m=0; m<testG.deckCount[thisPlayer]; m++)
	{
		printf("%d", testG.deck[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	printf("Cards in hand after:");
	for (m=0; m<testG.handCount[thisPlayer]; m++)
	{
		printf("%d", testG.hand[thisPlayer][m]);
		printf(" ");
	}
	printf("\n");
	printf("Cards in discard after:");
	for (m=0; m<testG.discardCount[thisPlayer]; m++)
	{
		printf("%d", testG.discard[thisPlayer][m]);
		printf(" ");
	}
	printf("\n\n");

	printf("Visually check that the cards are the same before and after\n");

	printf("\nTEST 4: Check that no changes were made to the player's coins or buys. \n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
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




