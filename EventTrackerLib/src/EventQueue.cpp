#include "EventQueue.hpp"

EventQueue::EventQueue(SendFunction sender)
    : _sender(sender), _running(true), _worker(&EventQueue::processLoop, this) {
}

EventQueue::~EventQueue() {
    _running = false;
    _cv.notify_all();
    if (_worker.joinable())
        _worker.join();
}

void EventQueue::push(const std::string& payload) {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(payload);
    }
    _cv.notify_one();
}

void EventQueue::processLoop() {
    while (_running) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this]() { return !_queue.empty() || !_running; });

        while (!_queue.empty()) {
            std::string payload = _queue.front();
            _queue.pop();
            lock.unlock(); // unlock while processing
            _sender(payload); // call the sender function
            lock.lock();     // lock again before next pop
        }
    }
}
void EventQueue::flush() {
    std::unique_lock<std::mutex> lock(_mutex);
    while (!_queue.empty()) {
        std::string payload = _queue.front();
        _queue.pop();
        lock.unlock();
        _sender(payload);
        lock.lock();
    }
}
void EventQueue::shutdown() {
    _running = false;
    _cv.notify_all();
    if (_worker.joinable())
        _worker.join();
}