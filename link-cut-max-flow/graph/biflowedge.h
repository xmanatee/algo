#ifndef _BIFLOWEDGE_H_
#define _BIFLOWEDGE_H_

#include <cstdlib>

#include "flowedge.h"

//Edge with Weight and Back-edge-links
class BiFlowEdge;


class BiFlowEdge: public FlowEdge {
private:
    BiFlowEdge* backEdge;

public:
    BiFlowEdge(unsigned int _from, unsigned int _to, long long _capacity): FlowEdge(_from, _to, _capacity), backEdge(NULL) {}

    BiFlowEdge* getBackEdge();

    void setBackEdge(BiFlowEdge* _backEdge);

    void push(long long d);
};


void linkBiFlowEdges(BiFlowEdge* a, BiFlowEdge* b);

#endif

