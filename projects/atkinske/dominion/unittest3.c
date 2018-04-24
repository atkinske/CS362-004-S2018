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
    int retVal = 0;
    int testState = 0;
    struct gameState G;
    printf("******TESTING scoreFor()******\n");


    //test new game status
    printf("\n**Testing for new game (3VP) scenario**\n");
    printf("\nTesting with normal reset values, expecting return value: 3\n");

    for (int i = 0; i < 1; i++) {
        resetTest(&G);
        retVal = scoreFor(i, &G);
        printf("Testing for player %d\n", i);
        if (assertTrue(3, retVal)) {
            printf("Assert for Function Test Passed, received value:%d\n", retVal);
        } else {
            printf("Assert for Function Test Failed, received value:%d\n", retVal);
            testState++;
        }
    }

    //test for discard score counting
    printf("\n**Testing for duchy in discard (6VP) scenario**\n");
    printf("\nTesting with duchy in discard, expecting return value: 6\n");

    for (int i = 0; i < 1; i++) {
        resetTest(&G);
        G.discardCount[i] = 1; //set discard count value
        G.discard[i][0] = duchy;
        retVal = scoreFor(i, &G);
        printf("Testing for player %d\n", i);
        if (assertTrue(6, retVal)) {
            printf("Assert for Function Test Passed, received value:%d\n", retVal);
        } else {
            printf("Assert for Function Test Failed, received value:%d\n", retVal);
            testState++;
        }
    }
    //test for score from cards in deck
    printf("\n**Testing for province in deck (9VP) scenario**\n");
    printf("\nTesting with province in deck, expecting return value: 9\n");

    for (int i = 0; i < 1; i++) {
        resetTest(&G);
        //find first copper in deck and replace
        for(int i = 0; i < G.deckCount[0]; i++)
        {
            if (G.deck[0][i] == copper)
            {
                G.deck[0][i] = province;
                printf("Copper card replaced with province\n");
                break;
            }
            if (i == G.deckCount[0] - 1)
            {
                printf("ERROR: No coppers found in deck\n");
            }
        }
        retVal = scoreFor(i, &G);
        printf("Testing for player %d\n", i);
        if (assertTrue(9, retVal)) {
            printf("Assert for Function Test Passed, received value:%d\n", retVal);
        } else {
            printf("Assert for Function Test Failed, received value:%d\n", retVal);
            testState++;
        }
    }


    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests for scoreFor() Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);
    }
    return 0;
}