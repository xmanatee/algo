#ifndef _SPLAYTREE_H_
#define _SPLAYTREE_H_

template<typename TNode>
void zug(TNode* pnode) {
    TNode* parent = pnode->getParent();
    bool wasLeft = pnode->isLeft();
    pnode->makeRoot();
    if (!parent->isRoot()) {
        TNode* grandParent = parent->getParent();
        if (parent->isLeft()) {
            grandParent->cutLeft();
            grandParent->linkToLeft(pnode);
        } else {
            grandParent->cutRight();
            grandParent->linkToRight(pnode);
        }
    }
    if (wasLeft) {
        TNode* childB = pnode->cutRight();
        parent->linkToLeft(childB);
        pnode->linkToRight(parent);
    }
    else {
        TNode* childB = pnode->cutLeft();
        parent->linkToRight(childB);
        pnode->linkToLeft(parent);
    }
    parent->update();
}

template<typename TNode>
void zugZug(TNode* pnode) {
    TNode *parent = pnode->getParent();
    if (pnode->isLeft() ^ parent->isLeft()) {
        zug(pnode);
        zug(pnode);
    }
    else {
        zug(parent);
        zug(pnode);
    }
}


template<typename TNode>
void upperPush(TNode* pnode) {
    std::vector<TNode*> stack;
    stack.push_back(pnode);
    TNode* parent = stack.back()->getParent();
    while (parent) {
        stack.push_back(parent);
        parent = parent->getParent();
    }
    while (!stack.empty()) {
        stack.back()->push();
        stack.pop_back();
    }
}


template<typename TNode>
void splay(TNode* pnode) {
    //upperPush(pnode);
    pnode->push();
    while (!pnode->isRoot()) {
        TNode *parent = pnode->getParent();
        if (parent->isRoot()) {
            zug(pnode);
            break;
        }
        zugZug(pnode);
    }
    pnode->update();
}


template<typename TNode>
TNode* find(unsigned int key, TNode* root) {
    TNode* cursor = root;
    while (true) {
        cursor->push();
        unsigned int position = getPos(cursor);
        if (position == key) {
            break;
        } else if (position < key) {
            key -= getPos(cursor);
            if (!cursor->getRight()) break;
            cursor = cursor->getRight();
        } else {
            if (!cursor->getLeft()) break;
            cursor = cursor->getLeft();
        }
    }
    //cursor->push();

    splay(cursor);
    return cursor;
}

template<typename TNode>
void merge(TNode* leftRoot, TNode* rightRoot, TNode*& result) {
    result = NULL;
    if (leftRoot) {
        leftRoot = leftRoot->getRightest();
        splay(leftRoot);
        leftRoot->linkToRight(rightRoot);
        result = leftRoot;
    }
    else {
        rightRoot = rightRoot->getLeftest();

        //upperPush(rightRoot);
        splay(rightRoot);
        rightRoot->linkToLeft(leftRoot);
        result = rightRoot;
    }
    result->update();
}

// all key values <= key in the left part
template<typename TNode>
void split(unsigned int key, TNode* root, TNode*& leftRoot, TNode*& rightRoot) {
    root = find(key, root);
    if (key < getPos(root)) {
        leftRoot = root->cutLeft();
        rightRoot = root;
    }
    else {
        leftRoot = root;
        rightRoot = root->cutRight();
    }
    root->update();
    return;
}


//gives pnode to the left part
template<typename TNode>
void split(TNode* pnode, TNode*& leftRoot, TNode*& rightRoot) {
    upperPush(pnode);
    splay(pnode);
    leftRoot = pnode;
    rightRoot = pnode->cutRight();
    pnode->update();
    return;
}


//gives pnode to the right part
template<typename TNode>
void rsplit(TNode* pnode, TNode*& leftRoot, TNode*& rightRoot) {
    upperPush(pnode);
    splay(pnode);
    rightRoot = pnode;
    leftRoot = pnode->cutLeft();
    pnode->update();
    return;

}


template<typename TNode>
TNode* add(unsigned int key, TNode* root, TNode* newNode) {

    TNode* right;
    split(key, root, root, right);
    newNode->makeRoot();
    newNode->linkToLeft(root);
    newNode->linkToRight(right);

    newNode->update();
    return newNode;
}

#endif // _SPLAYTREE_H_