#ifndef _FUTEX_H_
#define _FUTEX_H_

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>
#include <exception>

class futex_unlock_exception: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Exception unlocking futex occured";
    }
};

class futex {
private:
    typedef std::thread::id tid;
    std::atomic<tid> a;
public:
    futex(void): a(tid(0)) {}

    void lock() {
        tid id = std::this_thread::get_id();
        tid zero(0);
        while (!a.compare_exchange_strong(zero, id)) {
            std::this_thread::yield();
            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
            zero = std::thread::id(0);
        }
    }

    bool try_lock() {
        tid id = std::this_thread::get_id();
        tid zero(0);
        return a.compare_exchange_strong(zero, id);
    }

    void unlock() {
        tid id = std::this_thread::get_id();
        tid zero(0);
        if (!a.compare_exchange_strong(id, zero)) {
            throw futex_unlock_exception();
        }
    }
};

#endif // _FUTEX_H_