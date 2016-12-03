#ifndef _FLOWBLOCKER_H_
#define _FLOWBLOCKER_H_

#include "net.h"

class FlowBlocker {
public:
    virtual void processMaxFlow(Net *_net, unsigned int _s, unsigned int _t) = 0;

    virtual long long getFlow() = 0;
};

#endif // _FLOWBLOCKER_H_
