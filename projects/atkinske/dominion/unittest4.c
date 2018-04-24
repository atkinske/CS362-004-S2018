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

void resetTest(struct gameState *G) {
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    memset(G, -5, sizeof (struct gameState));
    initializeGame(numPlayers, k, seed, G); // initialize a new game 
    //G->hand[0][0] = cardValue;
    G->phase = 0;
    G->numActions = 1;
}

int main() {
    //int retVal = 0;
    int testState = 0;
    struct gameState G;
    printf("******TESTING endTurn()******\n");


    //test new game status
    printf("\n**Testing for typical first turn scenarios**\n\n");
    resetTest(&G);
    endTurn(&G);
    printf("Testing for whoseTurn, expected value:1\n");
    if (assertTrue(1, G.whoseTurn)) {
        printf("Assert for Function Test Passed, received value:%d\n", G.whoseTurn);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.whoseTurn);
        testState++;
    }
    
        printf("\nTesting for cardCount of player[1], expected value:5\n");
    if (assertTrue(5, G.handCount[1])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.handCount[1]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.handCount[1]);
        testState++;
    }

        printf("\nTesting for discardCount of player[0], expected value:5\n");
    if (assertTrue(5, G.discardCount[0])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.discardCount[0]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.discardCount[0]);
        testState++;
    }        
    
    printf("\n**Testing for typical second turn scenarios**\n\n");
    endTurn(&G); //run endTurn again, without reset
    printf("Testing for whoseTurn, expected value:0\n");
    if (assertTrue(0, G.whoseTurn)) {
        printf("Assert for Function Test Passed, received value:%d\n", G.whoseTurn);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.whoseTurn);
        testState++;
    }
    
        printf("\nTesting for cardCount of player[0], expected value:5\n");
    if (assertTrue(5, G.handCount[0])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.handCount[0]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.handCount[0]);
        testState++;
    }

        printf("\nTesting for discardCount of player[0], expected value:5\n");
    if (assertTrue(5, G.discardCount[0])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.discardCount[0]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.discardCount[0]);
        testState++;
    }        
   
    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests for endTurn() Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);
    }
    return 0;
}