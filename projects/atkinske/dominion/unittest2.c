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
// set NOISY_TEST to 0 to remove printfs from output

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

    printf("******TESTING isGameOver()******\n");
    
    
    //test for game not over status
     printf("\n**Testing for normal play (game not over) scenario**\n");
    resetTest(13, &G);
    printf("\nTesting with normal reset values, expecting return value: 0\n");
    retVal = isGameOver(&G);
    if (assertTrue(0, retVal)) {
        printf("Assert for Function Test Passed, received value:%d\n", retVal);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", retVal);
        testState++;
    }   
    
    //test for successful Province card victory status
    printf("\n**Testing for 0 Province cards scenario**\n");
    resetTest(13, &G);
    G.supplyCount[province] = 0; //set Province count to 0
    printf("\nTesting with province supply 0, expecting return value: 1\n");
    retVal = isGameOver(&G);
    if (assertTrue(1, retVal)) {
        printf("Assert for Function Test Passed, received value:%d\n", retVal);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", retVal);
        testState++;
    }

    //test for successful function completion
    printf("\n**Testing for 3 supply piles empty scenario**\n");
    resetTest(13, &G);
    G.supplyCount[adventurer] = 0;
    G.supplyCount[council_room] = 0;
    G.supplyCount[feast] = 0;
    printf("\nTesting with cards 7, 8, and 9 empty, expecting return value: 1\n");
    retVal = isGameOver(&G);
    if (assertTrue(1, retVal)) {
        printf("Assert for Function Test Passed, received value:%d\n", retVal);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", retVal);
        testState++;
    }

    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests for isGameOver() Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);    
    }
    return 0;
}