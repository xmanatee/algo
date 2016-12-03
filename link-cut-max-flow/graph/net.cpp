#ifndef _NET_CPP_
#define _NET_CPP_

#include "net.h"

Net::Net(void): Graph() {}
Net::Net(unsigned int _n): Graph(_n) {}


void Net::addWiseEdge(BiFlowEdge* edge) {
    unsigned int from = edge->getFrom();
    unsigned int to = edge->getTo();
    BiFlowEdge* pbackEdge = new BiFlowEdge(to, from, 0);
    linkBiFlowEdges(edge, pbackEdge);
    Graph::addEdge(edge);
    Graph::addEdge(pbackEdge);
}

// constructs net with edges where ResidualCapacity >= delta
Net* Net::copyWithResidualGreaterThan(long long delta) {
    Net* newNet = new Net(size());
    unsigned int n = size();
    for (unsigned int i = 0; i < n; ++i) {
        for (Net::EdgeIterator it = edges[i].begin(); it != edges[i].end(); ++it) {
            if ((*it) -> getResidualCapacity() > delta) {
                newNet -> addEdge(*it);
            }
        }
    }
    return newNet;
}

const long long LL_INF = (const long long) 1e18 + 7;
long long Net::getMaxCapacity() {
    unsigned int n = size();
    long long maxCapacity = -LL_INF;
    for (unsigned int i = 0; i < n; ++i) {
        for (Net::EdgeIterator it = edges[i].begin(); it != edges[i].end(); ++it) {
            if ((*it)->getCapacity() > maxCapacity) {
                maxCapacity = (*it)->getCapacity();
            }
        }
    }
    return maxCapacity;
}

void readNet(Net *net) {
    unsigned int from, to;
    long long c;
    unsigned int n = 0, m = 0;
    std::cin >> n >> m;
    net->clear();
    net->init(n);
    for (unsigned int i = 0; i < m; ++i) {
        std::cin >> from >> to >> c;
        net->addWiseEdge(new BiFlowEdge(--from, --to, c));
    }
}

void writeNet(Net *net) {
    unsigned int n = net->size();
    std::cout << n << " vertices; X edges;\n";
    for (unsigned int i = 0; i < n; ++i) {
        std::cout << i << " : ";
        Net::EdgeIterator itEnd = net->getEdgesFrom(i).end();
        for (Net::EdgeIterator it = net->getEdgesFrom(i).begin(); it != itEnd; ++it) {
            std::cout << "<" << (*it)->getFrom() << ","
            << (*it)->getTo() << ","
            << (*it)->getCapacity() << ","
            << (*it)->getFlow() << ">"
            << ", ";
        }
        std::cout << "\n";
    }
}

#endif // _NET_CPP_
