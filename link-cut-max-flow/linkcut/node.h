#ifndef _NODE_H_
#define _NODE_H_

#include <cstdlib>

class Node;

class Node {
protected:
    Node *parent;
    Node *left;
    Node *right;
    void sudoSu();
public:
    Node();
    Node(Node* leftTree, Node* rightTree);
    bool isLeft();
    bool isRight();
    bool isRoot();
    virtual Node* getParent();
    virtual Node* getRight();
    virtual Node* getLeft();

    virtual Node* cutLeft();
    virtual Node* cutRight();

    virtual Node* getLeftest();
    virtual Node* getRightest();

    void makeRoot();
    void linkToLeft(Node* whom);
    void linkToRight(Node* whom);

    virtual void push() {}
    virtual void update() {};
    
};

#endif // _NODE_H_
