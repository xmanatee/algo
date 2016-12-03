#ifndef _DINICFLOWBLOCKER_CPP_
#define _DINICFLOWBLOCKER_CPP_

#include "dinicflowblocker.h"

DinicFlowBlocker::DinicFlowBlocker() {}

void DinicFlowBlocker::processMaxFlow(Net *_net, unsigned int _s, unsigned int _t) {
    net = _net;
    flow = 0;
    edgesIterator.resize(net->size());
    edgesContainerEnd.resize(net->size());
    s = _s;
    t = _t;
    while (true) {
        if (!dinicDfs()) {
            break;
        }
        long long minCapacity = (long long int) (1e18 + 7);
        for (unsigned int i = 0; i < path.size(); ++i) {
            long long capacity = path[i]->getResidualCapacity();
            if (capacity < minCapacity) {
                minCapacity = capacity;
            }
        }
        for (unsigned int i = 0; i < path.size(); ++i) {
            path[i]->push(minCapacity);
        }
        flow += minCapacity;
        path.clear();
    }
}

long long DinicFlowBlocker::getFlow() {
    return flow;
}

bool DinicFlowBlocker::dinicDfs() {
    for (unsigned int i = 0; i < net->size(); ++i) {
        edgesIterator[i] = net->getEdgesFrom(i).begin();
        edgesContainerEnd[i] = net->getEdgesFrom(i).end();
    }
    bool foundPath = false;
    if (findPath(s)) {
        foundPath = true;
    }
    return foundPath;
}

bool DinicFlowBlocker::findPath(unsigned int currentVertice) {
    if (currentVertice == t) {
        return true;
    }
    Net::EdgeIterator it(edgesIterator[currentVertice]);
    Net::EdgeIterator endIt(edgesContainerEnd[currentVertice]);
    while (it != endIt) {
        unsigned int to = (*it)->getTo();
        long long capacity = (*it)->getResidualCapacity();
        if (capacity == 0) {
            ++it;
            continue;
        }
        path.push_back((*it));
        if (findPath(to)) {
            return true;
        }
        path.pop_back();
        ++it;
    }
    return false;
}

#endif // _DINICFLOWBLOCKER_H_
