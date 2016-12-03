//
// Created by manatee on 12.05.16.
//

#ifndef GRAPHIC3D_KDTREE_H
#define GRAPHIC3D_KDTREE_H
/*
#include <vector>
#include <algorithm>
#include "../figure/simplesphere.h"
#include "../figure/figure3d.h"

using std::nth_element;

int steps = 0;

class KDTree {
public:
    class Node {
        SimpleSphere bounds;
        Node *left, *right;
        Figure3d* figure;
        Node() {}
        Node (Figure3d *_figure) : figure(_figure) {
            bounds = figure->getBoundingSphere();
            left = right = NULL;
        }
    };

    Node *root;

    void recalc(Node *v) {
        if (v->left) {
            v->bounds = (v->bounds | v->left->bounds);
        }
        if (v->right) {
            v->bounds = (v->bounds | v->right->bounds);
        }
    }

    Node *makeTree(std::vector<Figure3d*>::iterator begin,
                   std::vector<Figure3d*>::iterator end, int step) {
        if (begin == end) {
            return NULL;
        }
        int n = end - begin;
        nth_element(begin, begin + n / 2, end,
                    [&step] (const Figure3d* a, const Figure3d *b) {
                        return a->getBoundingSphere(step, 0) <
                               b->getBoundingSphere(step, 0);
                    });
        Node *result = new Node(*(begin + n / 2));
        result->left = makeTree(begin, begin + (n / 2),
                                (step + 1) % DIMENSIONS);
        result->right = makeTree(begin + (n / 2) + 1, end,
                                 (step + 1) % DIMENSIONS);
        recalc(result);
        return result;
    }

    KDTree(std::vector<Figure3d*> figures) {
        root = makeTree(figures.begin(), figures.end(), 0);
    }

    void intersect(Node *v, myFloat &currentTime,
                   const IBody * &currentIntersection,
                   const Ray &currentRay) const {
        ++steps;
        if (!v || !(v->bounds.intersects(currentRay))) {
            return;
        }
        if (!v->body->getFigure()->on(currentRay.start)) {
            Vector current = v->body->getFigure()->rayIntersection(currentRay);
            if (current != NONE) {
                myFloat myTime = (current - currentRay.start)
                                 * currentRay.direction;
                if (greater(myTime, 0.) && less(myTime, currentTime)) {
                    currentTime = myTime;
                    currentIntersection = v->body;
                }
            }
        }
        intersect(v->left, currentTime, currentIntersection, currentRay);
        intersect(v->right, currentTime, currentIntersection, currentRay);
    }

    virtual pair<Vector, const IBody *> rayIntersection(const Ray &ray) const {
        myFloat currentTime = 1e18;
        const IBody * currentIntersection = NULL;
        intersect(root, currentTime, currentIntersection, ray);
        if (eq(currentTime, 1e18)) {
            return {NONE, NULL};
        }
        return {ray.start + ray.direction * currentTime, currentIntersection};
    }

    ~KDTree() {
        delete root;
    }
};
*/
#endif //GRAPHIC3D_KDTREE_H
