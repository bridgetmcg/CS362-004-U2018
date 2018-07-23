// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// This tests the "adventurer" effect
// Name: Bridget McGinn
// CS362

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
 
    int m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int discard = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("\nTEST 1: Check that the player's hand has two additional cards. \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (G.handCount[thisPlayer] == testG.handCount[thisPlayer] + 2 - discard)
	{
		printf("TEST PASSED HAND COUNT INCREASED CORRECTLY\n");
	}
	else
	{
		printf("TEST FAILED HAND COUNT not properly increased\n");
	}


	printf("\nTEST 2: Check that the two cards came from the player's deck and the other cards were discarded. \n");

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

	printf("Visually check that the cards are the same before and after\n\n");

	if (testG.handCount[thisPlayer]+ testG.deckCount[thisPlayer]+ testG.discardCount[thisPlayer] == 10)
	{
		printf("TEST PASSED HAND COUNT INCREASED CORRECTLY\n");
	}
	else
	{
		printf("TEST FAILED HAND COUNT not properly increased.\n");
	}

	printf("\nTEST 3: Check that the nothing was changed in another player's hand. \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.handCount[1] == G.handCount[1] && testG.discardCount[1] == G.discardCount[1] && testG.deckCount[1] == G.deckCount[1])
	{
		printf("TEST PASSED no change in other player's hand\n");
	}
	else
	{
		printf("TEST FAILED change in other player's hand\n\n");

	}

	return 0;
}

