// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// Purpose: This tests the shuffleTest() function
// Name: Bridget McGinn
// CS362

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {

    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG, otherTest;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&otherTest, &G, sizeof(struct gameState));
	int money = 0;
  	int smithyPos = -1;
 	int adventurerPos = -1;

  	int numSmithies = 0;
  	int numAdventurers = 0;

  	
  	//TESTING

  	for (j = 0; j < 5; j++) {
    money = 0;
    smithyPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper)
    money++;
      else if (handCard(i, &G) == silver)
    money += 2;
      else if (handCard(i, &G) == gold)
    money += 3;
      else if (handCard(i, &G) == smithy)
    smithyPos = i;
      else if (handCard(i, &G) == adventurer)
    adventurerPos = i;
    }

    if (whoseTurn(&G) == 0) {
      if (smithyPos != -1) {
        playCard(smithyPos, -1, -1, -1, &G);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        buyCard(province, &G);
      }
      else if (money >= 6) {
        buyCard(gold, &G);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
  
        buyCard(smithy, &G);
        numSmithies++;
      }
      else if (money >= 3) {

        buyCard(silver, &G);
      }

      endTurn(&G);
    }
    else {
      if (adventurerPos != -1) {
        playCard(adventurerPos, -1, -1, -1, &G);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }
      if (money >= 8) {
        buyCard(province, &G);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
       
        buyCard(adventurer, &G);
        numAdventurers++;
      }else if (money >= 6){
	    buyCard(gold, &G);
        }
      else if (money >= 3){
	    buyCard(silver, &G);
      }
 

      endTurn(&G);
    }
  } 
  printf("----------------- Testing shuffle(): ----------------\n");


	printf("\nTEST 1: check that the cards from the player's deck are in a different order.\n");
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

	//Copy the structure of the game to the TestG structure
	memcpy(&testG, &G, sizeof(struct gameState));
	shuffle(thisPlayer, &testG);
	
	//Show the cards afterward
	printf("Cards in deck after: ");
	i = 0;
	for (m=0; m<testG.deckCount[thisPlayer]; m++)
	{
		printf("%d", testG.deck[thisPlayer][m]);
		printf(" ");
		if (testG.deck[thisPlayer][m]!= G.deck[thisPlayer][m])
		{
			i = 1;
		}
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
	
	if (i == 1 && testG.deckCount[thisPlayer] == G.deckCount[thisPlayer])
	{
		printf("Deck count is the same before and after but the order is changed PASS\n");
	}
	else 
	{
		printf("Either deck count is not the same before and after or the order has not changed FAIL\n");
	}

	printf("\nTEST 2: Check that the number of cards in the deck after is the same that were in the deck before.\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	shuffle(thisPlayer, &testG);

	printf("Number of cards in deck before: %d\n", testG.deckCount[thisPlayer]);
	printf("Number of cards in deck after: %d\n", G.deckCount[thisPlayer]);

	if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer])
	{
		printf("Cards equal PASS.\n");
	}
	else
	{
		printf("Cards are not equal FAIL.\n");
	}

	printf("\nTEST 3: check that the number and order of another player's card have not been changed.\n");
	
	memcpy(&testG, &G, sizeof(struct gameState));
	shuffle(thisPlayer, &testG);
	if (testG.deckCount[1] == G.deckCount[1] && testG.handCount[1] == G.handCount[1] && testG.discardCount[1] == G.discardCount[1])
	{
		printf("Cards of other player equal PASS.\n");
	}
	else
	{
		printf("Cards of other player not equal FAIL.\n");
	}

	printf("\nTEST 4: check that if there are no cards in the deck, that shuffle returns -1.\n");

	for (j = 0; j < 3; j++) {
    money = 0;
    smithyPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(&otherTest); i++) {
      if (handCard(i, &otherTest) == copper)
    money++;
      else if (handCard(i, &otherTest) == silver)
    money += 2;
      else if (handCard(i, &otherTest) == gold)
    money += 3;
      else if (handCard(i, &otherTest) == smithy)
    smithyPos = i;
      else if (handCard(i, &otherTest) == adventurer)
    adventurerPos = i;
    }

    if (whoseTurn(&otherTest) == 0) {
      if (smithyPos != -1) {
        playCard(smithyPos, -1, -1, -1, &otherTest);
        money = 0;
        i=0;
        while(i<numHandCards(&otherTest)){
          if (handCard(i, &otherTest) == copper){
            playCard(i, -1, -1, -1, &otherTest);
            money++;
          }
          else if (handCard(i, &otherTest) == silver){
            playCard(i, -1, -1, -1, &otherTest);
            money += 2;
          }
          else if (handCard(i, &otherTest) == gold){
            playCard(i, -1, -1, -1, &otherTest);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        buyCard(province, &otherTest);
      }
      else if (money >= 6) {
        buyCard(gold, &otherTest);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
  
        buyCard(smithy, &otherTest);
        numSmithies++;
      }
      else if (money >= 3) {

        buyCard(silver, &otherTest);
      }

      endTurn(&otherTest);
    }
    else {
      if (adventurerPos != -1) {
        playCard(adventurerPos, -1, -1, -1, &otherTest);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &otherTest) == copper){
            playCard(i, -1, -1, -1, &otherTest);
            money++;
          }
          else if (handCard(i, &otherTest) == silver){
            playCard(i, -1, -1, -1, &otherTest);
            money += 2;
          }
          else if (handCard(i, &otherTest) == gold){
            playCard(i, -1, -1, -1, &otherTest);
            money += 3;
          }
          i++;
        }
      }
      if (money >= 8) {
        buyCard(province, &otherTest);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
       
        buyCard(adventurer, &otherTest);
        numAdventurers++;
      }else if (money >= 6){
	    buyCard(gold, &otherTest);
        }
      else if (money >= 3){
	    buyCard(silver, &otherTest);
      }
 

      endTurn(&otherTest);
    }
  } 

	memcpy(&testG, &otherTest, sizeof(struct gameState));
	j = shuffle(thisPlayer, &testG);
	if (j == -1)
	{
		printf("Shuffle returns -1 if there are no cards in the deck PASS.\n\n");
	}
	else
	{
		printf("Shuffle does not return -1 if there are not cards in the deck FAIL.\n");
	}

	return 0;
}

