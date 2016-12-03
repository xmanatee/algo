#ifndef _SPLAYNODE_CPP_
#define _SPLAYNODE_CPP_

#include "splaynode.h"

const unsigned int SplayNode::MAX_KEY = (const unsigned int) (1e9 + 7);

SplayNode::SplayNode(): Node(), key(1) { }

SplayNode::SplayNode(SplayNode* left, SplayNode* right): Node(left, right), key(1) { }


//======= CASTERS ========

SplayNode* SplayNode::getParent() {
    return static_cast<SplayNode*>(Node::getParent());
}

SplayNode* SplayNode::getRight() {
    return static_cast<SplayNode*>(Node::getRight());
}

SplayNode* SplayNode::getLeft() {
    return static_cast<SplayNode*>(Node::getLeft());
}

SplayNode* SplayNode::cutLeft() {
    return static_cast<SplayNode*>(Node::cutLeft());
}

SplayNode* SplayNode::cutRight() {
    return static_cast<SplayNode*>(Node::cutRight());
}

SplayNode* SplayNode::getLeftest() {
    return static_cast<SplayNode*>(Node::getLeftest());
}

SplayNode* SplayNode::getRightest() {
    return static_cast<SplayNode*>(Node::getRightest());
}

//======== END OF CASTERS ========


void SplayNode::update() {
    key = getKey(getLeft()) + getKey(getRight()) + 1;
}

void SplayNode::push() {}

unsigned int getKey(SplayNode* pnode) {
    return (pnode ? pnode->key : 0);
}


unsigned int getPos(SplayNode* pnode) {
    return getKey(pnode->getLeft()) + 1;
}


#endif // _SPLAYNODE_CPP_
