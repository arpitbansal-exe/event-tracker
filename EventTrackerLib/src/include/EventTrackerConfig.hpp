#pragma once

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
//Event Tracker Library Version
#define MAJOR_VERSION 1
#define MINOR_VERSION 0
#define PATCH_VERSION 0
#define EVENT_TRACKER_VERSION TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(PATCH_VERSION)

enum class DropPolicy {
    DROP_OLDEST,
    DROP_NEWEST
};

struct QueueConfig {
    size_t maxQueueSize = 100;          // Max events in queue
    size_t batchSize = 10;              // Events per HTTP POST
    size_t maxRetries = 3;              // Max retry attempts
    size_t retryDelayMs = 2000;         // Delay between retries
    DropPolicy dropPolicy = DropPolicy::DROP_OLDEST;
};
