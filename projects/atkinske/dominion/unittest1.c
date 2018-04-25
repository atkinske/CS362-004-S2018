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

int assertTrue(void *valA, void *valB) {
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

    printf("******TESTING playCard()******\n");
    //test for successful function completion
    printf("\n**Testing for function success**\n");
    resetTest(13, &G);
    printf("\nTesting with passing values, expecting return value: 0\n");
    retVal = playCard(0, -1, -1, -1, &G);
    if (assertTrue(0, retVal)) {
        printf("Assert for Function Test Passed, received value:%d\n", retVal);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", retVal);
    }

    //test for phase failure
    printf("\n**Testing for phase states failure**\n");
    resetTest(13, &G);
    G.phase = 1; //set phase to 1, failure state
    retVal = playCard(0, -1, -1, -1, &G);
    printf("\nTesting with phase=1, expecting return value: -1\n");
    if (assertTrue(-1, playCard(1, -1, -1, -1, &G))) {
        printf("Assert for Phase Test Passed, received value:%d\n", retVal);
    } else {
        printf("!!!Assert for Phase Test Failed, received value:%d\n", retVal);
        testState++;
    }

    //test for player actions failure
    printf("\n**Testing for player actions failure**\n");
    resetTest(13, &G);
    G.numActions = 0; //set actions to 0, failure state
    printf("\nTesting with player actions=0, expecting return value: -1\n");
    retVal = playCard(0, -1, -1, -1, &G);
    if (assertTrue(-1, retVal)) {
        printf("Assert for Player Actions Test Passed, received value:%d\n", retVal);
    } else {
        printf("Assert for Player Actions Test Failed, received value:%d\n", retVal);
        testState++;
    }

    //test for non-action card
    printf("\n**Testing for non-action card failure**\n");
    resetTest(0, &G); //set Card to non-action card
    printf("\nTesting with cardValue=0, expecting return value: -1\n");
    retVal = playCard(0, -1, -1, -1, &G);
    if (assertTrue(-1, retVal)) {
        printf("Assert for Player Actions Test Passed, received value:%d\n", retVal);
    } else {
        printf("Assert for Player Actions Test Failed, received value:%d\n", retVal);
        testState++;
    }

    //test for reduction of numActions
    printf("\n**Testing for numActions reduction**\n");
    resetTest(7, &G); //set card to Adventurer, no additional actions granted
    int preTestNumActions = G.numActions;
    printf("\nTesting comparison for numActions, expecting return value: %d\n", preTestNumActions - 1);
    retVal = playCard(0, -1, -1, -1, &G);
    if (assertTrue(preTestNumActions - 1, (G.numActions))) {
        printf("Assert for numActions Test Passed, received value:%d\n", G.numActions);
    } else {
        printf("Assert for numActions Test Failed, received value:%d\n", G.numActions);
        testState++;    
    }

    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);    
    }
    return 0;
}