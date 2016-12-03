#include <iostream>

#include "graph/bfs.cpp"

#include "graph/net.h"

#include "linkcutflowblocker.h"
#include "graph/dinicidea.h"


int main() {
    Net *net = new Net(5);
    readNet(*net);
    int n = net->size();

    int s = 0;
    int t = n - 1;

    std::cerr << "Initial Net : \n";
    writeNet(*net);
    std::cerr << "\n";

    Bfs<Net> bfs(*net, s, t);
    if (!bfs.gotTarget()) {
        return 0;
    }
    Net* layeredNet = DinicIdea::buildLayeredNet(net, bfs.getDistances());

    std::cerr << ":ayered Net : \n";
    writeNet(*layeredNet);
    std::cerr << "\n";


    int flow = FlowBlocker(layeredNet, s, t).getFlow();

    std::cerr << "Residual Net : \n";
    writeNet(*net);

    std::cout << flow << "\n";

    return 0;
}
