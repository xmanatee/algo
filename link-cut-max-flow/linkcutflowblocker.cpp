#ifndef _LINKCUTFLOWBLOCKER_CPP_
#define _LINKCUTFLOWBLOCKER_CPP_

#include "linkcutflowblocker.h"

LinkCutFlowBlocker::LinkCutFlowBlocker() { }

void LinkCutFlowBlocker::processMaxFlow(Net* net, unsigned int _s, unsigned int _t) {
    edgesIterator.resize(net->size());
    edgesContainerEnd.resize(net->size());
    inEdges.resize(net->size());
    linkCut.resize(net->size());
    s = _s;
    t = _t;
    flow = 0;

    for (unsigned int i = 0; i < net->size(); ++i) {
        edgesIterator[i] = net->getEdgesFrom(i).begin();
        edgesContainerEnd[i] = net->getEdgesFrom(i).end();
        if (edgesIterator[i] != edgesContainerEnd[i]) {
            elink(*edgesIterator[i]);
        }
    }

    for (unsigned int i = 0; i < net->size(); ++i) {
        if (i == t) continue;
        if (edgesIterator[i] == edgesContainerEnd[i]) {
            safeDelete(i);
        }
    }

    PathNode<MinProperty> *sNode = linkCut.getKth(s);
    PathNode<MinProperty> *tNode = linkCut.getKth(t);

    bool can = true;
    while (can) {
        revert(tNode);
        expose(sNode);

        PathNode<MinProperty> *minHolder = findMinHolder(sNode->getLeft());
        if (compare(sNode->getProperty(), minHolder->getProperty())) {
            minHolder = sNode;
        }

        long long minValue = minHolder->getProperty()->getValue();
        modifyOnPathToRoot(sNode, -minValue);
        flow += minValue;
        unsigned int from = minHolder->getId();
        pushAndCut(*edgesIterator[from]);

        while (true) {
            ++edgesIterator[from];
            if (edgesIterator[from] == edgesContainerEnd[from]) break;
            unsigned int to = (*edgesIterator[from])->getTo();
            if (to == t) break;
            if (edgesIterator[to] != edgesContainerEnd[to]) break;
        }
        if (edgesIterator[from] == edgesContainerEnd[from]) {
            safeDelete(from);
        }
        else {
            elink(*edgesIterator[from]);
        }

        if (edgesIterator[s] == edgesContainerEnd[s]) {
            can = false;
        }
    }

    for (unsigned int i = 0; i < edgesIterator.size(); ++i) {
        if (edgesIterator[i] != edgesContainerEnd[i]) {
            pushAndCut(*edgesIterator[i]);
        }
    }
    PathNode<MinProperty>::init();
}


void LinkCutFlowBlocker::safeDelete(unsigned int from) {
    std::vector<unsigned int> row;
    row.push_back(from);
    unsigned int l = 0;
    while (l < row.size()) {
        unsigned int cur = row[l++];
        Set::iterator sit;
        while (inEdges[cur].size() > 0) {
            sit = inEdges[cur].begin();
            unsigned int inFrom = (*sit);
            Net::EdgeIterator *vit = &edgesIterator[inFrom];

            pushAndCut(**vit);

            while ((*vit != edgesContainerEnd[inFrom])
                   && ((**vit)->getTo() != t)
                   && (edgesIterator[(**vit)->getTo()] == edgesContainerEnd[(**vit)->getTo()])) {
                ++*vit;
            }
            if (*vit != edgesContainerEnd[inFrom]) {
                elink(**vit);
            }
            else {
                row.push_back(inFrom);
            }
        }
    }
}


void LinkCutFlowBlocker::pushAndCut(Net::EdgeType *edge) {
    unsigned int to = edge->getTo();
    unsigned int from = edge->getFrom();
    linkCut.getKth(from);
    expose(linkCut.getKth(from));
    long long history = linkCut.getKth(from)->getProperty()->getHistory();
    edge->push(history);

    cut(linkCut.getKth(to), linkCut.getKth(from));
    inEdges[to].erase(from);
}


void LinkCutFlowBlocker::elink(Net::EdgeType *edge) {
    unsigned int to = edge->getTo();
    unsigned int from = edge->getFrom();
    long long capacity = edge->getResidualCapacity();

    link(linkCut.getKth(to), linkCut.getKth(from), capacity);
    inEdges[to].insert(from);
}


long long LinkCutFlowBlocker::getFlow() {
    return flow;
}


#endif // _LINKCUTFLOWBLOCKER_CPP_
