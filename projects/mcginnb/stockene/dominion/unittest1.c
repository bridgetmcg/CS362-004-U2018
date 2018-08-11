// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// Purpose: This tests the fullDeckCount() function
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
	int myCards =0;
    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing fullDeckCount(): ----------------\n");

	printf("\nCheck fullDeckCount() at beginning of game\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	j = fullDeckCount(thisPlayer, 0, &testG);
	for (m=0; m<G.deckCount[thisPlayer]; m++)
	{
		myCards++;
	}

	for (m=0; m<G.handCount[thisPlayer]; m++)
	{
		myCards++;
	}

	for (m=0; m<G.discardCount[thisPlayer]; m++)
	{
		myCards++;
	}

	if (j == myCards)
	{
		printf("Card values before and after are the same PASS\n");
	}
	else 
	{
		printf("Card values before and after are not the same FAIL\n");
	}

	printf("\nCheck fullDeckCount() if a 4 (copper) is passed in\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	j = fullDeckCount(thisPlayer, 4, &testG);
	if (j == 7)
	{

		printf("fullDeckCount can count individual cards PASS\n");
	}
	else 
	{
		printf("fullDeckCount cannot count individual cards FAIL\n");
	}

	printf("\nCheck fullDeckCount() after game runs several times\n");

	int money = 0;
  	int smithyPos = -1;
 	int adventurerPos = -1;

  	int numSmithies = 0;
  	int numAdventurers = 0;

  for (j = 0; j < 6; j++) {
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
	memcpy(&testG, &G, sizeof(struct gameState));
	j = fullDeckCount(thisPlayer, 0, &testG);
	myCards =0;
	for (m=0; m<G.deckCount[thisPlayer]; m++)
	{
		myCards++;
	}

	for (m=0; m<G.handCount[thisPlayer]; m++)
	{
		myCards++;
	}

	for (m=0; m<G.discardCount[thisPlayer]; m++)
	{
		myCards++;
	}

	if (j == myCards)
	{
		printf("Card values before and after are the same PASS\n");
	}
	else 
	{
		printf("Card values before and after are not the same FAIL\n\n");
	}


	return 0;
}


