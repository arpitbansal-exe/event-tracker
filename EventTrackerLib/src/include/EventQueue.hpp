#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>
#include "EventTrackerConfig.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
class EventQueue {
public:
    using SendFunction = std::function<bool(const std::vector<json>&)>;

    EventQueue(SendFunction sender, const QueueConfig& config);
    ~EventQueue();

    void push(const json & payload);
    void flush();      
    void shutdown(); 
	QueueConfig getConfig() const { return _config; }
private:
    void processBatch(const std::vector<json>& batch);
    void worker();

    std::queue<json> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::thread _worker;
    std::atomic<bool> _running;

    QueueConfig _config;
    SendFunction _sender;
};
