#ifndef _PATHNODE_H_
#define _PATHNODE_H_

#include <iostream>
#include <algorithm>
#include <vector>

#include "splaynode.h"
#include "splaytree.h"

template<typename T>
class PathNode;

template<typename T>
class PathNode : public SplayNode {
private:
    static unsigned int pathNodeNumber;
    unsigned int id;
    PathNode* dashedEdge;
    bool reversed;
    T* property;
public:
    virtual PathNode* getParent();
    virtual PathNode* getRight();
    virtual PathNode* getLeft();

    virtual PathNode* cutLeft();
    virtual PathNode* cutRight();

    //virtual PathNode* getRoot();
    virtual PathNode* getLeftest();
    virtual PathNode* getRightest();

    PathNode(void);
    PathNode(long long _value);
    virtual void update();
    virtual void push();
    void reverse();
    PathNode* getDashedEdge();
    void setDashedEdge(PathNode *pnode);

    T* getProperty();

    unsigned int getId();
    static void init();
};

#include "pathnode.tpp"

#endif
