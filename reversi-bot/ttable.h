#ifndef _TTABLE_H_
#define _TTABLE_H_

#include "common.h"
#include "reversinode.h"

class Memory {
public:
    AwardType alpha, beta;
    Memory(void) {};
    Memory(AwardType _alpha, AwardType _beta): alpha(_alpha), beta(_beta) {}
};

class TranspositionTable {
private:
    map<Node, Memory> table;
public:
    TranspositionTable(void) { }
    bool retrieve(Node &node, Memory &memory);
    void storeAlpha(Node &node, AwardType alpha);
    void storeBeta(Node &node, AwardType beta);
    void store(Node &node, AwardType alpha, AwardType beta);
    void clear() {
        table.clear();
    }
};

bool TranspositionTable::retrieve(Node &node, Memory &memory) {
    if (table.count(node) > 0) {
        memory = table[node];
        return true;
    } else {
        return false;
    }
}

void TranspositionTable::store(Node &node, AwardType alpha, AwardType beta) {
    Memory memory(alpha, beta);
    table[node] = memory;
}

void TranspositionTable::storeAlpha(Node &node, AwardType alpha) {
    if (table.count(node) > 0) {
        table[node].alpha = alpha;
    } else {
        Memory memory(alpha, INF_AWARD);
        table[node] = memory;
    }
}

void TranspositionTable::storeBeta(Node &node, AwardType beta) {
    if (table.count(node) > 0) {
        table[node].beta;
    } else {
        Memory memory(-INF_AWARD, beta);
        table[node] = memory;
    }
}

#endif