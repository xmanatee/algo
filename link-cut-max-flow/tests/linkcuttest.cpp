#include <iostream>


#include "../linkcut/linkcut.h"
#include "../linkcut/nodeproperties.h"

int main() {
    unsigned int n, m;
    std::cin >> n >> m;
    LinkCut<MinProperty> lc;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        PathNode<MinProperty> *newNode = new PathNode<MinProperty>();
        lc.track(newNode);
        std::cerr << newNode;
    }

    for (int i = 0; i < m; ++i) {
        int q, l, r;
        std::cin >> q >> l >> r;
        PathNode<MinProperty>* leftNode = lc.getKth(l);
        PathNode<MinProperty>* rightNode = lc.getKth(r);
        if (q == 1) {
            link(leftNode, rightNode);
        }
        if (q == 2) {
            cut(leftNode, rightNode);
        }
        std::cerr << "\n[" << q << "," << l << "," << r << "] : "; lc.print(); std::cerr << "\n";
    }

    return 0;
}

