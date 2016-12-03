/*
//
// Created by manatee on 27.05.16.
//

#ifndef SEM4_KD_H
#define SEM4_KD_H

#include <vector>
#include <functional>
#include <cstdlib>

template <typename T>
class KD {
    typedef typename std::vector<T*>::iterator vIter;
    int numCmp;
    std::vector<std::function<bool(T*, T*)>> cmp;
    class Node {
    public:
        Node *left, *right;
        T *data;
        //Plane p or BoundingBox b
        Node(Node *_left, Node *_right): left(_left), right(_right) {}
        Node(Node *_left, Node *_right, T *_data):
                left(_left),
                right(_right),
                data(_data) {}
        Node(T* _data): data(_data) {}
    };
    Node *root;
    Node *buildKD(vIter &first, vIter &last, int depth = 0) {
        int n = last - first;
        if (n == 0) return NULL;
        auto middle = first + n / 2;
        std::nth_element(first, middle, last, cmp[depth % numCmp]);
        Node *left = buildKD(first, middle);
        auto rmiddle = middle + 1;
        Node *right = buildKD(rmiddle, last);
        Node *node = new Node(left, right, *middle);
        return node;
    }
};

#endif //SEM4_KD_H
*/
