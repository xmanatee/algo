#ifndef _SPLAYNODE_H_
#define _SPLAYNODE_H_

#include <iostream>
#include <cstdlib>
#include <vector>

#include "node.h"



class SplayNode;

class SplayNode: public Node {
private:
    static const unsigned int MAX_KEY;
    unsigned int key;
public:
    SplayNode();
    SplayNode(SplayNode* left, SplayNode* right);

    virtual SplayNode* getParent();
    virtual SplayNode* getRight();
    virtual SplayNode* getLeft();

    virtual SplayNode* cutLeft();
    virtual SplayNode* cutRight();

    //virtual SplayNode* getRoot();
    virtual SplayNode* getLeftest();
    virtual SplayNode* getRightest();

    virtual void update();
    virtual void push();

    friend unsigned int getKey(SplayNode* pnode);
};

unsigned int getKey(SplayNode* pnode);

unsigned int getPos(SplayNode* pnode);

#endif // _SPLAY_H_
