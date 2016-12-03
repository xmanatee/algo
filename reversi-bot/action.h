#ifndef _ACTION_H_
#define _ACTION_H_

#include "common.h"
#include "reversinode.h"

class Action {
public:
    Int i, j;
    Action(Int _i, Int _j): i(_i), j(_j) { }
    Action(void): i(0), j(0) { }
    Node apply(const Node &node) const;
    void directedApply(Node &node, Int di, Int dj) const;
    bool validFor(const Node &node) const;
    bool directedValidFor(const Node &node, Int di, Int dj) const;
};

bool Action::directedValidFor(const Node &node, Int di, Int dj) const {
    Int len = 0;
    Int curi = i;
    Int curj = j;
    while (true) {
        ++len;
        curi += di;
        curj += dj;
        if (!isInField(curi, curj) || !node.filledMask(curi, curj)) {
            return false;
        }
        if (!node.whiteMask(curi, curj) ^ node.whitesTurn) {
            break;
        }
    }
    if (len > 1) {
        return true;
    }
    return false;
}

bool Action::validFor(const Node &node) const {
    if (node.filledMask(i, j)) return false;
    return (directedValidFor(node, 1, 0)
            || directedValidFor(node, 1, 1)
            || directedValidFor(node, 0, 1)
            || directedValidFor(node, -1, 1)
            || directedValidFor(node, -1, 0)
            || directedValidFor(node, -1, -1)
            || directedValidFor(node, 0, -1)
            || directedValidFor(node, 1, -1));
}

vector<Action> getValidActions(const Node &node) {
    Action action(0, 0);
    vector<Action> actions;
    for (action.i = 0; action.i < FIELD_SIZE; ++action.i) {
        for (action.j = 0; action.j < FIELD_SIZE; ++action.j) {
            if (action.validFor(node)) {
                actions.push_back(action);
            }
        }
    }
    return actions;
}

bool isGameOver(const Node &node) {
    return (getValidActions(node).size() == 0);
}

Node Action::apply(const Node &node) const {
    Node newNode = node;
    newNode.filledMask.set(i, j, true);
    newNode.whiteMask.set(i, j, node.whitesTurn);

    if (directedValidFor(node, 1, 0)) directedApply(newNode, 1, 0);
    if (directedValidFor(node, 1, 1)) directedApply(newNode, 1, 1);
    if (directedValidFor(node, 0, 1)) directedApply(newNode, 0, 1);
    if (directedValidFor(node, -1, 1)) directedApply(newNode, -1, 1);
    if (directedValidFor(node, -1, 0)) directedApply(newNode, -1, 0);
    if (directedValidFor(node, -1, -1)) directedApply(newNode, -1, -1);
    if (directedValidFor(node, 0, -1)) directedApply(newNode, 0, -1);
    if (directedValidFor(node, 1, -1)) directedApply(newNode, 1, -1);

    newNode.whitesTurn ^= true;

    if (getValidActions(newNode).size() == 0) {
        newNode.whitesTurn ^= true;
    }

    return newNode;
}

void Action::directedApply(Node &node, Int di, Int dj) const {
    Int len = 0;
    Int curi = i;
    Int curj = j;
    while (true) {
        ++len;
        curi += di;
        curj += dj;
        if (!node.whiteMask(curi, curj) ^ node.whitesTurn) {
            break;
        }
        node.whiteMask.set(curi, curj, node.whitesTurn);
    }

}

ostream& operator << (ostream& out, const Action &action) {
    out << "" << static_cast<char>(action.i + 'a') << " " << static_cast<char>(action.j + '1') << "";
    return out;
}

istream& operator >> (istream& in, Action &action) {
    char c;
    in >> c;
    action.i = c - 'a';
    in >> c;
    action.j = c - '1';
    return in;
}

ostream& operator << (ostream& out, const Node &node) {
    if (node.whitesTurn) {
        out << "Whites Turn:\n";
    } else {
        out << "Blacks Turn:\n";
    }
    out << "  abcdefgh\n";
    for (Int i = 0; i < FIELD_SIZE; ++i) {
        out << static_cast<char>(i + '1') << " ";
        for (Int j = 0; j < FIELD_SIZE; ++j) {
            if (node.whiteMask(j, i)) {
                out << static_cast<char>(WHITE_CELL);
            } else if (node.filledMask(j, i)) {
                out << static_cast<char>(BLACK_CELL);
            } else {
                Action action(j, i);
                if (action.validFor(node)) {
                    out << static_cast<char>(VALID_CELL);
                } else {
                    out << static_cast<char>(EMPTY_CELL);
                }
            }
        }
        out << "\n";
    }
    return out;
}

void outPossibleActions(Node &node) {
    vector<Action> actions = getValidActions(node);
    cout << "Possible Actions :\n";
    for (int i = 0; i < actions.size(); ++i) {
        cout << actions[i] << "\n";
    }
}

#endif // _ACTION_H_