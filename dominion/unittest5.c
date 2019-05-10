/*************************************************
 * unittest1.c
 *************************************************/

#include "dominion.h"
//#include "dominion_help.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR(x) #x
#define MY_ASSERT(x) if (!(x)) { printf("Assertion failed: %S, function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }
#define TESTCARD "adventurer"

int main(){
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int currPlayer=0;
  
  int newCards = 0;
  int discarded = 1;
  int xtraCoins = 2;
  int actions = 0;
  int buys = 0;
  
  int handpos = 0;
  struct gameState game, test;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

  //initialize a game state and player cards
  initializeGame(numPlayer, k, seed, &game);
  game.hand[currPlayer][handpos]=cutpurse;

  printf("--------------------TESTING CARD: %s--------------------\n", TESTCARD);

  //copy the game state to a test case
  memcpy(&test, &game, sizeof(struct gameState));
  //run the function
  i = _cutpurse(&test, handpos, currPlayer);
  //check the player state that it is correct
  printf("Hand Count = %d, expected = %d\n", test.handCount[currPlayer], game.handCount[currPlayer] + newCards - discarded);
  printf("Deck Count = %d, expected = %d\n", test.deckCount[currPlayer], game.deckCount[currPlayer] - test.discardCount[currPlayer]); 
  printf("Coins = %d, expected = %d\n", test.coins, game.coins + xtraCoins);
  printf("Actions = %d, expected = %d\n", test.numActions, game.numActions + actions);
  printf("Buys = %d, expected = %d\n", test.numBuys, game.numBuys + buys);

  //check if the correct card got discarded
  printf("Hand[Handpos] = %d, expected != %d\n unless Discard[discardCount]=%d expected=%d\n", test.hand[currPlayer][handpos], adventurer, test.discard[currPlayer][test.discardCount[currPlayer]-1], adventurer); 
  //check other players hand and deck state
  for(i=1; i<numPlayer; i++){
    int j;
    for(j=0;j<game.handCount[i];j++){
      if(game.hand[i][j]==4){
        printf("Player%d: Hand Count = %d, expected = %d\n", i+1, test.handCount[i], game.handCount[i]-1);
        printf("Player%d: Deck Count = %d, expected = %d\n", i+1, test.deckCount[i], game.deckCount[i]); 
        break;
      }
      if(i==game.handCount[i]-1){
        printf("Player%d: Hand Count = %d, expected = %d\n", i+1, test.handCount[i], game.handCount[i]);
        printf("Player%d: Deck Count = %d, expected = %d\n", i+1, test.deckCount[i], game.deckCount[i]); 
      }
    }
  }
  //make sure none of the victory or kingdom cards changed
  for(i=0; i<treasure_map+1; i++){
    printf("%d = %d, expected = %d\n", i, test.supplyCount[i], game.supplyCount[i]);
  }
}
