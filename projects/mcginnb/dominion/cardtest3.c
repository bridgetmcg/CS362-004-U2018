
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
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("TEST 1: test if 3 new cards are added to the deck and if current card is discardeds\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discard);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

	printf("TEST 2: check that the played cards were discarded properly\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("output = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], G.hand[thisPlayer][handpos]);
	

	printf("TEST 3: check that the new cards are from the player's pile\n");
	for (m=0; m<G.deckCount[thisPlayer]; m++)
	{
		printf("Cards in deck before: %d\n", G.deck[thisPlayer][m]);
	}

	for (m=0; m<G.handCount[thisPlayer]; m++)
	{
		printf("Cards in hand before: %d\n", G.hand[thisPlayer][m]);
	}

	for (m=0; m<G.discardCount[thisPlayer]; m++)
	{
		printf("Cards in hand before: %d\n", G.discard[thisPlayer][m]);
	}

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	for (m=0; m<G.handCount[thisPlayer]; m++)
	{
		printf("Cards hand after: %d\n", G.deck[thisPlayer][m]);
	}




	printf("new cards in hand = %d, cards in  = %d\n", testG.playedCards[testG.playedCardCount -1], G.hand[thisPlayer][handpos]);


	return 0;
}
