#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "flowedge.h"

FlowEdge::FlowEdge(unsigned int _from, unsigned int _to, long long _c): Edge(_from, _to), flow(0), capacity(_c) {}


long long FlowEdge::getCapacity() {
    return capacity;
}


long long FlowEdge::getFlow() {
    return flow;
}


long long FlowEdge::getResidualCapacity() {
    return capacity - flow;
}


void FlowEdge::push(long long d) {
    flow += d;
}

#endif
