/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int numPlayers = 2;

int assertTrue(int valA, int valB) {
    if (valA == valB) {
        return 1;
    }
    return 0;
}

void resetTest(int cardValue, struct gameState *G) {
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    memset(G, -5, sizeof (struct gameState));
    initializeGame(numPlayer, k, seed, G); // initialize a new game 
    G->hand[0][0] = cardValue;
    G->phase = 0;
    G->numActions = 1;
}

int main() {
    int retVal = 0;
    int testState = 0;
    struct gameState G;
    printf("******TESTING Adventurer Card******\n");


    //test new game status
    printf("\n**Testing for typical adventurer play\n\n");
    resetTest(7, &G); //reset test, have adventurer card in handPos 0
    //set deck cards to control
    G.deck[0][0] = estate;
    G.deck[0][1] = copper; //treasure #1
    G.deck[0][2] = smithy;
    G.deck[0][3] = gold; //treasure #2
    cardEffect(adventurer, -1, -1, -1, &G, 0, -1); //simulate adventurer card play
    printf("Testing copper at position 6, expected value:4\n");   
    if (assertTrue(4, G.hand[0][5])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.hand[0][5]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.hand[0][5]);
        testState++;
    }
    printf("\nTesting for gold at position 7, expected value:6\n");     
     if (assertTrue(6, G.hand[0][6])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.hand[0][6]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.hand[0][6]);
        testState++;
    }   
    
     printf("\nTesting for discardCount, expected value:2\n");     
     if (assertTrue(2, G.discardCount[0])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.discardCount[0]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n\n", G.discardCount[0]);
        testState++;
    }   
     
    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests for the Adventurer card Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);
    }
    return 0;
}