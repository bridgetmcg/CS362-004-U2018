// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// Purpose: This tests the isGameOver() function
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
  int seed = 30;
  int numPlayers = 2;

	struct gameState G, testG, otherTest;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

  	
  //TESTING
  printf("----------------- Testing isGameOver(): ----------------\n");
  printf("\nTEST 1: check that isGameOver will work if there are no Provinces.\n");
  G.supplyCount[3] = 0;
  printf("Provinces: %d\n",G.supplyCount[3]);
  m=0;
  for (i = 0; i < 25; i++)
  {
    if (G.supplyCount[i] == 0)
     {
       m++;
     }
  }
  printf("Number of supplies with 0: %d\n", m);

  if(isGameOver(&G) == 1)
  {
    printf("TEST 1 = PASS\n");
  }
  else
  {
    printf("TEST 1 = FAIL\n");
  }

  printf("\nTEST 2: check that isGameOver will work if there are three cards with 0 left.\n");
  initializeGame(numPlayers, k, seed, &otherTest);
  j=8;
  printf("Provinces: %d\n", otherTest.supplyCount[3]);

  for (i = 8; i < 11; i++)
  {
    otherTest.supplyCount[i] = 0;
  }
  m =0;
  for (i = 0; i < 25; i++)
  {
    if (otherTest.supplyCount[i] == 0)
     {
       m++;
     }
  }
printf("Number of supplies with 0: %d\n", m);
if(isGameOver(&otherTest) == 1)
  {
    printf("TEST 2 = PASS\n");
  }
  else
  {
    printf("TEST 2 = FAIL\n");
  }

printf("\nTEST 3: check that isGameOver will return 0 if neither of the criteria are met.\n");
initializeGame(numPlayers, k, seed, &testG);
if(isGameOver(&testG) == 0)
  {
    printf("TEST 3 = PASS\n\n");
  }
  else
  {
    printf("TEST 3 = FAIL\n\n");
  }
return 0;
}


