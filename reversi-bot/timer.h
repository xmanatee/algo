#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

const double TIMER_RATIO = 0.99;
bool TIMESUP = false;
class Timer {
public:
    double secDelay;
    int initTime;
    Timer(double initSecDelay): secDelay(initSecDelay) {}

    void init() {
        initTime = clock();
        TIMESUP = false;
    }

    bool timesUp() {
        if (TIMESUP) return true;
        TIMESUP = (clock() - initTime > CLOCKS_PER_SEC * secDelay * TIMER_RATIO);
        return TIMESUP;
    }

    double getPastTimeSec() {
        return (clock() - initTime) * 1.0 / CLOCKS_PER_SEC;
    }
};

#endif // _TIMER_H_