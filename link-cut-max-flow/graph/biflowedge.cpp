#ifndef _BIFLOWEDGE_CPP_
#define _BIFLOWEDGE_CPP_

#include "biflowedge.h"

BiFlowEdge* BiFlowEdge::getBackEdge() {
    return backEdge;
}


void BiFlowEdge::setBackEdge(BiFlowEdge* _backEdge) {
    backEdge = _backEdge;
}


void BiFlowEdge::push(long long d) {
    FlowEdge::push(d);
    backEdge->FlowEdge::push(-d);
}


void linkBiFlowEdges(BiFlowEdge* a, BiFlowEdge* b) {
    a->setBackEdge(b);
    b->setBackEdge(a);
}

#endif

