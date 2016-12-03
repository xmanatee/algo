#ifndef _LINKCUTFLOWBLOCKER_H_
#define _LINKCUTFLOWBLOCKER_H_

#include <vector>
#include <unordered_set>

#include "graph/net.h"
#include "linkcut/linkcut.h"
#include "linkcut/nodeproperties.h"
#include "graph/flowblocker.h"


class LinkCutFlowBlocker : public FlowBlocker {
private:
    typedef std::unordered_set<unsigned int> Set;
    std::vector<Net::EdgeIterator> edgesIterator;
    std::vector<Net::EdgeIterator> edgesContainerEnd;
    std::vector<Set> inEdges;
    LinkCut<MinProperty> linkCut;
    unsigned int s, t;
    long long flow;

    void safeDelete(unsigned int from);

    void pushAndCut(Net::EdgeType *edge);

    void elink(Net::EdgeType *edge);

public:
    LinkCutFlowBlocker();
    virtual void processMaxFlow(Net* _net, unsigned int _s, unsigned int _t);

    long long getFlow();

};

#endif
