#include "EventQueue.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
EventQueue::EventQueue(SendFunction sender, const QueueConfig& config)
    : _sender(std::move(sender)),
    _running(true),
    _config(config),
    _worker(&EventQueue::worker, this)  // start worker after all initializations
{
}

EventQueue::~EventQueue() {
    _running = false;
    _cv.notify_all();
    if (_worker.joinable())
        _worker.join();
}

void EventQueue::push(const json& event) {
    std::unique_lock lock(_mutex);
    if (_queue.size() >= _config.maxQueueSize) {
        if (_config.dropPolicy == DropPolicy::DROP_OLDEST) {
            _queue.pop();
        }
        else {
            return; // DROP_NEWEST - do not enqueue new event
        }
    }
    _queue.push(event);  //Pushing event in queue
    _cv.notify_one();
}
void EventQueue::worker() {
    while (_running) {
        std::vector<json> batch;
        {
            std::unique_lock lock(_mutex);
            _cv.wait(lock, [&] { return !_queue.empty() || !_running; });

            while (!_queue.empty() && batch.size() < _config.batchSize) {
                batch.push_back(_queue.front());
                _queue.pop();
            }
        }

        if (!batch.empty()) {
            processBatch(batch);
        }
    }
}

void EventQueue::processBatch(const std::vector<json>& batch) {
    size_t attempt = 0;
    while (attempt <= _config.maxRetries) {
        bool success= _sender(batch);
        if(success)
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(_config.retryDelayMs));
        attempt++;
    }
}

void EventQueue::flush() {
    std::unique_lock<std::mutex> lock(_mutex);
    while (!_queue.empty()) {
        std::vector<json> batch;

        size_t count = 0;
        while (!_queue.empty() && count < _config.batchSize) {
            batch.push_back(std::move(_queue.front()));
            _queue.pop();
            ++count;
        }

        lock.unlock();
        processBatch(batch);  // Handles retries internally
        lock.lock();
    }
}
void EventQueue::shutdown() {
    flush();
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _running = false;
    }
    _cv.notify_all();

    if (_worker.joinable())
        _worker.join();
}