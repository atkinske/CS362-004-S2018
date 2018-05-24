/* -----------------------------------------------------------------------
 * Author: Kevin Atkinson
 * Date: 5/6/18
 * Description: Assignment 4 - Random test for the Council Room card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

int numPlayers = 2;

int assertTrue(int valA, int valB) {
    if (valA == valB) {
        return 1;
    }
    return 0;
}

void resetTest(int cardNum, struct gameState *G) {
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    memset(G, -5, sizeof (struct gameState));
    initializeGame(numPlayer, k, seed, G); // initialize a new game 
    G->hand[0][0] = cardNum;
    G->phase = 0;
    G->numActions = 1;
}

int randomizeDeck(struct gameState *G) {
    int player = 0;
    int randCard;
    int cardQty;

    //player = (rand() % G->numPlayers); //set to random player
    G->deckCount[player] = 0; //reset deck count

    cardQty = rand() % 30 + 4; //randomize deck size

    for (int i = 0; i < cardQty; i++) {
        randCard = (rand() % 27);
        G->deck[player][i] = randCard;
        G->deckCount[player]++;
    }
    return player;
}

int randomizeDeckandDiscard(int cardQty, int discQty, struct gameState *G) {
    int player = 0;
    int randCard;

    //player = (rand() % G->numPlayers); //set to random player
    G->deckCount[player] = 0; //reset deck count
    cardQty = rand() % 30 + 2; //randomize deck size

    //randomize player deck with at least 2 cards
    for (int i = 0; i < cardQty; i++) {
        randCard = (rand() % 27);
        G->deck[player][i] = randCard;
        G->deckCount[player]++;
    }
    discQty = rand() % 10 + 4; //randomize discard pile
    //randomize discard pile with at least 4 cards
    for (int i = 0; i < discQty; i++) {
        randCard = (rand() % 27);
        G->discard[player][i] = randCard;
        G->discardCount[player]++;
    }

    return player;
}

int playerControl(int controlPlayer, struct gameState *Control, struct gameState *Test) {
    int result = 0;
    if (!assertTrue(Control->handCount[controlPlayer] + 1, Test->handCount[controlPlayer])) {
        result = 1;
    }
    if (!assertTrue(Control->deckCount[controlPlayer] - 1, Test->deckCount[controlPlayer])) {
        result = 1;
    }
    if (!assertTrue(Control->discardCount[controlPlayer], Test->discardCount[controlPlayer])) {
        result = 1;
    }
    if (!assertTrue(Control->playedCards[controlPlayer], Test->playedCards[controlPlayer])) {
        result = 1;
    }
    return result;
}

int main() {
    // int retVal = 0;
    int testState = 0;
    int testsRan = 0;
    int testPlayer = 0;
    int otherPlayer = 1;
    int controlPlayer = 1;
    int control;
    int deckSize = 30; //ensure deck size is of appropriate size, >10
    int discSize = 10; //ensure discard pile size is of appropriate size, > 0
    const int TEST_RUNS = 10; //set the loop count for testing
    struct gameState G;
    struct gameState T;

    printf("******RANDOM TESTING Council Room Card******\n");
    srand(time(0));
    //random test with randomized remaining deck left, good data
    for (int i = 0; i < TEST_RUNS; i++) {
        resetTest(8, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        randomizeDeckandDiscard(deckSize, discSize, &G);
        cardEffect(council_room, -1, -1, -1, &G, 0, -1); //simulate council room card play
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        testsRan++;
        if (assertTrue(T.handCount[testPlayer] + 3, G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for basic randomized deck Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        testsRan++;
        if (assertTrue(T.handCount[otherPlayer] + 1, G.handCount[otherPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for other player hand count Failed, received value:%d\n", G.handCount[otherPlayer]);
            testState++;
        }
        
        //printf("Testing numBuys value, expected value:%d\n", T.numBuys + 1);
        testsRan++;
        if (assertTrue(T.numBuys + 1, G.numBuys)) {
        //    printf("Assert for Function Test Passed, received value:%d\n", G.numBuys);
        } else {
            printf("Assert for numBuys Failed, received value:%d\n", G.numBuys);
            testState++;
        }
        //assert for player 2 status change   
        testState = testState + playerControl(controlPlayer, &T, &G);
        //assert for discard count?
    }

    //random test that requires a deck shuffle
     for (int i = 0; i < TEST_RUNS; i++) {
        resetTest(8, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        randomizeDeckandDiscard(deckSize, discSize, &G);
        G.deckCount[testPlayer] = 0;
        cardEffect(council_room, -1, -1, -1, &G, 0, -1); //simulate council room card play
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        testsRan++;
        if (assertTrue(T.handCount[testPlayer] + 3, G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for basic randomized deck with shuffle Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        testsRan++;
        if (assertTrue(T.handCount[otherPlayer] + 1, G.handCount[otherPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for other player hand count Failed, received value:%d\n", G.handCount[otherPlayer]);
            testState++;
        }
        
        //printf("Testing numBuys value, expected value:%d\n", T.numBuys + 1);
        if (assertTrue(T.numBuys + 1, G.numBuys)) {
        testsRan++;
        //    printf("Assert for Function Test Passed, received value:%d\n", G.numBuys);
        } else {
            printf("Assert for numBuys Failed, received value:%d\n", G.numBuys);
            testState++;
        }
        //assert for player 2 status change   
        testState = testState + playerControl(controlPlayer, &T, &G);
        //assert for discard count?
    }   
    
    //test with bad player information
    for (int i = 0; i < TEST_RUNS; i++) {
        resetTest(council_room, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        deckSize = 0; //force shuffle with randomized discard pile
        randomizeDeckandDiscard(deckSize, discSize, &G);
        cardEffect(council_room, -1, -1, -1, &G, 0, -1); //simulate council room card play
    
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        testsRan++;
        if (assertTrue(T.handCount[testPlayer] + 3, G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for hand count with shuffle required Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        testsRan++;
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        if (assertTrue(T.handCount[otherPlayer] + 1, G.handCount[otherPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for other players with shuffle required Failed, received value:%d\n", G.handCount[otherPlayer]);
            testState++;
        }
        testsRan++;
        //printf("Testing numBuys value, expected value:%d\n", T.numBuys + 1);
        if (assertTrue(T.numBuys + 1, G.numBuys)) {
        //    printf("Assert for Function Test Passed, received value:%d\n", G.numBuys);
        } else {
            printf("Assert for numBuys with shuffle required Failed, received value:%d\n", G.numBuys);
            testState++;
        }
    
    }

    //boundary cases (1000 card deck, 1000 card discard, numPlayers = 100)
    for (int i = 0; i < TEST_RUNS; i++) {
        resetTest(8, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        testPlayer = 0;
        G.numPlayers = 2;
        deckSize = rand () %100 + 100;
        discSize = rand () %100 + 100;
        randomizeDeckandDiscard(deckSize, discSize, &G);
        cardEffect(council_room, -1, -1, -1, &G, 0, -1); //simulate council room card play
       // printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        testsRan++;
        if (assertTrue(T.handCount[testPlayer] + 3, G.handCount[testPlayer])) {
          //  printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for Boundary Test Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer] + 3);
        if (assertTrue(T.handCount[otherPlayer] + 1, G.handCount[otherPlayer])) {
        testsRan++; 
        //   printf("Assert for Function Test Passed, received value:%d\n", G.handCount[testPlayer]);
        } else {
            printf("Assert for other player hand count Failed, received value:%d\n", G.handCount[otherPlayer]);
            testState++;
        }
    }

    printf("Total tests ran: %d", testsRan);
    if (testState == 0) {
        printf("\n\nAll %d Tests for the councilRoom card Passed!!\n", testsRan);
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);
    }
    return 0;
}