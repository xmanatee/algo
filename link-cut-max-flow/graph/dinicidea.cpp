#ifndef _DINICIDEA_CPP_
#define _DINICIDEA_CPP_

#include "dinicidea.h"

Net* DinicIdea::buildLayeredNet(Net* net, std::vector<int> &classes) {
    unsigned int n = net -> size();
    Net *layeredNet = new Net(n);
    for (unsigned int i = 0; i < n; ++i) {
        Net::EdgeIterator itEnd = net->getEdgesFrom(i).end();
        for (Net::EdgeIterator it = net->getEdgesFrom(i).begin(); it != itEnd; ++it) {
            unsigned int from = (*it) -> getFrom();
            unsigned int to = (*it) -> getTo();
            if (classes[from] == Bfs<Net>::NOT_VISITED || classes[to] == Bfs<Net>::NOT_VISITED) {
                continue;
            }
            if (classes[from] + 1 == classes[to]) {
                layeredNet -> addEdge((*it));
            }

        }
    }
    return layeredNet;
}


DinicIdea::DinicIdea(Net* net, FlowBlocker *flowBlocker, unsigned int s, unsigned int t) {
    flow = 0;
    while (true) {
        Net *residualNet = net -> copyWithResidualGreaterThan(0);
        Bfs<Net> bfs(residualNet, s, t);

        if (!bfs.gotTarget()) {
            break;
        }
        Net* layeredNet = buildLayeredNet(residualNet, bfs.getDistances());

        flowBlocker->processMaxFlow(layeredNet, s, t);
        flow += flowBlocker->getFlow();

        delete residualNet;
        delete layeredNet;
    }
}


long long DinicIdea::getFlowValue() {
    return flow;
}

#endif // _DINICIDEA_H_
