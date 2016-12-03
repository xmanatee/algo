#ifndef _NODEPROPERTIES_H_
#define _NODEPROPERTIES_H_

#include "pathnode.h"

class MinProperty {
private:
    static const long long NEUTRAL;

    long long value;
    long long minValue;
    long long delta;
    long long initialValue;
public:

    MinProperty(void);
    MinProperty(long long _value);
    long long getValue();
    long long getMinValue();
    long long getHistory();
    void reset();
    void reset(long long _value);

    void receiveDelta(long long _delta);
    void push(PathNode<MinProperty> *leftChild, PathNode<MinProperty> *rightChild);
    void update(PathNode<MinProperty> *leftChild, PathNode<MinProperty> *rightChild);

    friend PathNode<MinProperty>* findMinHolder(PathNode<MinProperty> *root);
    friend std::ostream& operator << (std::ostream& out, MinProperty *property);
    friend bool compare(MinProperty *a, MinProperty * b);
};

PathNode<MinProperty>* findMinHolder(PathNode<MinProperty> *root);

#ifdef _LINKCUt_H_
// before calling CALL REVERT FROM ROOT
long long getMin(PathNode<MinProperty>* pnode);
#endif


bool compare(MinProperty *a, MinProperty *b);


std::ostream& operator << (std::ostream& out, MinProperty *property);


#endif // _NODEPROPERTIES_H_