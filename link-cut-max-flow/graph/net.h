#ifndef _NET_H_
#define _NET_H_

#include "graph.h"
#include "biflowedge.h"

class Net;

class Net : public Graph<BiFlowEdge> {
public:
    Net(void);

    Net(unsigned int _n);

    void addWiseEdge(BiFlowEdge* pedge);

    Net* copyWithResidualGreaterThan(long long delta);

    long long getMaxCapacity();

};

void readNet(Net *net);

void writeNet(Net *net);

#endif // _NET_H_
