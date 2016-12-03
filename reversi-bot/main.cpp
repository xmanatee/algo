#include <iostream>
#include <vector>

using namespace std;

bool iamwhite;

#define NO_TTABLE

#include "common.h"
#include "reversinode.h"
#include "action.h"
#include "mtdf.h"
#include "evaluate.h"

bool isMaxNode(const Node &node) {
    return (!iamwhite ^ node.whitesTurn);
}

int main() {

    string initStr;
    while (true) {
        cin >> initStr;
        if (initStr != "init") {
            continue;
        }
        cin >> initStr;
        if (initStr == "white") {
            iamwhite = true;
        } else if (initStr == "black") {
            iamwhite = false;
        }
        break;
    }

    Node game = getStartingNode();
    AwardType firstGuess = 0;
    string moveStr;
    Action action;
    while (true) {
        if (isGameOver(game)) {
            return 0;
        }

        if (game.whitesTurn ^ iamwhite) {
            cin >> moveStr >> action;
            game = action.apply(game);
        } else {
            cin >> moveStr;
            timer.init();
#ifdef NO_MTDF
            firstGuess = treeSearcher.AlphaBetaWM(game, -INF_AWARD, +INF_AWARD, 6);
            action = treeSearcher.firstAction;
#else
            firstGuess = iterativeDeepening(game, firstGuess, action);
#endif
            game = action.apply(game);
            cout << "move " << action << "\n";
        }
    }
}
