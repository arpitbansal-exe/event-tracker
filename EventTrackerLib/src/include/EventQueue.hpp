#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>

class EventQueue {
public:
    using SendFunction = std::function<void(const std::string&)>;

    EventQueue(SendFunction sender);
    ~EventQueue();

    void push(const std::string& payload);
    void flush();      
    void shutdown();   
private:
    void processLoop();

    std::queue<std::string> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::thread _worker;
    std::atomic<bool> _running;

    SendFunction _sender;
};
