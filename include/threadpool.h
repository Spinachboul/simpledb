#ifndef SIMPLEDB_THREADPOOL_H
#define SIMPLEDB_THREADPOOL_H

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::atomic<bool> stop;
public:
    explicit ThreadPool(size_t threads);
    ~ThreadPool();

    template<class F>
    void enqueue(F&& f) {
        // In real system: push to a queue
        // Here: just run immediately (no real thread queue)
        f();
    }
};

#endif // SIMPLEDB_THREADPOOL_H
