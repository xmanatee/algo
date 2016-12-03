#include <iostream>

int debug_exposeCalls = 0;

#include "graph/net.h"
#include "graph/dinicflowblocker.h"
#include "linkcutflowblocker.h"
#include "graph/dinicidea.h"

int main() {
    Net *net = new Net();
    readNet(net);
    unsigned int n = net->size();
    //writeNet(net);

    unsigned int s = 0;
    unsigned int t = n - 1;

    long long flow = 0;

#ifndef DINICBLOCK
    LinkCutFlowBlocker *flowBlocker = new LinkCutFlowBlocker();
/*
#else
    DinicFlowBlocker *flowBlocker = new DinicFlowBlocker();
    */
#endif


/*
#ifdef SCALING
    long long delta = net->getMaxCapacity();
    while (true) {
        Net *scaledNet = net->copyWithResidualGreaterThan(delta - 1);
        DinicIdea dinic(scaledNet, flowBlocker, s, t);
        flow += dinic.getFlowValue();
        delete scaledNet;
        delta /= 2;
        if (delta == 0) {
            break;
        }
    }
#else
*/
    DinicIdea dinic(net, flowBlocker, s, t);
    flow += dinic.getFlowValue();
//#endif

    std::cout << flow << "\n";

    return 0;
}
