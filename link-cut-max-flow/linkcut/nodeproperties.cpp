#ifndef _NODEPROPERTIES_CPP_
#define _NODEPROPERTIES_CPP_

#include "nodeproperties.h"

const long long MinProperty::NEUTRAL = (const long long) (1e18 + 7);

MinProperty::MinProperty(void): value(NEUTRAL), minValue(NEUTRAL), delta(0), initialValue(NEUTRAL) {}
MinProperty::MinProperty(long long _value): value(_value), minValue(_value), delta(0), initialValue(_value) {}


long long MinProperty::getValue() {
    return value;
}


long long MinProperty::getMinValue() {
    return minValue;
}


long long MinProperty::getHistory() {
    return initialValue - value;
}


void MinProperty::reset() {
    value = NEUTRAL;
    minValue = NEUTRAL;
    delta = 0;
    initialValue = NEUTRAL;
}


void MinProperty::reset(long long _value) {
    value = _value;
    minValue = _value;
    delta = 0;
    initialValue = _value;
}


void MinProperty::receiveDelta(long long _delta) {
    delta += _delta;
    value += _delta;
    minValue += _delta;
    return;
}


void MinProperty::push(PathNode<MinProperty> *leftChild, PathNode<MinProperty> *rightChild) {
    long long delta = this->delta;
    if (delta) {
        if (leftChild) {
            leftChild->getProperty()->receiveDelta(delta);
        }
        if (rightChild) {
            rightChild->getProperty()->receiveDelta(delta);
        }
        this->delta = 0;
    }
}


void MinProperty::update(PathNode<MinProperty> *leftChild, PathNode<MinProperty> *rightChild) {
    long long leftMin, rightMin;
    leftMin = leftChild ? leftChild->getProperty()->minValue : MinProperty::NEUTRAL;
    rightMin = rightChild ? rightChild->getProperty()->minValue : MinProperty::NEUTRAL;

    long long minOfChildren = leftMin < rightMin ? leftMin : rightMin;
    minValue = value < minOfChildren ? value : minOfChildren;
}


PathNode<MinProperty>* findMinHolder(PathNode<MinProperty> *root) {
    long long min = root->getProperty()->minValue;
    PathNode<MinProperty>* current = root;
    while (true) {
        current->push();
        PathNode<MinProperty>* left = current->getLeft();
        if (left && left->getProperty()->minValue == min) {
            current = left;
        }
        else if (current->getProperty()->value == min) {
            return current;
        }
        else {
            current = current->getRight();
        }
    }
}


#ifdef _LINKCUt_H_
// before calling CALL REVERT FROM ROOT
long long getMin(PathNode<MinProperty>* pnode) {
    expose(pnode);
    PathNode<MinProperty> *right = pnode->cutRight();
    long long ans = pnode->getProperty()->minValue;
    pnode->linkToRight(right);
    return ans;
}
#endif


bool compare(MinProperty *a, MinProperty *b) {
    return (a->value < b->value);
}


std::ostream& operator << (std::ostream& out, MinProperty *property) {
    std::cerr << "(" << property->value << "," << property->minValue << ")";
    return out;
}

#endif // _NODEPROPERTIES_CPP_
