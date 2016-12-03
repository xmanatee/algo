#ifndef _FLOWEDGE_H_
#define _FLOWEDGE_H_

#include "edge.h"

//Edge with Flow and Capacity left
class FlowEdge;


class FlowEdge : public Edge {
    long long flow;

    long long capacity;
public:
    FlowEdge(unsigned int _from, unsigned int _to, long long _c);

    long long getCapacity();

    long long getFlow();

    long long getResidualCapacity();

    virtual void push(long long d);

};

#endif
