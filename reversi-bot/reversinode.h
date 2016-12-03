#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

#include "bitboard.h"

const Int FIELD_SIZE = 8;
const Int WHITE_CELL = 'W';
const Int BLACK_CELL = 'B';
const Int VALID_CELL = ' ';
const Int EMPTY_CELL = '*';


bool isInField(Int i, Int j) {
    return ((0 <= i) && (i < FIELD_SIZE) && (0 <= j) && (j < FIELD_SIZE));
}

class Node {
public:
    BitBoard8x8 filledMask;
    BitBoard8x8 whiteMask;
    bool whitesTurn;

    Node(void);
    void pass();
    Int count() const;
    Int countWhites() const;
    Int countBlacks() const;
};

Node::Node(void): filledMask(), whiteMask(), whitesTurn(false) { }

void Node::pass() {
    whitesTurn ^= true;
}

bool operator < (const Node &a, const Node &b) {
    if (a.whitesTurn ^ b.whitesTurn) {
        return b.whitesTurn;
    }
    for (Int i = 0; i < FIELD_SIZE; ++i) {
        if ((a.filledMask[i]) ^ b.filledMask[i]) {
            return a.filledMask[i] < b.filledMask[i];
        }
        if (a.whiteMask[i] ^ b.whiteMask[i]) {
            return a.filledMask[i] < b.whiteMask[i];
        }
    }
    return false;
}

Node getStartingNode() {
    Node startingNode;
    startingNode.filledMask.set(3, 3, true);
    startingNode.filledMask.set(3, 4, true);
    startingNode.filledMask.set(4, 3, true);
    startingNode.filledMask.set(4, 4, true);
    startingNode.whiteMask.set(3, 3, true);
    startingNode.whiteMask.set(4, 4, true);
    return startingNode;
}

Int Node::count() const {
    Int discs = 0;
    for (Int i = 0; i < FIELD_SIZE; ++i) {
        for (Int j = 0; j < FIELD_SIZE; ++j) {
            if (filledMask(i, j)) ++discs;
        }
    }
    return discs;
}

Int Node::countWhites() const {
    Int whites = 0;
    for (Int i = 0; i < FIELD_SIZE; ++i) {
        for (Int j = 0; j < FIELD_SIZE; ++j) {
            if (whiteMask(i, j)) ++whites;
        }
    }
    return whites;
}

Int Node::countBlacks() const {
    Int blacks = 0;
    for (Int i = 0; i < FIELD_SIZE; ++i) {
        for (Int j = 0; j < FIELD_SIZE; ++j) {
            if (filledMask(i, j) && !whiteMask(i, j)) ++blacks;
        }
    }
    return blacks;
}




#endif // _NODE_H_
