#include "threadpool.h"

ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this] {
            while (!stop) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}
