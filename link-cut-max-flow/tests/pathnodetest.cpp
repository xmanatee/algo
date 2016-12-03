#include <iostream>

//#include "linkcut/pathnode.h"
//#include "linkcut/splaytree.h"
//#include "linkcut/nodeproperties.h"


void myReverse(PathNode<MinProperty> *pnode, int l, int r, PathNode<MinProperty>*& newRoot) {
    PathNode<MinProperty> *leftRoot, *middleRoot, *rightRoot;
    split(r, pnode, leftRoot, rightRoot);
    split(l - 1, leftRoot, leftRoot, middleRoot);

    //std::cerr << "reversing on " << middleRoot << "\n";
    middleRoot->reverse();

    merge(leftRoot, middleRoot, leftRoot);
    merge(leftRoot, rightRoot, newRoot);
}

int myGetMin(PathNode<MinProperty> *pnode, int l, int r, PathNode<MinProperty>*& newRoot) {
    PathNode<MinProperty> *leftRoot, *middleRoot, *rightRoot;
    split(r, pnode, leftRoot, rightRoot);
    split(l - 1, leftRoot, leftRoot, middleRoot);

    //std::cerr << "getting min on " << middleRoot << "\n";
    int ans = middleRoot->getProperty()->getMinValue();

    merge(leftRoot, middleRoot, leftRoot);
    merge(leftRoot, rightRoot, newRoot);

    return ans;
}

int main() {
    PathNode<MinProperty> *root = new PathNode<MinProperty>();
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        PathNode<MinProperty> *node = new PathNode<MinProperty>(a);
        root = add(i, root, node);
        //std::cerr << "add(" << a << ") : " << root << "\n";
    }
    delete(root -> cutRight());
    //std::cerr << "\nbuilt : " << root << "\n";


    for (int i = 0; i < m; ++i) {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q == 1) {
            myReverse(root, l, r, root);
        }
        if (q == 2) {
            std::cout << myGetMin(root, l, r, root) << "\n";
        }
        //std::cerr << "\n[" << q << "," << l << "," << r << "] : " << root << "\n";
    }


    return 0;
}

