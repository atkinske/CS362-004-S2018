/* -----------------------------------------------------------------------
 * Author: Kevin Atkinson
 * Date: 5/6/18
 * Description: Assignment 4 - Random test for the Village card
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

int randomizeDeck(int cardQty, struct gameState *G) {
    int player = 0;
    int randCard, randTreasure;

    //player = (rand() % G->numPlayers); //set to random player
    G->deckCount[player] = 0; //reset deck count

    for (int i = 0; i < cardQty; i++) {
        randCard = (rand() % 27);
        G->deck[player][i] = randCard;
        G->deckCount[player]++;
    }
    //randomize with at least 2 treasure cards
    for (int i = 0; i < 2; i++) {
        randCard = (rand() % cardQty);
        randTreasure = (rand() % 3) + 4;
        G->deck[player][randCard] = randTreasure;
    }
    return player;
}

int randomizeDeckandDiscard(int deckQty, int discQty, struct gameState *G) {
    int player = 0;
    int randCard, randTreasure;

    //player = (rand() % G->numPlayers); //set to random player
    G->deckCount[player] = 0; //reset deck count

    //randomize player deck
    for (int i = 0; i < deckQty; i++) {
        randCard = (rand() % 27);
        G->deck[player][i] = randCard;
        G->deckCount[player]++;
    }
    //randomize discard pile
    for (int i = 0; i < discQty; i++) {
        randCard = (rand() % 27);
        G->discard[player][i] = randCard;
        G->discardCount[player]++;
    }

    return player;
}

int playerControl(int controlPlayer, struct gameState *Control, struct gameState *Test) {
    int result = 0;
    if (!assertTrue(Control->handCount[controlPlayer], Test->handCount[controlPlayer])) {
        result = 1;
    }
    if (!assertTrue(Control->deckCount[controlPlayer], Test->deckCount[controlPlayer])) {
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
    int testPlayer = 0;
    int controlPlayer = 1;
    int control;
    int deckSize = 30; //ensure deck size is of appropriate size, >10
    int discSize = 10; //ensure discard pile size is of appropriate size, > 0
    const int TEST_RUNS = 10; //set the loop count for testing
    struct gameState G;
    struct gameState T;
    printf("******RANDOM TESTING Village Card******\n");
    
    srand(time(0));
    //random test with randomized remaining deck left
    for (int i = 0; i < TEST_RUNS; i++) 
    {
        resetTest(village, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        randomizeDeck(deckSize, &G);
        cardEffect(village, -1, -1, -1, &G, 0, -1); //simulate adventurer card play
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer]);
        if (assertTrue(T.handCount[testPlayer], G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", T.handCount[testPlayer]);
        } else {
            printf("Assert for handCount with randomized deck Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        if (assertTrue(T.numActions +1, G.numActions)) {
         //   printf("Assert for Actions Test Passed, received value:%d\n", T.numActions[testPlayer] + 1);
        } else {
            printf("Assert for player actions with randomized deck Failed, received value:%d\n", G.numActions);
            testState++;
        }
        testState = testState + playerControl(controlPlayer, &T, &G);
        //assert for discard count?
        //assert for player 2 status change   
    }
    //test for random deck, with random shuffle required
    for (int i = 0; i < TEST_RUNS; i++) {
        resetTest(village, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        randomizeDeckandDiscard(deckSize, discSize, &G);
        cardEffect(village, -1, -1, -1, &G, 0, -1); //simulate village card play
      //  printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer]);
        if (assertTrue(T.handCount[testPlayer], G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", T.handCount[testPlayer]);
        } else {
            printf("Assert for shuffling required tests Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        //test to make sure other player is not affected
        if (assertTrue(T.numActions + 1, G.numActions)) {
         //   printf("Assert for Actions Test Passed, received value:%d\n", T.numActions[testPlayer]);
        } else {
            printf("Assert for player actions with randomized deck and shuffle Failed, received value:%d\n", G.numActions);
            testState++;
        }
        //testState = testState + playerControl(controlPlayer, &T, &G);
    }
        //test with bad data (bad state, bad current player)
    for (int i = 0; i < TEST_RUNS; i++) {
        resetTest(village, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        randomizeDeckandDiscard(deckSize, discSize, &G);
        testPlayer = 1; //bad current player
        cardEffect(village, -1, -1, -1, &G, 1, -1); //simulate village card play with bad current player
        //printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer]);
        if (assertTrue(T.handCount[testPlayer], G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", T.handCount[testPlayer]);
        } else {
            printf("Assert for player actions with bad Player Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        if (assertTrue(T.numActions + 1, G.numActions)) {
         //   printf("Assert for Actions Test Passed, received value:%d\n", T.numActions[testPlayer] + 1);
        } else {
            printf("Assert for actions with bad Player Failed, received value:%d\n", G.numActions);
            testState++;
        }
        
        //test with randomized bad hand position for potential failure
        resetTest(village, &G); //set state to original settings
        randomizeDeckandDiscard(deckSize, discSize, &G);
        T = G; //copy the game state into base testing state struct
        int handPos = rand() %1000 + 10;
        testPlayer =0;
        cardEffect(village, -1, -1, -1, &G, handPos, -1); //simulate village card play with bad current player
        //printf("Testing discardCount value, expected value:%d\n", T.discardCount[testPlayer]);
        if (assertTrue(T.discardCount[testPlayer], G.discardCount[testPlayer])) {
         //   printf("Assert for handCount shuffling required tests Passed, received value:%d\n", T.handCount[testPlayer]);
        } else {
            printf("Assert for discard with bad hand Position required tests Failed, received value:%d\n", G.discardCount[testPlayer]);
            testState++;
        }
        if (assertTrue(T.numActions + 1, G.numActions)) {
         //   printf("Assert for Actions Test Passed, received value:%d\n", T.numActions[testPlayer] + 1);
        } else {
            printf("Assert for actions with bad handPos Failed, received value:%d\n", G.numActions);
            testState++;
        }
        //test to make sure other player is not affected
        testState = testState + playerControl(controlPlayer, &T, &G);
    }
    
    //boundary cases (100+ card deck, 100+ card discard)
    for (int i = 0; i < TEST_RUNS; i++) 
    {
        testPlayer = 0;
        resetTest(village, &G); //set state to original settings
        T = G; //copy the game state into base testing state struct
        deckSize = rand() %100 + 100;
        discSize = rand() %100 + 100;        
        randomizeDeckandDiscard(deckSize, discSize, &G);
        cardEffect(village, -1, -1, -1, &G, 0, -1); //simulate village card play
     //   printf("Testing handCount value, expected value:%d\n", T.handCount[testPlayer]);
          if (assertTrue(T.handCount[testPlayer], G.handCount[testPlayer])) {
         //   printf("Assert for Function Test Passed, received value:%d\n", T.handCount[testPlayer]);
        } else {
            printf("Assert for shuffling required tests Failed, received value:%d\n", G.handCount[testPlayer]);
            testState++;
        }
        //test to make sure other player is not affected
        if (assertTrue(T.numActions + 1, G.numActions)) {
         //   printf("Assert for Actions Test Passed, received value:%d\n", T.numActions[testPlayer] + 1);
        } else {
            printf("Assert for player actions with randomized deck Failed, received value:%d\n", G.numActions);
        }
        testState = testState + playerControl(controlPlayer, &T, &G); 
    }
    
    //display testing summary
    if (testState == 0) {
        printf("\n\nAll Tests for the Village card Passed!!\n");
    } else {
        printf("\n\n%d TEST FAILURES! Reference above for specific test cases.\n", testState);
    }
    return 0;
}