#ifndef _CONCURRENTQUEUE_H_
#define _CONCURRENTQUEUE_H_

#include "syncqueue.h"

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue : public SyncQueue<T> {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable notEmpty;
public:
    virtual T waitAndPop() {
        std::unique_lock<std::mutex> mlock(mutex);
        notEmpty.wait(mlock, [this]{ return !this->queue.empty(); });
        auto item = queue.front();
        queue.pop();
        return item;
    }

    virtual void waitAndPop(T& item) {
        std::unique_lock<std::mutex> mlock(mutex);
        notEmpty.wait(mlock, [this]{ return !this->queue.empty(); });
        item = queue.front();
        queue.pop();
    }

    virtual void offer(const T& item) {
        std::unique_lock<std::mutex> mlock(mutex);
        queue.push(item);
        mlock.unlock();
        notEmpty.notify_one();
    }
};



#endif // _CONCURRENT_H_