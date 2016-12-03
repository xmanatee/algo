#ifndef _SORTACTIONS_H_
#define _SORTACTIONS_H_

#include "common.h"
#include <algorithm>
#include "reversinode.h"
#include "action.h"

AwardType evaluate(Node &node);
bool isMaxNode(const Node &node);


Node *node4comparision;

bool compareAscEval(const Action &a, const Action &b) {
    Node node = a.apply(*node4comparision);
    AwardType ansA = evaluate(node);
    //ansA = evaluationMap[node];

    node = b.apply(*node4comparision);
    //ansB = evaluationMap[node];
    AwardType ansB = ansB = evaluate(node);

    return ansA < ansB;
};

bool compareDescEval(const Action &a, const Action &b) {
    Node node = a.apply(*node4comparision);
    AwardType ansA = evaluate(node);
    //ansA = evaluationMap[node];

    node = b.apply(*node4comparision);
    //ansB = evaluationMap[node];
    AwardType ansB = ansB = evaluate(node);

    return ansA > ansB;
};

void sortActions(Node &node, vector<Action> &actions) {
    node4comparision = &node;
    if (isMaxNode(node)) {
        sort(actions.begin(), actions.end(), compareDescEval);
    } else {
        sort(actions.begin(), actions.end(), compareAscEval);
    }
}

#endif // _SORTACTIONS_H_