#ifndef _NODE_CPP_
#define _NODE_CPP_

#include "node.h"

Node::Node(): parent(NULL), left(NULL), right(NULL) {}

Node::Node(Node* leftTree, Node* rightTree) {
    linkToLeft(leftTree);
    linkToRight(rightTree);
    update();
    parent = this;
}


bool Node::isLeft() {
    if (!parent) return false;
    return (parent->left == this);
}


bool Node::isRight() {
    if (!parent) return false;
    return (parent->right == this);
}


bool Node::isRoot() {
    return (!parent);
}


Node* Node::getParent() {
    return parent;
}


Node* Node::getRight() {
    return right;
}


Node* Node::getLeft() {
    return left;
}


Node* Node::cutLeft() {
    //push();
    Node* ans = left;
    left = NULL;
    if (ans) {
        ans->sudoSu();
    }
    //update();
    return ans;
}


Node* Node::cutRight() {
    //push();
    Node* ans = right;
    right = NULL;
    if (ans) {
        ans->sudoSu();
    }
    //update();
    return ans;
}


void Node::sudoSu() {
    parent = NULL;
}


void Node::makeRoot() {
    if (isRoot()) {
        return;
    }
    if (isLeft()) {
        parent->cutLeft();
    }
    else {
        parent->cutRight();
    }
    sudoSu();
}


void Node::linkToLeft(Node* pnode) {
    if (pnode) {
        pnode->parent = this;
    }
    left = pnode;
    //update();
}


void Node::linkToRight(Node* pnode) {
    if (pnode) {
        pnode->parent = this;
    }
    right = pnode;
    //update();
}

Node* Node::getRightest() {
    Node* pnode = this;
    pnode->push();
    Node* right = this->right;
    while (right) {
        right->push();
        pnode = right;
        right = pnode->getRight();
    }
    return pnode;
}


Node* Node::getLeftest() {
    Node* pnode = this;
    pnode->push();
    Node* left = this->left;
    while (left) {
        pnode->push();
        pnode = left;
        left = pnode->getLeft();
    }
    return pnode;
}

#endif // _NODE_CPP_
