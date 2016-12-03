#ifndef _MTDF_H_
#define _MTDF_H_

#include <map>

#include "common.h"
#include "reversinode.h"
#include "ttable.h"
#include "sortactions.h"

class Node;
AwardType terminalNodeEvaluate(Node &node);
AwardType evaluate(Node &node);
bool isMaxNode(const Node &node);

class AlphaBetaPrunner {
public:
    int nodeCounter = 0;
#ifndef NO_TTABLES
    TranspositionTable table;
#endif
//    static map<Node, AwardType> evaluationMap;
    Action firstAction;

    AlphaBetaPrunner() {}

    AwardType AlphaBetaWM(Node &node, AwardType alpha, AwardType beta, int d) {
        nodeCounter = 1;
#ifdef AB_DEBUG
        cerr << "AB-run with (" << alpha << " , " << beta << ")\n";
#endif

#ifndef NO_TTABLES
        Memory mem;
        if (table.retrieve(node, mem)) {
            if (mem.alpha >= beta) return mem.alpha;
            if (mem.beta <= alpha) return mem.beta;
            alpha = MAX(alpha, mem.alpha);
            beta = MIN(beta, mem.beta);
        }
#endif

        AwardType g;
        vector<Action> actions = getValidActions(node);
        if (actions.size() == 0) {
            g = terminalNodeEvaluate(node);
//            evaluationMap[node] = g;
        } else {
#ifndef NO_AORDERING
            if (d != 1) sortActions(node, actions);
#endif
            int c = 0;

            g = -INF_AWARD;
            AwardType a = alpha;

            while ((g < beta) && (c != actions.size())) {
                if (timer.timesUp()) break;
                Node child = actions[c].apply(node);
                AwardType deeperAns = AlphaBetaWMLight(child, a, beta, d - 1);
                if (deeperAns > g) {
                    g = deeperAns;
                    firstAction = actions[c];
                }
                a = MAX(a, g);
                ++c;
//                cerr << "> c=" << c << ".g=" << g << ".beta=" << beta << ".a=" << a << "\n";
            }
        }


#ifndef NO_TTABLES
        if (g <= alpha) table.storeBeta(node, g);
        if ((alpha < g) && (g < beta)) table.store(node, g, g);
        if (g >= beta) table.storeAlpha(node, g);
#endif

#ifdef AB_DEBUG
        cerr << "=========================\ndepth: " << d << ". g: " << g << ". k: " << actions.size() << ". " << node << "\n";
#endif

        return g;
    }

    AwardType AlphaBetaWMLight(Node &node, AwardType alpha, AwardType beta, int d) {
        ++nodeCounter;

#ifndef NO_TTABLES
        Memory mem;
        if (table.retrieve(node, mem)) {
            if (mem.alpha >= beta) return mem.alpha;
            if (mem.beta <= alpha) return mem.beta;
            alpha = MAX(alpha, mem.alpha);
            beta = MIN(beta, mem.beta);
        }
#endif

        AwardType g;
        if (d == 0) {
            g = evaluate(node);
//            evaluationMap[node] = g;
        } else {
            vector<Action> actions = getValidActions(node);
            if (actions.size() == 0) {
                g = terminalNodeEvaluate(node);
//                evaluationMap[node] = g;
            } else {
#ifndef NO_AORDERING
                if (d != 1) sortActions(node, actions);
#endif

                int c = 0;
                if (isMaxNode(node)) {
                    g = -INF_AWARD;
                    AwardType a = alpha; /* save original alpha value */

                    while ((g < beta) && (c != actions.size())) {
                        if (timer.timesUp()) break;
                        Node child = actions[c].apply(node);
                        AwardType deeperAns = AlphaBetaWMLight(child, a, beta, d - 1);
                        if (deeperAns > g) {
                            g = deeperAns;
                        }
                        a = MAX(a, g);
                        ++c;
                    }
                } else {
                    g = +INF_AWARD;
                    AwardType b = beta; /* save original beta value */

                    while ((g > alpha) && (c != actions.size())) {
                        if (timer.timesUp()) break;
                        Node child = actions[c].apply(node);
                        AwardType deeperAns = AlphaBetaWMLight(child, alpha, b, d - 1);
                        if (deeperAns < g) {
                            g = deeperAns;
                        }
                        b = MIN(b, g);
                        ++c;
                    }
                }
            }
        }

#ifndef NO_TTABLES
        if (g <= alpha) table.storeBeta(node, g);
        if ((alpha < g) && (g < beta)) table.store(node, g, g);
        if (g >= beta) table.storeAlpha(node, g);
#endif

#ifdef AB_DEBUG
        cerr << "=========================\ndepth: " << d << ". g: " << g << ". " << node << "\n";
#endif
        return g;
    }

} treeSearcher;

AwardType mtdf(Node &root, AwardType f, int d, Action &bestAction) {
    AwardType g = f;
    AwardType upperbound = +INF_AWARD;
    AwardType lowerbound = -INF_AWARD;

    while (lowerbound < upperbound) {
#ifndef NO_TTABLES
        treeSearcher.table.clear();
#endif
        AwardType beta;
        if (g == lowerbound) {
            beta = g + 1;
        } else {
            beta = g;
        }
        g = treeSearcher.AlphaBetaWM(root, beta - 1, beta, d);
        if (timer.timesUp()) {
            break;
        }
        if (g < beta) {
            upperbound = g;
        } else {
            lowerbound = g;
        }
    }

    if (timer.timesUp()) {
        return 0;
    }

    bestAction = treeSearcher.firstAction;
#ifdef AB_DEBUG
    cerr << "MTDF::G: " << g << "\n";
#endif

    return g;
}

const int MIN_SEARCH_DEPTH = 1;
const int MAX_SEARCH_DEPTH = 20;
const int DEEPENING_STEP = 1;
AwardType iterativeDeepening(Node &root, AwardType initFirstGuess, Action &bestAction) {
    int d;
    AwardType firstguess = initFirstGuess;
    AwardType mtdfAnswer;
    for (d = MIN_SEARCH_DEPTH; d <= MAX_SEARCH_DEPTH; d += DEEPENING_STEP) {
        mtdfAnswer = mtdf(root, firstguess, d, bestAction);
        if (timer.timesUp()) {
            break;
        } else {
            firstguess = mtdfAnswer;
        }
    }

#ifdef IT_DEBUG
    cerr << "\tfinal search depth : " << d << "\n";
    cerr << "\t" << timer.getPastTimeSec() << "sec past" << "\n";
#endif

    return firstguess;
}

#endif // _MTDF_H_