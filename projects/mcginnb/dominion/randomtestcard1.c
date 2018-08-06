//Bridget McGinn
//Note: I used the code framework from TestDrawCard.c to outline my random testing

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TESTCARD "smithy"

int smithyFail = 0;												//Define the failure counters as global variables
int drawCardFail = 0;
int discardFail = 0;

void checkSmithyCard(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int r, m, j;
  int bonus = 0;
  r = cardEffect(smithy, 0, 0, 0, post, 0, &bonus);				//Call cardEffect on the post gamestate
  m = drawCard(p, &pre);										//Draw three cards as expected on the pre gamestate
  m = drawCard(p, &pre);
  m = drawCard(p, &pre);
  j = discardCard(0, p, &pre, 0);								//Discard one card as expected on the pre gamestate

  if (m==-1)
  {
  		drawCardFail++;											//If the drawCard function was the issue
  }
  if(j==-1)
  {
  		discardFail++;											//If the discard funciton was the issue
  }
  if (r!=0)
  {
  		smithyFail++;									
  }
 
  if (pre.handCount[p] != post->handCount[p] || pre.deckCount[p] != post->deckCount[p])
  {
  		smithyFail++;											//Check if the three cards were correctly added
  }

}

int main () {

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  int i, n, p;
  struct gameState G;
  printf ("RANDOM TESTS running 1000 times.\n");
  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 1000; n++) {									//Set up 1000 forms of the gamestate
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * MAX_PLAYERS);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * MAX_DECK -1);
    G.whoseTurn = p;
    checkSmithyCard(p, &G);										//Call the check function
  }

  if (smithyFail + discardFail + drawCardFail == 0)				//Display the results as passed if there are no errors
  {
  	printf("ALL RANDOM TESTS PASSED\n");
  }
  else 
  {
  	printf("TEST FAILURES\n");
  	printf("smithyFails = %d \n", smithyFail);
  	printf("drawCardFail = %d \n", drawCardFail);
  	printf("discardFail = %d \n", discardFail);
  	
  }
  return 0;
}
