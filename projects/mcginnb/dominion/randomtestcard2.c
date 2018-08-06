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

#define TESTCARD "great hall"


int greatHallEffectFail = 0;                                      //Define the failure counters as global variables
int greatHallActionFail = 0;
int greatHallCountFail = 0;
int drawCardFail = 0;
int discardFail = 0;

void checkGreatHallCard(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int r, m, j;
  int bonus = 0;
  r = cardEffect(great_hall, 0, 0, 0, post, 0, &bonus);           //Call cardEffect on the post gamestate
  m = drawCard(p, &pre);                                          //Draw one card as expected on the pre gamestate
  j = discardCard(0, p, &pre, 0);                                 //Discard one card as expected on the pre gamestate
  pre.numActions++;                                               //Increase the number of actions as expected on the pre gamestate
  if (m==-1)
  {
      drawCardFail++;                                             //If the drawCard function was the issue
  }
  if(j==-1)
  {
      discardFail++;                                              //If the discard function was the issue
  }
  if (r!=0)
  {
      greatHallEffectFail++;
  }
  if(pre.numActions != post -> numActions)                        //If the number of actions was the issue
  {
      greatHallActionFail++;
  }
  if (pre.handCount[p] != post->handCount[p] || pre.deckCount[p] != post->deckCount[p])
  {
      greatHallCountFail++;                                       //If the card count was the issue
  }

}

int main () {

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  int i, n, p;
  struct gameState G;
  printf ("RANDOM TESTS running 1000 times.\n");
  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 1000; n++) {                                    //Set up 1000 forms of the gamestate
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * MAX_PLAYERS);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * MAX_DECK -1);
    G.whoseTurn = p;
    G.numActions = floor(Random() * 5);
    checkGreatHallCard(p, &G);                                    //Call the check function
  }

  if (greatHallCountFail + greatHallEffectFail + greatHallActionFail + discardFail + drawCardFail == 0)
  {
    printf("ALL RANDOM TESTS PASSED\n");                          //Display the results as passed if there are no errors
  }
  else 
  {
    printf("TEST FAILURES\n");
    printf("greatHallCountFails = %d \n", greatHallCountFail);
    printf("greatHallEffectFails = %d \n", greatHallEffectFail);  
    printf("greatHallActionFails = %d \n", greatHallActionFail);
    printf("drawCardFail = %d \n", drawCardFail);
    printf("discardFail = %d \n", discardFail);
    
  }
  return 0;
}
