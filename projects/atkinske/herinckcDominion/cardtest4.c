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
    printf("******TESTING Great Hall Card******\n");

    
    //test typical play of card
    printf("\n**Testing for typical Council Room play\n\n");
    resetTest(16, &G); //reset test, have council room in handPos 0
    cardEffect(great_hall, -1, -1, -1, &G, 0, -1); //simulate adventurer card play
    printf("Testing handCount for player[0], expected value:5\n");
    if (assertTrue(5, G.handCount[0])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.handCount[0]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.handCount[0]);
        testState++;
    }
    printf("\nTesting numActions for player[0], expected value:2\n");
    if (assertTrue(2, G.numActions)) {
        printf("Assert for Function Test Passed, received value:%d\n", G.numActions);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n", G.numActions);
        testState++;
    }
    printf("\nTesting for playedCardCount, expected value:1\n");
    if (assertTrue(1, G.discardCount[0])) {
        printf("Assert for Function Test Passed, received value:%d\n", G.discardCount[0]);
    } else {
        printf("Assert for Function Test Failed, received value:%d\n\n", G.discardCount[0]);
        testState++;
    }

    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests for the Great Hall card Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);
    }
    return 0;
}