
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TESTCARD "adventurer"
int AdventurerTreasureFail = 0;
int AdventurerCardCountFail = 0;
int AdventurerFail = 0;
int drawCardFail = 0;


void checkAdventureCard(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int r,m, i, cardDrawn, cardHolder;
  int z = 0;
  int bonus = 0;
  int drawnTreasure = 0;
  int PreTreasure = 0;
  int PostTreasure = 0;
  int tempHand[MAX_HAND];

  r = cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);
  while(drawnTreasure < 2)
  {
    if (pre.deckCount[p] < 1) {
      shuffle(p,&pre);}
    m = drawCard(p, &pre);
    cardDrawn = pre.hand[p][pre.handCount[p]-1];
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    {
      drawnTreasure++;
    }
    else
    {
      tempHand[z]=cardDrawn;
      pre.handCount[p]--;
      z++;
    }
  }  
  while(z-1 >=0){
    pre.discard[p][pre.discardCount[p]++]=tempHand[z-1];
    z--;
  }
 

  if (m==-1)
  {
      drawCardFail++;
  }
  if (r!=0)
  {
      AdventurerFail++;
  }

  for (i = 0; i < post->handCount[p]; i++) {
    cardHolder = post->hand[p][i];
    if (cardHolder == copper || cardHolder == silver || cardHolder == gold) {
        PostTreasure++;
      }
  }
 
  for (i = 0; i < pre.handCount[p]; i++) {
    cardHolder =pre.hand[p][i];
    if (cardHolder == copper || cardHolder == silver || cardHolder == gold) {
        PreTreasure++;
    }
  }

  if(PostTreasure != PreTreasure)
  {
    AdventurerTreasureFail++;
  }
  if (pre.handCount[p] != post->handCount[p] || pre.deckCount[p] != post->deckCount[p] || pre.discardCount[p] != post -> discardCount[p])
  {
      AdventurerCardCountFail++;
  }
}

int main () {

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  int i, n, p, treasures;
  struct gameState G;
  int treasureCards[] = {copper, silver, gold};

  printf ("RANDOM TESTS running 2000 times.\n");
  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 4);
    G.deckCount[p] = floor(Random() * ((MAX_DECK- 3) + 1) + 3);
    treasures = floor(Random() * ((G.deckCount[p] - 3) + 1) + 3);
    G.discardCount[p] = 0;
    G.handCount[p] = floor(Random() * ((MAX_HAND - 3) + 1) + 3);

    for (i = 0; i < treasures; i++) {
        G.deck[p][i] = treasureCards[rand() % 3];
      }
    G.playedCardCount = floor(Random() * MAX_DECK -1);
    G.whoseTurn = p;
   
    checkAdventureCard(p, &G);
  }

  if (AdventurerTreasureFail + AdventurerCardCountFail + AdventurerFail + drawCardFail == 0)
  {
    printf("ALL RANDOM TESTS PASSED\n");
  }
  else 
  {
    printf("TEST FAILURES\n");
    printf("Adventurer Treasure Fails = %d \n", AdventurerTreasureFail);
    printf("Adventurer Card Count Fails = %d \n", AdventurerCardCountFail);  
    printf("Adventurer Function Fails = %d \n", AdventurerFail);
    printf("Draw Card Fails = %d \n", drawCardFail);
    
  }


  return 0;
}
