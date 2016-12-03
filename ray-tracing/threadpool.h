//
// Created by manatee on 27.05.16.
//

#include <thread>
#include <vector>
#include <mutex>
#include "settings.h"


class TaskGenerator {
public:
    typedef std::function<void()> Executor;

    virtual bool isEmpty() {
        return true;
    }

    virtual Executor operator () () {
        return Executor();
    }
};


class ThreadPool {
public:
    std::mutex mtx;
    std::vector<std::thread> threads;

    TaskGenerator *generator;

    ThreadPool(TaskGenerator *_generator): generator(_generator) {}

    void worker() {
        TaskGenerator::Executor task;
        while (true) {
            mtx.lock();
            if (generator->isEmpty()) {
                mtx.unlock();
                return ;
            }
            task = (*generator)();
            mtx.unlock();
            task();
        }
        return;
    }
    void run() {
        for (int i = 0; i < settings.threadNumber; ++i) {
            threads.push_back(std::thread(&ThreadPool::worker, this));
        }
        for (int i = 0; i < settings.threadNumber; ++i) {
            threads[i].join();
        }
    }
};
