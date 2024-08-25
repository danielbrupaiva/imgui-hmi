#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

#include "globals.hpp"

using namespace Global;

// Data race prevention
std::mutex mutex;
std::condition_variable condition_variable;

int main()
{
    logger.info("CppTemplate is running...");

    // Container of threads
    std::vector<std::jthread> workers;

    for(uint32_t index = 0; index < 5; index++){
        workers.emplace_back([index]() {
            const auto id = index;
            while (true) {
                std::unique_lock<std::mutex> lock(mutex);
                if (condition_variable.wait_for(lock, std::chrono::milliseconds(1), []{return false;})){
                    logger.error("Thread ID: {} fail", id);
                }
                else{
                    logger.debug("Thread ID: {} ", id);
                    condition_variable.notify_one();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        });
    }

    return 0;
}
