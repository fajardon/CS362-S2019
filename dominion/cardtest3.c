/*************************************************
 * cardtest3.c
 *************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR(x) #x
#define MY_ASSERT(x) if (!(x)) { printf("Assertion failed: %S, function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }
#define TESTCARD "minion"

int main(){
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int currPlayer=0;
  
  int newCards = 0;
  int discarded = 1;
  int xtraCoins = 0;
  int shuffledCards = 0;
  int actions = 0;
  int buys = 0;
  
  int handpos = 0;
  int bonus;
  struct gameState game, test;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

  //initialize a game state and player cards
  initializeGame(numPlayer, k, seed, &game);
  game.hand[currPlayer][handpos]=minion;
  //figure out what cards can the player have in hand
  int possibleCards[27];
  memset(possibleCards, 0, 27*sizeof(*possibleCards));
  for(i=0; i<game.handCount[currPlayer]; i++){
    possibleCards[game.hand[currPlayer][i]]=1;
  }
  for(i=0; i<game.deckCount[currPlayer]; i++){
    possibleCards[game.deck[currPlayer][i]]=1;
  }

  printf("--------------------TESTING CARD: %s in cardEffect--------------------\n", TESTCARD);
  printf("----------------- Choice 1: add 2 coins ----------------\n");
  newCards=0;
  shuffledCards=0;
  xtraCoins=0;
  actions=1;
  buys=0;

  //copy the game state to a test case
  memcpy(&test, &game, sizeof(struct gameState));
  //run the function
  i = cardEffect(minion, 1, 0, 0, &test, handpos, &bonus);
  //check the player state that it is correct
  printf("Hand Count = %d, expected = %d\n", test.handCount[currPlayer], game.handCount[currPlayer] - newCards - discarded);
  printf("Deck Count = %d, expected = %d\n", test.deckCount[currPlayer], game.deckCount[currPlayer] - newCards + shuffledCards); 
  printf("Coins = %d, expected = %d\n", test.coins, game.coins + xtraCoins);
  printf("Actions = %d, expected = %d\n", test.numActions, game.numActions + actions);
  printf("Buys = %d, expected = %d\n", test.numBuys, game.numBuys + buys);
  //make sure new cards are from the players deck
  for(i=0; i<game.handCount[currPlayer]; i++){
    if(possibleCards[game.hand[currPlayer][i]]!=1){    
      printf("Card not from deck\n");
    }
  }
  //check if the correct card got discarded
  printf("Hand[Handpos] = %d, expected != %d\n unless Discard[discardCount]=%d expected=%d\n", test.hand[currPlayer][handpos], smithy, test.discard[currPlayer][test.discardCount[currPlayer]-1], smithy); 
  for(i=1; i<numPlayer; i++){
    printf("Player%d: Hand Count = %d, expected = %d\n", i+1, test.handCount[i], game.handCount[i]);
    printf("Player%d: Deck Count = %d, expected = %d\n", i+1, test.deckCount[i], game.deckCount[i]); 
  }
  for(i=0; i<treasure_map+1; i++){
    printf("%d = %d, expected = %d\n", i, test.supplyCount[i], game.supplyCount[i]);
  }

  printf("-- Choice 2: discard hand and get 4 cards; all other players only have 4 cards --\n");
  newCards=4;
  shuffledCards=0;
  xtraCoins=0;
  actions=1;
  buys=0;

  //copy the game state to a test case
  memcpy(&test, &game, sizeof(struct gameState));
  //run the function
  i = cardEffect(minion, 0, 1, 1, &test, handpos, &bonus);
  //check the player state that it is correct
  printf("Hand Count = %d, expected = %d\n", test.handCount[currPlayer], newCards);
  printf("Deck Count = %d, expected = %d\n", test.deckCount[currPlayer], game.deckCount[currPlayer] - newCards + shuffledCards); 
  printf("Coins = %d, expected = %d\n", test.coins, game.coins + xtraCoins);
  printf("Actions = %d, expected = %d\n", test.numActions, game.numActions + actions);
  printf("Buys = %d, expected = %d\n", test.numBuys, game.numBuys + buys);
  //make sure new cards are from the players deck
  for(i=0; i<game.handCount[currPlayer]; i++){
    if(possibleCards[game.hand[currPlayer][i]]!=1){    
      printf("Card not from deck\n");
    }
  }
  //check if the correct card got discarded
  printf("Hand[Handpos] = %d, expected != %d\n unless Discard[discardCount]=%d expected=%d\n", test.hand[currPlayer][handpos], smithy, test.discard[currPlayer][test.discardCount[currPlayer]-1], smithy); 
  for(i=0; i<numPlayer; i++){
    printf("Player%d: Hand Count = %d, expected = %d\n", i+1, test.handCount[i], newCards);
    printf("Player%d: Deck Count = %d, expected = %d\n", i+1, test.deckCount[i], game.deckCount[i]-4); 
  }
  for(i=0; i<treasure_map+1; i++){
    printf("%d = %d, expected = %d\n", i, test.supplyCount[i], game.supplyCount[i]);
  }
}
