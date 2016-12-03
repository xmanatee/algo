#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <future>

std::vector<double> generateNumSet(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform(0, 1);

    std::vector<double> numSet(n);

    for (int i = 0; i < n; ++i) {
        numSet[i] = uniform(gen);
    }
    return numSet;
}

double partSumById(std::vector<double>& numbers, int a, int b) {
    double sum = 0;
    for (int i = a; i < b; ++i) {
        sum += numbers[i];
    }
    return sum;
}

double partSumSinById(std::vector<double>& numbers, int a, int b) {
    double sum = 0;
    for (int i = a; i < b; ++i) {
        sum += sin(numbers[i]);
    }
    return sum;
}


double partSumByIter(std::vector<double>::iterator begin, std::vector<double>::iterator end) {
    double sum = 0;
    while (begin != end) {
        sum += *begin;
        ++begin;
    }
    return sum;
}

double parallelSum(std::vector<double>& numbers, int threadNum) {
    std::vector<std::future<double>> results;
    int n = numbers.size();
    int partSize = n / threadNum;
    for (int i = 0; i < threadNum; ++i) {
        int a = i * partSize;
        int b = std::min((i + 1) * partSize, n);
        results.push_back(std::async(std::launch::async, partSumById,
                                     ref(numbers), a, b));
    }

    double sum = 0;
    for (int i = 0; i < threadNum; ++i) {
        sum += results[i].get();
    }
    return sum;
}

double parallelSumSin(std::vector<double>& numbers, int threadNum) {
    std::vector<std::future<double>> results;
    int n = numbers.size();
    int partSize = n / threadNum;
    for (int i = 0; i < threadNum; ++i) {
        int a = i * partSize;
        int b = std::min((i + 1) * partSize, n);
        results.push_back(std::async(std::launch::async, partSumSinById,
                                     ref(numbers), a, b));
    }

    double sum = 0;
    for (int i = 0; i < threadNum; ++i) {
        sum += results[i].get();
    }
    return sum;
}


template <typename RAIter>
int stolenSum(RAIter beg, RAIter end)
{
    typename RAIter::difference_type len = end-beg;
    if(len < 3e7)
        return std::accumulate(beg, end, 0);

    RAIter mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             stolenSum<RAIter>, mid, end);
    int sum = stolenSum(beg, mid);
    return sum + handle.get();
}

int main() {
    int N = 1e7;
    int threadMin = 1, threadMax = 15;
    int numSamples = 5;
    std::vector<double> numbers;
    double realSum, sum;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    start = std::chrono::system_clock::now();
    numbers = generateNumSet(N);
    end = std::chrono::system_clock::now();
    std::cout << "Generation: " << std::chrono::duration<double>(end - start).count() << std::endl;

    start = std::chrono::system_clock::now();
    realSum = partSumById(numbers, 0, numbers.size());
    end = std::chrono::system_clock::now();
    std::cout << "Brute time: " << std::chrono::duration<double>(end - start).count() << std::endl;
    std::cout << "REAL SUM = " << realSum << std::endl;

    start = std::chrono::system_clock::now();
    sum = partSumByIter(numbers.begin(), numbers.end());
    end = std::chrono::system_clock::now();
    std::cout << "Iter time: " << std::chrono::duration<double>(end - start).count() << std::endl;

    start = std::chrono::system_clock::now();
    sum = stolenSum(numbers.begin(), numbers.end());
    end = std::chrono::system_clock::now();
    std::cout << "Stolen time: " << std::chrono::duration<double>(end - start).count() << std::endl;

    start = std::chrono::system_clock::now();
    sum = parallelSum(numbers, 4);
    end = std::chrono::system_clock::now();
    std::cout << "Parall time: " << std::chrono::duration<double>(end - start).count() << std::endl;

    std::cout << "Time of sum() for " << threadMin << ".." << threadMax << " threads:" << std::endl;
    for (int threadNum = threadMin; threadNum <= threadMax; ++threadNum) {
        start = std::chrono::system_clock::now();
        for (int sample = 0; sample < numSamples; ++sample) {
            sum = parallelSum(numbers, threadNum);
        }
        end = std::chrono::system_clock::now();
        std::cout << std::chrono::duration<double>(end - start).count() / numSamples << std::endl;
    }

    std::cout << "Time of sumSin() for " << threadMin << ".." << threadMax << " threads:" << std::endl;
    for (int threadNum = threadMin; threadNum <= threadMax; ++threadNum) {
        start = std::chrono::system_clock::now();
        for (int sample = 0; sample < numSamples; ++sample) {
            sum = parallelSumSin(numbers, threadNum);
        }
        end = std::chrono::system_clock::now();
        std::cout << std::chrono::duration<double>(end - start).count() / numSamples << std::endl;
    }

    return 0;
}