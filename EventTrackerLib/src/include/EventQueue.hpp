#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>
#include "EventTrackerConfig.hpp"
class EventQueue {
public:
    using SendFunction = std::function<bool(const std::vector<std::string>&)>;

    EventQueue(SendFunction sender, const QueueConfig& config);
    ~EventQueue();

    void push(const std::string& payload);
    void flush();      
    void shutdown();   
private:
    void processBatch(const std::vector<std::string>& batch);
    void worker();

    std::queue<std::string> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::thread _worker;
    std::atomic<bool> _running;

    QueueConfig _config;
    SendFunction _sender;
};
