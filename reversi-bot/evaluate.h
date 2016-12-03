#ifndef _EVALUATE_H_
#define _EVALUATE_H_

#include "common.h"
#include "reversinode.h"

int desk_weights[8][8] =
        {{99, -8, 8, 6, 6, 8, -8, 99},
         {-8, -24, -4, -3, -3, -4, -24, -8},
         {8, -4, 7, 4, 4, 7, -4, 8},
         {6, -3, 4, 0, 0, 4, -3, 6},
         {6, -3, 4, 0, 0, 4, -3, 6},
         {8, -4, 7, 4, 4, 7, -4, 8},
         {-8, -24, -4, -3, -3, -4, -24, -8},
        {99, -8, 8, 6, 6, 8, -8, 99}};

AwardType weightedDeskEval(Node &node) {
    AwardType weightedDeskAward = 0;
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            if (node.filledMask(i, j)) {
                if (node.whiteMask(i, j)) {
                    weightedDeskAward += desk_weights[i][j];
                } else {
                    weightedDeskAward -= desk_weights[i][j];
                }
            }
        }
    }
    return (iamwhite ? weightedDeskAward : -weightedDeskAward);
}

AwardType mobilityEval(Node &node) {
    AwardType mobilityAward = getValidActions(node).size();
    node.pass();
    mobilityAward -= getValidActions(node).size();
    node.pass();

    return mobilityAward * (isMaxNode(node) ? 1 : -1);
}

const AwardType MAX_SCORE = 1e5;
AwardType terminalNodeEvaluate(Node &node) {
    int finalScore = node.countWhites() - node.countBlacks();

    if (finalScore > 0) finalScore = MAX_SCORE;
    else if (finalScore < 0) finalScore = -MAX_SCORE;
    else return 0;

    finalScore = (iamwhite ? finalScore : -finalScore);
    return finalScore;
}

AwardType evaluate(Node &node) {
    AwardType award = 0;

    award += weightedDeskEval(node);
    //award += 3 * mobilityEval(node);

    return award;
}

#endif // _EVALUATE_H_


/*
it is not good enough. The number of disks is particularly useless - although it is the goal of the game to collect as many as possible, the count on any move except for the last one is rather meaningless. Here are a few more things that you should take into consideration:

Counting the number of moves gives you a measure of immediate mobility; everything else being equal, situations when you can make a move that opens up more other moves should be favored. You need to measure the potential mobility as well - the number of opponent's disks next to an open space.
X squares - B2, B7, G2, and G7. Placing your disk there early almost certainly gives away the adjacent corner, so your heuristic should give them high negative weight, at least in the first 40 moves
C squares - A2, A7, B1, G1, H2, H7, B8, and G8. They offer the opponent access to corners, so their value should be different from that of other squares, at least when the edge has fewer than five disks
You can read a relatively short description of the strategy used in building a relatively strong (in the sense of its ability to beat human novices) reversi applet here.

 */