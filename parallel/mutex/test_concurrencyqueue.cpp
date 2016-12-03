#include <iostream>

#include "concurrentqueue.h"

using namespace std;

void pusher(SyncQueue<int>& q, int i) {
    while (true) {
        q.push(i);
    }
}

void taker(SyncQueue<int>& q, int i, std::mutex omutex) {
    while(true) {
        int val = q.waitAndPop();
        omutex.lock();
        std::cout << i << " : " << val << std::endl;
        omutex.unlock();
    }
}

int main() {

    std::mutex
    for (int i = 0; i < n; i += 2) {
        std::thread(pusher, std::ref(q), i);
        std::thread(taker, std::ref(q), i, std::ref(omutex));
    }

/*
    ConcurrentQueue<int> q;
    q.offer(3);
    q.offer(3);
    q.offer(5);
    std::cout << "HW" << std::endl;
    std::cout << q.waitAndPop() << std::endl;
    std::cout << q.waitAndPop() << std::endl;
    std::cout << q.waitAndPop() << std::endl;
    std::cout << q.waitAndPop() << std::endl;
*/
    return 0;
}