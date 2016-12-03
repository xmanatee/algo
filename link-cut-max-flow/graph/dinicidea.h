#ifndef _DINICIDEA_H_
#define _DINICIDEA_H_

#include <vector>

#include "bfs.h"
#include "net.h"

#include "flowblocker.h"

class DinicIdea {
private:
    long long flow;
public:
    DinicIdea(Net* net, FlowBlocker *flowBlocker, unsigned int s, unsigned int t);

    static Net* buildLayeredNet(Net* net, std::vector<int> &classes);

    long long getFlowValue();
};

#endif // _DINICIDEA_H_
