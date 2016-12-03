#pragma once

#include <vector>

class StackWithMax;

class StackWithMax {
 public:
    void put(int item);
    int getMax() const;
    int pop();
    void reverse();
    bool empty() const;
    void clear();
    int size() const;
    void operator=(const StackWithMax& other);
        
 private:
    std::vector<int> stack, maxStack;
};

void StackWithMax::put(int item) {
    stack.push_back(item);
    if (maxStack.empty()) {
        maxStack.push_back(item);
    } else {
        maxStack.push_back(std::max(item, maxStack.back()));
    }
}

int StackWithMax::getMax() const {
    assert(!empty());
    return maxStack.back();
}

int StackWithMax::pop() {
    assert(!empty());
    int value = stack.back();
    stack.pop_back();
    maxStack.pop_back();
    return value;
}

void StackWithMax::reverse() {
    std::vector<int> stackCopy(stack);
    maxStack.clear();
    stack.clear();
    while (!stackCopy.empty()) {
        put(stackCopy.back());
        stackCopy.pop_back();
    }
}

bool StackWithMax::empty() const {
    return stack.empty();
}

void StackWithMax::clear() {
    stack.clear();
    maxStack.clear();
}

int StackWithMax::size() const {
    return stack.size();
}

void StackWithMax::operator=(const StackWithMax& other) {
    stack = other.stack;
    maxStack = other.maxStack;
}

class QueueWithMax {
  public:
    void put(int item);
    int getMax() const;
    int pop();
    bool empty() const;
    int size() const;
 private:
    StackWithMax begin, end;
};

void QueueWithMax::put(int item) {
    begin.put(item);
}

int QueueWithMax::getMax() const {
    assert(!empty());
    if (begin.empty()) {
        return end.getMax();
    }
    if (end.empty()) {
        return begin.getMax();
    }
    return std::max(begin.getMax(), end.getMax());
}

int QueueWithMax::pop() {
    assert(!empty());
    if (end.empty()) {
        end = begin;
        end.reverse();
        begin.clear();
    }
    return end.pop();
}

bool QueueWithMax::empty() const {
    return begin.empty() && end.empty();
}

int QueueWithMax::size() const {
    return begin.size() + end.size();
}
