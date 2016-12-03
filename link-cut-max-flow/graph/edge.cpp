#ifndef _EDGE_CPP_
#define _EDGE_CPP_

#include "edge.h"

Edge::Edge(unsigned int _from, unsigned int _to): from(_from), to(_to) {}


unsigned int Edge::getFrom() {
    return from;
}


unsigned int Edge::getTo() {
    return to;
}

#endif // _EDGE_CPP
