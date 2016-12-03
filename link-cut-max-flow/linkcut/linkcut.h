#ifndef _LINKCUT_H_
#define _LINKCUT_H_

#include <cstdlib>
#include <vector>

#include "pathnode.h"
#include "splaytree.h"

template<typename T>
class LinkCut {
private:
    unsigned int size;
    std::vector<PathNode<T>*> nodes;
public:
    LinkCut(void);
    void resize(unsigned int n);
    void track(PathNode<T>* pnode);
    void print();
    PathNode<T> *getKth(unsigned int k);
};

template<typename T>
LinkCut<T>::LinkCut(void): size(0) {}

template<typename T>
void LinkCut<T>::resize(unsigned int n) {
    size = n;
    for (unsigned int i = 0; i < n; ++i) {
        nodes.push_back(new PathNode<T>());
    }
}


template<typename T>
void LinkCut<T>::track(PathNode<T> *node) {
    nodes.push_back(node);
}


template<typename T>
void LinkCut<T>::print() {
    std::cerr << "Your LinkCut : \n";
    for (typename std::vector<PathNode<T>*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        if ((*it)->isRoot()) {
            std::cerr << (*it) << "\n";
        }
    }
}


template<typename T>
PathNode<T>* LinkCut<T>::getKth(unsigned int k) {
    return nodes[k];
}


template<typename T>
void expose(PathNode<T>* pnode) {
    upperPush(pnode);
    splay(pnode);
    PathNode<T>* v = pnode->getLeftest();
    splay(v);

    while (v->getDashedEdge()) {
        PathNode<T>* parent = v->getDashedEdge();
        upperPush(parent);
        splay(parent);
        PathNode<T>* rightRoot = parent->cutRight();
        parent->linkToRight(v);
        if (rightRoot) {
            rightRoot = rightRoot->getLeftest();
            splay(rightRoot);
            rightRoot->setDashedEdge(parent);
        }

        v = parent->getLeftest();
        splay(v);
    }

    //upperPush(pnode);
    splay(pnode);
}

template<typename T>
void modifyOnPathToRoot(PathNode<T>* pnode, long long d) {
    expose(pnode);
    PathNode<T> *right = pnode->cutRight();
    pnode->getProperty()->receiveDelta(d);
    pnode->linkToRight(right);
}


template<typename T>
void revert(PathNode<T>* v) {
    expose(v);
    if (!v->getLeft()) {
        return;
    }
    PathNode<T> *leftRoot, *rightRoot;
    rsplit(v, leftRoot, rightRoot);
    // Here I probably need to reverse, but not this time
    leftRoot->reverse();
    // It's actually empty
    leftRoot = leftRoot->getLeftest();
    splay(leftRoot);
    leftRoot->setDashedEdge(rightRoot);
    rightRoot->setDashedEdge(NULL);
}

// links right to left
template<typename T>
void link(PathNode<T>* v, PathNode<T>* u) {
    revert(u);
    u->setDashedEdge(v);
    u->getProperty()->reset();
}

// links right to left
template<typename T>
void link(PathNode<T>* v, PathNode<T>* u, long long c) {
    revert(u);
    u->setDashedEdge(v);
    u->getProperty()->reset(c);
}


// u must be closer to the root
template<typename T>
void cut(PathNode<T>* u, PathNode<T>* v) {
    revert(u);
    expose(v);
    PathNode<T> *leftRoot, *rightRoot;
    rsplit(v, leftRoot, rightRoot);
    rightRoot = rightRoot->getLeftest();
    splay(rightRoot);
    rightRoot->setDashedEdge(NULL);
    rightRoot->getProperty()->reset();
    rightRoot->update();
}

#endif // _LINKCUT_H_
