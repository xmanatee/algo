#ifndef _SYNCQUEUE_H_
#define _SYNCQUEUE_H_

template <typename T>
class SyncQueue {
public:
    virtual T waitAndPop() = 0;

    virtual void waitAndPop(T& item) = 0;

    virtual void offer(const T& item) = 0;
};

#endif // _SYNCQUEUE_H_