#ifndef _DINICFLOWBLOCKER_H_
#define _DINICFLOWBLOCKER_H_

#include <vector>

#include "net.h"
#include "flowblocker.h"



class DinicFlowBlocker;


class DinicFlowBlocker : public FlowBlocker {
private:
    long long flow;

    std::vector<Net::EdgeIterator> edgesIterator;

    std::vector<Net::EdgeIterator> edgesContainerEnd;

    std::vector<Net::EdgeType*> path;

    unsigned int s, t;

    Net* net;

    //std::vector<Net::EdgeType>* stack;

    //bool foundPath;

public:
    DinicFlowBlocker();
    virtual void processMaxFlow(Net *_net, unsigned int _s, unsigned int _t);

    virtual long long getFlow();

    bool dinicDfs();

    bool findPath(unsigned int currentVertice);

};

#endif // _DINICFLOWBLOCKER_H_
