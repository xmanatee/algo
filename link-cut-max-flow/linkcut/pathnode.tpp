#ifndef _PATHNODE_TPP_
#define _PATHNODE_TPP_

#include "pathnode.h"

template<typename T>
PathNode<T>::PathNode(void): SplayNode(), id(pathNodeNumber++), dashedEdge(NULL), property(new T()) {}

template<typename T>
PathNode<T>::PathNode(long long _value): SplayNode(), id(pathNodeNumber++), dashedEdge(NULL), property(new T(_value)) {}

template<typename T>
unsigned int PathNode<T>::pathNodeNumber = 0;

template<typename T>
void PathNode<T>::init() {
    pathNodeNumber = 0;
}

//======= CASTERS ========

template<typename T>
PathNode<T>* PathNode<T>::getParent() {
    return static_cast<PathNode<T>*>(Node::getParent());
}

template<typename T>
PathNode<T>* PathNode<T>::getRight() {
    return static_cast<PathNode<T>*>(Node::getRight());
}

template<typename T>
PathNode<T>* PathNode<T>::getLeft() {
    return static_cast<PathNode<T>*>(Node::getLeft());
}

template<typename T>
PathNode<T>* PathNode<T>::cutLeft() {
    return static_cast<PathNode<T>*>(Node::cutLeft());
}

template<typename T>
PathNode<T>* PathNode<T>::cutRight() {
    return static_cast<PathNode<T>*>(Node::cutRight());
}
/*
template<typename T>
PathNode<T>* PathNode<T>::getRoot() {
    return static_cast<PathNode<T>*>(Node::getRoot());
}
*/
template<typename T>
PathNode<T>* PathNode<T>::getLeftest() {
    return static_cast<PathNode<T>*>(Node::getLeftest());
}

template<typename T>
PathNode<T>* PathNode<T>::getRightest() {
    return static_cast<PathNode<T>*>(Node::getRightest());
}

//======== END OF CASTERS ========


template<typename T>
PathNode<T>* PathNode<T>::getDashedEdge() {
    return dashedEdge;
}


template<typename T>
void PathNode<T>::setDashedEdge(PathNode<T>* pnode) {
    dashedEdge = pnode;
}


template<typename T>
T* PathNode<T>::getProperty() {
    return property;
}


template<typename T>
unsigned int PathNode<T>::getId() {
    return id;
}

template<typename T>
void PathNode<T>::update() {
    SplayNode::update();
    this->getProperty()->update(getLeft(), getRight());
}


template<typename T>
void PathNode<T>::push() {
//    SplayNode::push();
    if (reversed) {
        reversed = false;
        if (left) {
            getLeft()->reverse();
        }
        if (right) {
            getRight()->reverse();
        }
    }
    this->getProperty()->push(getLeft(), getRight());
}


template<typename T>
void PathNode<T>::reverse() {
    reversed ^= true;
    Node *temp = left;
    left = right;
    right = temp;
}


template<typename T>
T* getSegmentProperty(PathNode<T>* root, unsigned int l, unsigned int r, PathNode<T>*& newRoot) {
    PathNode<T> *leftRoot, *middleRoot, *rightRoot;
    split(r, root, leftRoot, rightRoot);
    split(l - 1, leftRoot, leftRoot, middleRoot);
    T* ans = middleRoot->getProperty();
    merge(leftRoot, middleRoot, leftRoot);
    merge(leftRoot, rightRoot, leftRoot);
    newRoot = leftRoot;
    return ans;
}



template<typename T>
std::ostream& operator << (std::ostream& out, PathNode<T> *pnode) {
    if (!pnode) {
        out << "n";
        return out;
    }
    out << "( " << pnode->getLeft() << "[";
    out << pnode->getId() << ";";
    out << pnode->getProperty() << ";";
    pnode->getDashedEdge() ? out << pnode->getDashedEdge()->getId() << ";" : out << "x;";
    out << "]" << pnode->getRight() << " )";
}


#endif // _PATHNODE_TPP_