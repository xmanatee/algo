#ifndef _INCREMENTER_H_
#define _INCREMENTER_H_

#include <thread>
#include <future>
#include <vector>

template <typename T, typename M>
class Incrementer {
public:
    static T maxN, threadNum;
    static std::vector<std::future<T>> results;

    static void setup(const T& _maxN, const T& _threadNum) {
        maxN = _maxN;
        threadNum = _threadNum;
        results.clear();
    }

    static T lockedNaive(T& n, M& xutex) {
        T i(0);
        while (true) {
            xutex.lock();
            if (n >= maxN) {
                xutex.unlock();
                break;
            }
            ++n;
            ++i;
            xutex.unlock();
        }
        return i;
    }

    static T parallel(T &n, M& xutex) {
        for (int i = 0; i < threadNum; ++i) {
            results.push_back(std::async(std::launch::async, lockedNaive, std::ref(n), std::ref(xutex)));
        }

        T sum = 0;
        for (int i = 0; i < threadNum; ++i) {
            T c = results[i].get();
            //std::cerr << 100 * c / maxN << "%" << std::endl;
            sum += c;
        }
        return sum;
    }
};

template <typename T, typename M>
T Incrementer<T, M>::maxN(0);

template <typename T, typename M>
T Incrementer<T, M>::threadNum(0);

template <typename T, typename M>
std::vector<std::future<T>> Incrementer<T, M>::results(0);


#endif // _INCREMENTER_H_